#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <cmath>

const double t = 10e-6;
const double epsilon = 10e-9;
const int N = 2400;

void initialization(double **matrix, double **bmatrix, double **xmatrix, double **tempX) {

    *bmatrix = new double[N];
    for(int k = 0; k < N; ++k) {
        (*bmatrix)[k] = N + 1;
    }

    *xmatrix = new double[N];
    *tempX = new double[N];
    for(int i = 0; i < N; i++) {
        (*xmatrix)[i] = 0;
        (*tempX)[i] = 0;
    }

    *matrix = new double[N * N];
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            (*matrix)[i * N + j] = i == j ? 2 : 1;
        }
    }
}

int main(int argc, char **argv) {

        if (argc < 2) {
            std::cout << "Usage: Need arg!" << std::endl;
            return EXIT_FAILURE;
        }

        int countThread = 0;
        sscanf(argv[1], "%d", &countThread);
        omp_set_num_threads(countThread);

        double *xmatrix;
        double *tempX;
        double *matrix;
        double *bmatrix;

        initialization(&matrix, &bmatrix, &xmatrix, &tempX);

        double startTime = omp_get_wtime();

        double normB = 0;
#pragma omp parallel for schedule(auto)
        for (int k = 0; k < N; ++k) {
            normB += bmatrix[k] * bmatrix[k];
        }
        normB = sqrt(normB);

        int f = true;
        while (f) {

            double s = 0;

#pragma omp parallel for schedule(auto)
            for (int i = 0; i < N; ++i) {
                double valueX = 0;
                for (int j = 0; j < N; ++j) {
                    valueX += matrix[i * N + j] * xmatrix[j];
                }
                valueX -= bmatrix[i];
                tempX[i] = xmatrix[i] - valueX * t;
                s += valueX * valueX;
            }

            std::swap(xmatrix, tempX);

            s = sqrt(s);
            f = s / normB >= epsilon;
        }

        double finishTime = omp_get_wtime();

        std::cout << "Threads: " << countThread << ", time: " << (finishTime - startTime) << std::endl;

        bool answerCorrect = true;
        for (int i = 0; i < N; ++i) {
            if (fabs(xmatrix[i] - 1) >= epsilon) {
                answerCorrect = false;
                break;
            }
        }
        std::cout << "Answer correct: " << answerCorrect << std::endl;

        delete[] bmatrix;
        delete[] matrix;
        delete[] tempX;
        delete[] xmatrix;

    return EXIT_SUCCESS;
}

