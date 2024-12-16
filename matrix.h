#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double** index;
    size_t num_rows;
    size_t num_cols;
} matrix_struct;

typedef matrix_struct* Matrix;

Matrix NewMatrix(size_t num_rows, size_t num_cols);
Matrix MultiplyMatrices(Matrix matrix_A, Matrix matrix_B);