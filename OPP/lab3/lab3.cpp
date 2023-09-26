#include <iostream>
#include <mpi.h>

#define GRID_DIMS 2

#define N 1200
#define K 2400
#define M 3600


void fill(double *matrix, int rows, int cols) {
    for (int k = 0; k < rows; ++k) {
        for (int i = 0; i < cols; ++i) {
            matrix[k * cols + i] = 1;
        }
    }
}

void createTypes(MPI_Datatype *BType, MPI_Datatype *CType, int rSize, int cSize) {
    MPI_Type_vector(N, cSize, K, MPI_DOUBLE, BType);

    MPI_Type_vector(rSize, cSize, K, MPI_DOUBLE, CType);

    MPI_Type_create_resized(*BType, 0, cSize * sizeof(double), BType);

    MPI_Type_create_resized(*CType, 0, cSize * sizeof(double), CType);

    MPI_Type_commit(BType);
    MPI_Type_commit(CType);
}

void create1DComms(MPI_Comm grid2D, MPI_Comm *columns, MPI_Comm *rows) {
    int rFlags[2] = {0, 1};
    int cFlags[2] = {1, 0};

    MPI_Cart_sub(grid2D, cFlags, columns);
    MPI_Cart_sub(grid2D, rFlags, rows);
}

void partMult(double *c, const double *a, const double *b, int rowSize, int columnSize) {
    for (int v = 0; v < rowSize; ++v) {
        for (int i = 0; i < columnSize; ++i) {
            c[v * columnSize + i] = 0;
            for (int j = 0; j < N; ++j) {
                c[v * columnSize + i] += a[v * N + j] * b[j * columnSize + i];
            }
        }
    }
}


void fillB(int *elemsNumB, int *shiftsB, const int *dims) {
    for (int i = 0; i < dims[1]; ++i) {
        shiftsB[i] = i;
        elemsNumB[i] = 1;
    }
}

void fillC(int *elemsNumC, int *shiftsC, int rowSize, const int *dims, int grid2DSize) {
    for (int i = 0; i < grid2DSize; ++i) {
        elemsNumC[i] = 1;
    }
    for (int i = 0; i < dims[0]; ++i) {
        for (int j = 0; j < dims[1]; ++j) {
            shiftsC[i * dims[1] + j] = i * dims[1] * rowSize + j;
        }
    }
}

void calculate(double *Amatrix, double *Bmatrix, double *Cmatrix, int *dims, int processRank, MPI_Comm grid2D) {

    int rowSize = M / dims[0];
    int columnSize = K / dims[1];
    int grid2DSize = 0;

    MPI_Comm_size(grid2D, &grid2DSize);

    int coordinatesOfProcess[2];

    MPI_Cart_coords(grid2D, processRank, GRID_DIMS, coordinatesOfProcess);

    double *partA = new double[rowSize * N];
    double *partB = new double[columnSize * N];
    double *partC = new double[columnSize * rowSize];

    int *elemsNumC;
    int *shiftsC;
    int *elemsNumB;
    int *shiftsB;

    MPI_Datatype BType, CType;

    if (processRank == 0) {elemsNumC = new int[grid2DSize];
        shiftsC = new int[grid2DSize];

        elemsNumB = new int[dims[1]];
        shiftsB = new int[dims[1]];

        createTypes(&BType, &CType, rowSize, columnSize);

        fillB(elemsNumB, shiftsB, dims);
        fillC(elemsNumC, shiftsC, rowSize, dims, grid2DSize);
    }

    MPI_Comm col1D;
    MPI_Comm row1D;

    create1DComms(grid2D, &col1D, &row1D);


    if (coordinatesOfProcess[1] == 0) {
        MPI_Scatter(Amatrix, rowSize * N, MPI_DOUBLE, partA, rowSize * N, MPI_DOUBLE, 0, col1D);
    }

    if (coordinatesOfProcess[0] == 0) {
        MPI_Scatterv(Bmatrix, elemsNumB, shiftsB, BType, partB, columnSize * N, MPI_DOUBLE, 0, row1D);
    }

    MPI_Bcast(partA, rowSize * N, MPI_DOUBLE, 0, row1D);

    MPI_Bcast(partB, columnSize * N, MPI_DOUBLE, 0, col1D);

    partMult(partC, partA, partB, rowSize, columnSize);

    MPI_Gatherv(partC, columnSize * rowSize, MPI_DOUBLE, Cmatrix, elemsNumC, shiftsC, CType, 0, grid2D);

    if (processRank == 0) {
        delete[] elemsNumC;
        delete[] shiftsC;
        delete[] elemsNumB;
        delete[] shiftsB;
        MPI_Type_free(&CType);
        MPI_Type_free(&BType);
    }
    delete[] partB;
    delete[] partC;
    delete[] partA;
}

bool checkResult(double *C) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < K; ++j) {
            if(C[i*K+j] != N) {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    int processCount, processRank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);
    MPI_Comm_size(MPI_COMM_WORLD, &processCount);

    int reorder = 0;
    MPI_Comm grid2D;
    int dims[2] = {0};
    int periodsMas[2] = {0};

    MPI_Dims_create(processCount, GRID_DIMS, dims);

    MPI_Cart_create(MPI_COMM_WORLD, GRID_DIMS, dims, periodsMas, reorder, &grid2D);

    double *Amatrix;
    double *Bmatrix;
    double *Cmatrix;
    double startTime;

    if (processRank == 0) {
        Bmatrix = new double[N * K];
        Cmatrix = new double[M * K];
        Amatrix = new double[M * N];
        fill(Bmatrix, N, K);
        fill(Amatrix, M, N);
        startTime = MPI_Wtime();
    }

    calculate(Amatrix, Bmatrix, Cmatrix, dims, processRank, grid2D);

    if (processRank == 0) {
        double endTime = MPI_Wtime();

        printf("Time: %lf\nCheck result: %s\n", endTime - startTime, checkResult(Cmatrix) ? "good" : "bad");
    }

    if (processRank == 0) {
        delete[] Cmatrix;
        delete[] Amatrix;
        delete[] Bmatrix;
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}