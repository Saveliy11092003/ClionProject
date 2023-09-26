#include <cmath>
#include <omp.h>
#include <stdio.h>
#include <iostream>

const double t = 10e-6;
const double epsilon = 10e-9;
const int N = 2000;

void initialization(double **matrix, double **bmatrix, double **xmatrix, double **tempX) {

    *bmatrix = new double[N];
    for (int k = 0; k < N; ++k) {
        (*bmatrix)[k] = N + 1;
    }

    *xmatrix = new double[N];
    *tempX = new double[N];
    for (int j = 0; j < N; j++) {
        (*xmatrix)[j] = 0;
        (*tempX)[j] = 0;
    }

    *matrix = new double[N * N];
    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            (*matrix)[k * N + i] = k == i ? 2 : 1;
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
#pragma omp parallel for reduction(+:normB)
    for (int j = 0; j < N; ++j) {
        normB += bmatrix[j] * bmatrix[j];
    }
    normB = sqrt(normB);

    int f = true;
    while (f) {

        double sum = 0;

#pragma omp parallel for reduction(+:sum)
        for (int i = 0; i < N; ++i) {
            double valueX = 0;
            for (int j = 0; j < N; ++j) {
                valueX += matrix[i * N + j] * xmatrix[j];
            }
            valueX -= bmatrix[i];
            tempX[i] = xmatrix[i] - valueX * t;
            sum += valueX * valueX;
        }

        std::swap(xmatrix, tempX);

        sum = sqrt(sum);
        f = sum / normB >= epsilon;
    }

    double finishTime = omp_get_wtime();

    std::cout << "Threads: " << countThread << ", Time: " << (finishTime - startTime) << std::endl;

    bool answerCorrect = true;
    for (int j = 0; j < N; ++j) {
        if (fabs(xmatrix[j] - 1) >= epsilon) {
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

