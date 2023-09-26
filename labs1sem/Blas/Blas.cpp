#include <iostream>
#include <limits.h>
#include <time.h>
#include "mkl_cblas.h"
#include <math.h>

void CopyMatrix(float *A, float *B, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[i * n + j] = A[i * n + j];
}

void PrintMatrix(float *Matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%f ",Matrix[i * n + j]);
        }
        printf("\n");
    }
}

float UnitRate(float *Matrix, int n)
{
    float result = __FLT_MIN__;
    float sum = 0;
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            sum += fabs(Matrix[i * n + j]);
        }
        if (sum > result)
        {
            result = sum;
        }
        sum = 0;
    }
    return result;
}

float InfiniteRate(float *Matrix, int n)
{
    float result = 0;
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            sum += abs(Matrix[i * n + j]);
        }
        if (sum > result)
        {
            result = sum;
        }
        sum = 0;
    }
    return result;
}

float *TranspositionMatrix(float *Matrix, int n)
{
    float *MatrixResult = new float[n * n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            MatrixResult[j * n + i] = Matrix[i * n + j];
            int a = j * n + i;
            int b = i * n + j;
        }
    }
    return MatrixResult;
}

float *DivMatrix(float *Matrix1, float digit, int n)
{
    float *MatrixResult = new float[n * n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            MatrixResult[i * n + j] = Matrix1[i * n + j] / digit;
        }
    }
    return MatrixResult;
}

float *SubMatrix(float *Matrix1, float *Matrix2, int n)
{
    float *MatrixResult = new float[n * n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            MatrixResult[i * n + j] = Matrix1[i * n + j] - Matrix2[i * n + j];
        }
    }
    return MatrixResult;
}

void SumMatrix(float *Matrix1, float *Matrix2,float* MatrixResult, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            MatrixResult[i * n + j] = Matrix1[i * n + j] + Matrix2[i * n + j];
        }
    }
}

void FillMatrix(float *Matrix, int n)
{
    int number = 1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
           // scanf("%f", &Matrix[i*n+j]);
            Matrix[i * n + j] = number % 5;
            number += 1;
        }
    }
}

void InitializationMatrix(float *Matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Matrix[i * n + j] = 0;
        }
    }
}

void FillIdentityMatrix(float *Matrix, int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            Matrix[i * n + j] = 0;
            if (i == j)
            {
                Matrix[i * n + j] = 1;
            }
        }
    }
}

void InversionMatrix(float *Matrix, float *MatrixResult, int n, int m)
{
    float *MatrixRFix;
    float *MatrixB;
    float *MatrixIdentity = new float[n * n];
    FillIdentityMatrix(MatrixIdentity, n);

    float digit = UnitRate(Matrix, n) * InfiniteRate(Matrix, n);
    MatrixB = DivMatrix(TranspositionMatrix(Matrix, n), digit, n);

    float *Matrix1 = new float[n * n];
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1, MatrixB, n, Matrix, n, 0, Matrix1, n);
    MatrixRFix = SubMatrix(MatrixIdentity, Matrix1, n);

    float *MatrixC = new float[n * n];
    FillIdentityMatrix(MatrixC, n);

    float *MatrixR = new float[n * n];
    CopyMatrix(MatrixRFix, MatrixR, n);

    float *MatrixRCopy = new float[n * n];


    for (int i = 0; i < m; i++)
    {
        SumMatrix(MatrixC, MatrixR, MatrixC, n);
        CopyMatrix(MatrixR, MatrixRCopy, n);
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1, MatrixRCopy, n, MatrixRFix, n, 0, MatrixR, n);
    }
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1, MatrixC, n, MatrixB, n, 0, MatrixResult, n);
    delete [] MatrixRFix;
    delete [] MatrixB;
    delete [] MatrixIdentity;
    delete [] Matrix1;
    delete [] MatrixC;
    delete [] MatrixR;
    delete [] MatrixRCopy;
}

int main()
{
    int n, m;
    printf("Введите размер матрицы: ");
    scanf("%d", &n);
    printf("\n");
    printf("Введите количество членов ряда: ");
    scanf("%d", &m);
    float *Matrix;
    Matrix = new float[n * n];
    FillMatrix(Matrix,n);
    float *MatrixResult;
    MatrixResult = new float[n * n];

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    InversionMatrix(Matrix, MatrixResult,n,m);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    printf("Время: %lf секунд.\n",
           end.tv_sec - start.tv_sec + 0.000000001 * (end.tv_nsec - start.tv_nsec));

    float *Matrix2 = new float[n * n];
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1, Matrix, n, MatrixResult, n, 0, Matrix2, n);
    printf("%f", UnitRate(Matrix2, n));
    delete [] MatrixResult;
    delete [] Matrix;
    delete [] Matrix2;
    return 0;
}