#include <cmath>
#include <mpi.h>
#include <iostream>

const double t = 10e-6;
const double epsilon = 10e-9;
const int N = 5000;

void initialization(int **perProcess, int *startLine, double **matrix, double **bmatrix, double **xmatrix, int processCount, int processRank) {
    *perProcess = new int[processCount];

    for(int i = 0, temp = processCount - (N % processCount); i < processCount; ++i) {
        (*perProcess)[i] = i < temp ? (N / processCount) : (N / processCount + 1);
        if(i < processRank) {
            *startLine += (*perProcess)[i];
        }
    }

    *bmatrix = new double[(*perProcess)[processRank]];
    for(int i = 0; i < (*perProcess)[processRank]; ++i) {
        (*bmatrix)[i] = N + 1;
    }

    *xmatrix = new double[N / processCount + 1];
    for(int i = 0; i < N / processCount + 1; ++i) {
        (*xmatrix)[i] = 0;
    }

    *matrix = new double[(*perProcess)[processRank] * N];
    for(int i = 0; i < (*perProcess)[processRank]; ++i) {
        for(int j = 0; j < N; ++j) {
            (*matrix)[i * N + j] = ((*startLine) + i) == j ? 2 : 1;
        }
    }
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int processCount = 0;
    int processRank = 0;

    MPI_Comm_size(MPI_COMM_WORLD, &processCount);
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);

    double *matrix = 0;
    double *bmatrix = 0;
    double *xmatrix = 0;
    int startLine = 0;
    int *perProcess = 0;

    initialization(&perProcess, &startLine, &matrix, &bmatrix, &xmatrix, processCount, processRank);

    double *tempX = new double[N / processCount + 1]();
    double *tempSum = new double[perProcess[processRank]];


    printf("I'm %d process from %d processes and my lines: %d-%d (%d)\n", processRank, processCount, startLine,
           startLine + perProcess[processRank], perProcess[processRank]);

    double normB = 0;
    double start = 0;

    if(processRank != 0) {
        for(int i = 0; i < perProcess[processRank]; ++i) {
            normB += bmatrix[i] * bmatrix[i];
        }
        MPI_Send(&normB, 1, MPI_DOUBLE, 0, 4, MPI_COMM_WORLD); //отправляем b
    } else {
        start = MPI_Wtime();

        for(int i = 0; i < perProcess[processRank]; ++i) {
            normB += bmatrix[i] * bmatrix[i];
        }

        for(int i = 1; i < processCount; ++i) {
            double temp;
            MPI_Status status;
            MPI_Recv(&temp, 1, MPI_DOUBLE, i, 4, MPI_COMM_WORLD, &status);
            normB += temp;
        }
        normB = sqrt(normB);
    }

    int f = true;
    while(f) {

        for(int i = 0; i < perProcess[processRank]; ++i) {
            tempSum[i] = 0;
        }

        for(int i = processRank, currentLine = startLine, l=0; l < processCount; i=(i+1)%processCount, ++l) {
            for(int k = currentLine, c = currentLine + perProcess[i]; k < c; ++k) {
                for(int j = 0; j < perProcess[processRank]; ++j) {
                    tempSum[j] += matrix[j * N + k] * xmatrix[k - currentLine];
                }
            }

            MPI_Status status;

            MPI_Sendrecv(xmatrix, N / processCount + 1, MPI_DOUBLE, (processRank - 1 + processCount) % processCount, 0,
                         tempX, N / processCount + 1, MPI_DOUBLE, (processRank + 1) % processCount, 0, MPI_COMM_WORLD, &status);

            std::swap(xmatrix, tempX);
            currentLine = (currentLine+ perProcess[i]) % N;
        }

        double processAnswer = 0;

        for(int i = 0; i < perProcess[processRank]; ++i) {
            tempSum[i] -= bmatrix[i];

            xmatrix[i] = xmatrix[i] - tempSum[i] * t;
            processAnswer += tempSum[i] * tempSum[i];
        }

        if(processRank != 0) {

            MPI_Send(&processAnswer, 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD); //частичную сумму координат

        } else {

            double s = processAnswer;
            for(int i  = 1; i < processCount; ++i) {
                MPI_Status status;
                double temp;
                MPI_Recv(&temp, 1, MPI_DOUBLE, i, 2, MPI_COMM_WORLD, &status); //получаем частичную сумму

                s += temp;
            }

            s = sqrt(s);

            f = s / normB >= epsilon;
        }

        MPI_Bcast(&f, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }

    if(processRank != 0) {
        MPI_Send(xmatrix, perProcess[processRank], MPI_DOUBLE, 0, 1, MPI_COMM_WORLD); //отправляем столбец значений
    } else {
        double *fX = new double[N];
        for(int i = 0; i < perProcess[processRank]; ++i) {
            fX[i] = xmatrix[i];
        }

        for(int i = 1, currentLine = perProcess[processRank]; i < processCount; ++i) {
            MPI_Status status;
            MPI_Recv(&fX[currentLine], perProcess[i], MPI_DOUBLE, i, 1, MPI_COMM_WORLD, &status); //получаем столбец
            currentLine += perProcess[i];
        }

        double finish = MPI_Wtime();
        std::cout << "process: " << processCount << ", time: " << (finish - start) << std::endl;


        bool correctAnswer = true;
        for(int i = 0; i < N; ++i) {
            if(fabs(fX[i] - 1) >= epsilon) {
                correctAnswer = false;
                break;
            }
        }

        std::cout << "Answer correct: " << correctAnswer << std::endl;

        delete[] fX;
    }

    delete[] bmatrix;
    delete[] matrix;
    delete[] perProcess;
    delete[] tempX;
    delete[] xmatrix;

    MPI_Finalize();
    return 0;
}
