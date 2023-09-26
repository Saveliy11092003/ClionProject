#include <cmath>
#include <mpi.h>
#include <iostream>

const double epsilon = 10e-9;
const int N = 5000;
const double t = 10e-6;

void
initialization(int **perProcess, int *startLine, double **matrix, double **bmatrix, double **xmatrix, int processCount,
               int processRank) {

    *perProcess = new int[processCount];

    for (int k = 0, temp = processCount - (N % processCount); k < processCount; ++k) {
        (*perProcess)[k] = k < temp ? (N / processCount) : (N / processCount + 1);
        if (k < processRank) {
            *startLine += (*perProcess)[k];
        }
    }

    *matrix = new double[(*perProcess)[processRank] * N];
    for (int k = 0; k < (*perProcess)[processRank]; ++k) {
        for (int j = 0; j < N; ++j) {
            (*matrix)[k * N + j] = ((*startLine) + k) == j ? 2 : 1;
        }
    }

    *xmatrix = new double[N];
    for (int j = 0; j < N; ++j) {
        (*xmatrix)[j] = 0;
    }

    *bmatrix = new double[N];
    for (int j = 0; j < N; ++j) {
        (*bmatrix)[j] = N + 1;
    }

}


int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int processCount = 0;
    int v = 0;
    int processRank = 0;

    MPI_Comm_size(MPI_COMM_WORLD, &processCount);
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);

    double *matrix;
    double *bmatrix;
    double *xmatrix;
    int startLine = 0;
    int *perProcess;

    initialization(&perProcess, &startLine, &matrix, &bmatrix, &xmatrix, processCount, processRank);

    printf("I'm %d from %d and my lines: %d-%d (%d)\n", processRank, processCount, startLine,
           startLine + perProcess[processRank], perProcess[processRank]);

    double normB = 0;
    double start = 0;

    if (processRank == 0) {
        start = MPI_Wtime();

        for (int i = 0; i < N; ++i) {
            normB += bmatrix[i] * bmatrix[i];
        }
        normB = sqrt(normB);
    }

    int f = 1;
    double *processX = new double[perProcess[processRank]];

    while (f) {
        v++;
        double processAnswer = 0;

        for (int i = 0; i < perProcess[processRank]; ++i) {
            double s = 0;
            for (int j = 0; j < N; ++j) { //Ax
                s += matrix[i * N + j] * xmatrix[j];
            }
            s -= bmatrix[i];
            processX[i] = xmatrix[i + startLine] - s * t;
            processAnswer += s * s;
        }

        if (processRank != 0) {
            MPI_Send(processX, perProcess[processRank], MPI_DOUBLE, 0, 0, MPI_COMM_WORLD); //отправляем столбец значений
            MPI_Send(&processAnswer, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD); //частичную сумму координат


        } else {


            for (int i = startLine, c = startLine + perProcess[processRank]; i < c; ++i) {
                xmatrix[i] = processX[i - startLine];
            }


            double s = processAnswer;
            for (int i = 1, currentLine = perProcess[processRank]; i < processCount; ++i) {
                MPI_Status status;
                MPI_Recv(&xmatrix[currentLine], perProcess[i], MPI_DOUBLE, i, 0, MPI_COMM_WORLD,
                         &status); //получаем столбец
                currentLine += perProcess[i];

                double temp;
                MPI_Recv(&temp, 1, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, &status); //получаем частичную сумму
                s += temp;
            }
            s = sqrt(s);

            f = s / normB >= epsilon;
        }

        MPI_Bcast(&f, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(xmatrix, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }


    if (processRank == 0) {
        double finish = MPI_Wtime();
        std::cout << "Processes: " << processCount << ", Time: " << (finish - start) << std::endl;


        bool correctAnswer = true;
        for (int i = 0; i < N; ++i) {
            if (fabs(xmatrix[i] - 1) >= epsilon) {
                correctAnswer = false;
                break;
            }
        }

        std::cout << "Answer correct: " << correctAnswer << std::endl;
    }
    std::cout << v;
    delete[] processX;
    delete[] xmatrix;
    delete[] bmatrix;
    delete[] matrix;
    delete[] perProcess;

    MPI_Finalize();

    return 0;
}

