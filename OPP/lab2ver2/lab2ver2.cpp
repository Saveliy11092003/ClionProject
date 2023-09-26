#include <cmath>
#include <omp.h>
#include <stdio.h>
#include <iostream>

const double t = 10e-6;
const double epsilon = 10e-9;
const int N = 2001;

void initialization(double **matrix, double **bmatrix, double **xmatrix, double **tempX) {

    *bmatrix = new double[N];
    for(int i = 0; i < N; ++i) {
        (*bmatrix)[i] = N + 1;
    }

    *xmatrix = new double[N];
    *tempX = new double[N];

    for(int i; i < N; i++) {
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

    if(argc < 2) {
        std::cout << "Usage: Need arg!" << std::endl;
        return EXIT_FAILURE;
    }

    int countThread = 0;
    sscanf(argv[1], "%d", &countThread);
    omp_set_num_threads(countThread);

    double *x;
    double *tempX;
    double *matrix;
    double *b;


    initialization(&matrix, &b, &x, &tempX);

    double startTime = omp_get_wtime();

    double s = 0;
    double normB = 0;
    int f = true;

#pragma omp parallel
    {

#pragma omp for reduction(+:normB)
        for (int k = 0; k < N; ++k) {
            normB += b[k] * b[k];
        }

#pragma omp single
        {
            normB = sqrt(normB);
        }

        while (f) {

#pragma omp for reduction(+:s)
            for (int k = 0; k < N; ++k) {
                double X = 0;
                for (int j = 0; j < N; ++j) {
                    X += matrix[k * N + j] * x[j];
                }
                X -= b[k];
                tempX[k] = x[k] - X * t;
                s += X * X;
            }

#pragma omp single
            {
                std::swap(x, tempX);

                s = sqrt(s);
                f = s / normB >= epsilon;
                s = 0;
            }
        }
    }

    double finishTime = omp_get_wtime();

    std::cout << "Threads: " << countThread << ", Time: " << (finishTime - startTime) << std::endl;

    bool answerCorrect = true;
    for(int i = 0; i < N; ++i) {
        if(fabs(x[i] - 1) >= epsilon) {
            answerCorrect = false;
            break;
        }
    }
    std::cout << "Answer correct: " << answerCorrect << std::endl;

    delete[] b;
    delete[] matrix;
    delete[] tempX;
    delete[] x;

    return EXIT_SUCCESS;
}
