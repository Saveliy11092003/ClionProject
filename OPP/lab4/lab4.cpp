#include <algorithm>
#include "mpi.h"
#include <iostream>
#include <cmath>

#define DY 2.0f
#define DX 2.0f
#define DZ 2.0f

#define PARAMETER 1e5
#define EPSILON 1e-8

#define NY 398
#define NX 373
#define NZ 333

const double hz = DZ / (NZ - 1);
const double hy = DY / (NY - 1);
const double hx = DX / (NX - 1);
const double h2Z = hz * hz;
const double h2Y = hy * hy;
const double h2X = hx * hx;
const double factor = 1 / (2 / h2X + 2 / h2Y + 2 / h2Z + PARAMETER);

double phiF(double x, double y, double z) {
    return x * x + y * y + z * z;
}

double tail(double x, double y, double z) {
    return 6 - phiF(x, y, z) * PARAMETER;
}

void receiveBorders(MPI_Request sR, MPI_Request rR) {
    MPI_Wait(&rR, MPI_STATUS_IGNORE);
    MPI_Wait(&sR, MPI_STATUS_IGNORE);
}

void sendBorders(int pos, int sizeP, int rankP, double *Function, int t, double *buf, MPI_Request *sR, MPI_Request *rR) {
    MPI_Isend(&(Function[pos]), sizeP, MPI_DOUBLE, rankP, t, MPI_COMM_WORLD, &sR[t]);
    MPI_Irecv(buf, sizeP, MPI_DOUBLE, rankP, 1 - t, MPI_COMM_WORLD, &rR[1 - t]);
}


void initBounds(int x, int y, int z, double **F, const int *offsets, int rank) {
    int startLine = offsets[rank];
    for (int r = 0; r < x; r++, startLine++) {
        for (int l = 0; l < y; l++) {
            for (int v = 0; v < z; v++) {
                if ((startLine != 0) && (l != 0) && (v != 0) && (startLine != NX-1) && (l != y-1) && (v != z-1)) {
                    F[0][r * y * z + l * z + v] = 0;
                    F[1][r * y * z + l * z + v] = 0;
                } else {
                    F[0][r * y * z + l * z + v] = phiF(startLine * hx, l * hy, v * hz);
                    F[1][r * y * z + l * z + v] = F[0][r * y * z + l * z + v];
                }
            }
        }
    }
}

double findDif(int X, int Y, int Z, double *Function, int shift) {
    double m = 0;
    double dif;
    for (int i = 1; i < X - 2; i++) {
        for (int j = 1; j < Y; j++) {
            for (int k = 1; k < Z; k++) {
                dif = fabs(Function[i * Y * Z + j * Z + k] - phiF((i + shift) * hx, j * hy, k * hz));
                m = std::max(m, dif);
            }
        }
    }
    double r = 0;
    MPI_Allreduce(&m, &r, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
    return r;
}

double calculate(int X, int Y, int Z, int shift, int curent, double m, double **Function) {
    double p, termX, termY, termZ;
    for (int x = 1; x < X - 1; ++x) {
        for (int y = 1; y < Y - 1; ++y) {
            for (int z = 1; z < Z - 1; ++z) {

                termX = (Function[1 - curent][(x + 1) * Y * Z + y * Z + z] + Function[1 - curent][(x - 1) * Y * Z + y * Z + z]) / h2X;
                termY = (Function[1 - curent][x * Y * Z + (y + 1) * Z + z] + Function[1 - curent][x * Y * Z + (y - 1) * Z + z]) / h2Y;
                termZ = (Function[1 - curent][x * Y * Z + y * Z + (z + 1)] + Function[1 - curent][x * Y * Z + y * Z + (z - 1)]) / h2Z;
                p = tail((x + shift) * hx, y * hy, z * hz);
                Function[curent][x * Y * Z + y * Z + z] = factor * (termX + termY + termZ - p);

                double diff = fabs(Function[curent][x * Y * Z + y * Z + z] - Function[1 - curent][x * Y * Z + y * Z + z]);
                m = std::max(m, diff);
            }
        }
    }
    return m;
}

double calculateRightB(int X, int Y, int Z, int cur, int shift, double m, double **Function, const double *b) {
    double p, termX, termY, termZ;
    for (int y = 1; y < Y-1; ++y) {
        for (int z = 1; z < Z-1; ++z) {
            int x = X - 1;

            termX = (b[y * Z + z] + Function[1 - cur][(x - 1) * Y * Z + y * Z + z]) / h2X;
            termY = (Function[1 - cur][x * Y * Z + (y + 1) * Z + z] + Function[1 - cur][x * Y * Z + (y - 1) * Z + z]) / h2Y;
            termZ = (Function[1 - cur][x * Y * Z + y * Z + (z + 1)] + Function[1 - cur][x * Y * Z + y * Z + (z - 1)]) / h2Z;
            p = tail((x + shift) * hx, y * hy, z * hz);
            Function[cur][x * Y * Z + y * Z + z] = factor * (termX + termY + termZ - p);

            double diff = fabs(Function[cur][x * Y * Z + y * Z + z] - Function[1 - cur][x * Y * Z + y * Z + z]);
            m = std::max(m, diff);
        }
    }
    return m;
}

double calculateLeftB(int Y, int Z, int cur, int shift, double max, double **Function, const double *b) {
    double p, termX, termY, termZ;
    for (int y = 1; y < Y-1; ++y) {
        for (int z = 1; z < Z-1; ++z) {
            int x = 0;
            termX = (Function[1 - cur][(x + 1) * Y * Z + y * Z + z] + b[y * Z + z]) / h2X;
            termY = (Function[1 - cur][x * Y * Z + (y + 1) * Z + z] + Function[1 - cur][x * Y * Z + (y - 1) * Z + z]) / h2Y;
            termZ = (Function[1 - cur][x * Y * Z + y * Z + (z + 1)] + Function[1 - cur][x * Y * Z + y * Z + (z - 1)]) / h2Z;
            p = tail((x + shift) * hx, y * hy, z * hz);
            Function[cur][x * Y * Z + y * Z + z] = factor * (termX + termY + termZ - p);

            double diff = fabs(Function[cur][x * Y * Z + y * Z + z] - Function[1 - cur][x * Y * Z + y * Z + z]);
            max = std::max(max, diff);
        }
    }
    return max;
}

double jac(int X, int Y, int Z, int shift, int sizeP, int rankP, double **Functions) {

    double * b[2];
    b[0] = new double[Z * Y];
    b[1] = new double[Z * Y];

    MPI_Request sReq[2], rReq[2];

    int cur = 0;
    double max = 0;
    do {
        double maxCount = 0;
        cur = 1 - cur;
        if (rankP != 0) {
            sendBorders(0, Z * Y, rankP - 1, Functions[1 - cur], 0, b[0], sReq, rReq);
        }
        if (rankP != sizeP - 1) {
            sendBorders((X - 1) * Y * Z, Z * Y, rankP + 1, Functions[1 - cur], 1, b[1], sReq, rReq);
        }

        maxCount = calculate(X, Y, Z, shift, cur, maxCount, Functions);

        if (rankP != 0) {
            receiveBorders(sReq[0], rReq[1]);
            maxCount = calculateLeftB(Y, Z, cur, shift, maxCount, Functions, b[0]);
        }
        if (rankP != sizeP - 1) {
            receiveBorders(sReq[1], rReq[0]);
            maxCount = calculateRightB(X, Y, Z, cur, shift, maxCount, Functions, b[1]);
        }

        MPI_Allreduce(&maxCount, &max, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);

    }while (max >= EPSILON);


    double r = findDif(X, Y, Z, Functions[cur], shift);

    delete[] b[0];
    delete[] b[1];

    return r;
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    int processSize, processRank;
    MPI_Comm_size(MPI_COMM_WORLD, &processSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);

    int shiftForProcess = 0;

    int linesPerProcess[processSize];

    int shifts[processSize];

    for (int j = 0; j < processSize; ++j) {
        shifts[j] = shiftForProcess;
        linesPerProcess[j] = NX / processSize;

        if (j >= processSize - (NX % processSize)) {
            linesPerProcess[j]++;
        }

        shiftForProcess += linesPerProcess[j];
    }
    double *Functions[2];

    Functions[0] = new double[linesPerProcess[processRank] * NY * NZ];
    Functions[1] = new double[linesPerProcess[processRank] * NY * NZ];

    initBounds(linesPerProcess[processRank], NY, NZ, Functions, shifts, processRank);

    double startTime = MPI_Wtime();


    double r = jac(linesPerProcess[processRank], NY, NZ, shifts[processRank], processSize, processRank, Functions);

    double finishTime = MPI_Wtime();

    if (processRank == 0) {
        std::cout << "Max difference: " << r << std::endl;
        std::cout << "Time: " << finishTime-startTime << std::endl;
    }

    delete[] Functions[0];
    delete[] Functions[1];
    MPI_Finalize();
    return EXIT_SUCCESS;
}
