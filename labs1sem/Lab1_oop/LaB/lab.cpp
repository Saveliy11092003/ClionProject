#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mkl_cblas.h"
#include <iostream>

typedef float* matrix;
static matrix I;
static int N;

matrix constructMatrix() {
    matrix newMatrix = (matrix)malloc(sizeof(float) * N * N);
    return newMatrix;
}

void printMatrix(const matrix X) {
    printf("\n");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf( "%f ", X[i * N + j]);
        }
        printf("\n");
    }
    printf("\n");
}

float findMaxLineSum(matrix A) {
    float sum = 0, maxSum = 0;
    matrix line;
    for (int i = 0; i < N; ++i, sum = 0) {
        line = A + i * N;
        for (int j = 0; j < N; ++j) {
            sum += line[j];
        }
        if (sum > maxSum || i == 0) {
            maxSum = sum;
        }
    }
    return maxSum;
}

float findMaxCollumnSum(matrix A) {
    float sum = 0, maxSum = 0;
    matrix column;
    for (int j = 0; j < N; ++j, sum = 0) {
        column = A + j;
        for (int i = 0; i < N; ++i) {
            sum += column[i * N];
        }
        if (sum > maxSum || j == 0) {
            maxSum = sum;
        }
    }
    return maxSum;
}

void divideMatrixByNum(matrix A, float num) {
    matrix line = A;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            line[j] /= num;
        }
        line += N;
    }
}

void matrixMul(const matrix Y, const matrix X, matrix res) {
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1, Y, N, X, N, 0, res, N);
}

void evaluate(matrix Y, const matrix X) {
    matrix xLine, yLine;
    for (int i = 0; i < N; ++i) {
        xLine = X + i * N;
        yLine = Y + i * N;
        for (int j = 0; j < N; ++j) {
            *(yLine + j) = *(xLine + j);
        }
    }
}

void matrixSumAndEq(matrix Y, const matrix X) {
    cblas_saxpy(N*N, 1.0, X, 1, Y, 1);
}

matrix findB(const matrix A) {
    matrix B = constructMatrix();
    evaluate(B, A);
    divideMatrixByNum(B, findMaxCollumnSum(A));
    divideMatrixByNum(B, findMaxLineSum(A));
    return B;
}

matrix findR(const matrix A, const matrix B) {
    matrix R = constructMatrix();
    matrix A0 = constructMatrix();
    evaluate(A0, A);
    matrixMul(B, A0, R);
    divideMatrixByNum(R, -1);
    matrixSumAndEq(R, I);
    free(A0);
    return R;
}

void fillWithZero(matrix X) {
    matrix line;
    for (int i = 0; i < N; ++i) {
        line = X + i * N;
        for (int j = 0; j < N; ++j) {
            *(line + j) = 0;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("wrong input");
    }
    N = atoi(argv[1]);
    int M = atoi(argv[2]);

    matrix A = constructMatrix();
    for (int i = 1; i <= N * N; ++i) {
        A[i - 1] = i;
        A[i - 1] /= 10;
    }
    I = constructMatrix();
    fillWithZero(I);
    for (int i = 0; i < N; ++i) {
        I[i + N * i] = 1;
    }

    matrix B = findB(A);
    matrix R = findR(A, B);
    matrix R0[2];
    R0[0] = constructMatrix();
    R0[1] = constructMatrix();
    evaluate(R0[1], I);
    matrix A0 = constructMatrix();
    evaluate(A0, I);
    struct timespec mt1, mt2;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &mt1);
    for (int i = 0; i < M; ++i) {
        matrixMul(R0[(i + 1) % 2], R, R0[i % 2]);
        matrixSumAndEq(A0, R0[i % 2]);
    }
    matrixMul(A0, B, A);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &mt2);
    printf("\n%d %d %d\n", mt2.tv_sec, mt1.tv_sec, (mt2.tv_sec-mt1.tv_sec));
    free(A);
    free(B);
    free(R);
    free(A0);
    free(R0[0]); free(R0[1]);
}