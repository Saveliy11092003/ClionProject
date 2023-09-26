#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <cmath>

const double t = 10e-6;
const double eps = 10e-9;
const int N = 2400;

void initialization(double **matrix, double **bmatrix, double **xmatrix, double **tempX) {

    *bmatrix = new double[N];
    for(int k = 0; k < N; ++k) {
        (*bmatrix)[k] = N + 1;
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

    int a = 1;

    while(a != 670) {

        double *x;
        double *tempX;
        double *matrix;
        double *b;


        initialization(&matrix, &b, &x, &tempX);

        double startTime = omp_get_wtime();

        double s = 0;
        double normB = 0;
        int f = 1;

#pragma omp parallel
        {

#pragma omp for schedule(auto)
            for (int k = 0; k < N; ++k) {
                normB += b[k] * b[k];
            }

#pragma omp single
            {
                normB = sqrt(normB);
            }

            while (f) {

#pragma omp for schedule(auto)
                for (int i = 0; i < N; ++i) {
                    double X = 0;
                    for (int j = 0; j < N; ++j) {
                        X += matrix[i * N + j] * x[j];
                    }
                    X -= b[i];
                    tempX[i] = x[i] - X * t;
                    s += X * X;
                }

#pragma omp single
                {
                    std::swap(x, tempX);

                    s = sqrt(s);
                    f = s / normB >= eps;
                    s = 0;
                }
            }
        }
        double finishTime = omp_get_wtime();

        std::cout << a << " " << "Threads: " << countThread << ", time: " << (finishTime - startTime) << std::endl;

        bool answerCorrect = true;
        for (int i = 0; i < N; ++i) {
            if (fabs(x[i] - 1) >= eps) {
                answerCorrect = false;
                break;
            }
        }
        std::cout << "Answer correct: " << answerCorrect << std::endl;

        delete[] b;
        delete[] matrix;
        delete[] tempX;
        delete[] x;

        if(a == 1){
            a=10;
        }else if(a == 10){
            a=20;
        }else if(a == 20){
            a=40;
        }else if(a == 40){
            a=100;
        }else if(a == 100){
            a=400;
        }else if(a == 400){
            a=600;
        }else if(a == 600){
            a=650;
        }else if(a == 650){
            a=670;
        }
    }

    return EXIT_SUCCESS;
}
