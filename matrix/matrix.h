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
Matrix AddMatrices(Matrix matrix_A, Matrix matrix_B);
Matrix SubMatrices(Matrix matrix_A, Matrix matrix_B);
Matrix MultiplyMatrices(Matrix matrix_A, Matrix matrix_B);
Matrix InverseMatrices(Matrix matrix, int n);
Matrix TransposeMatrices(Matrix matrix);

int IsEmpty(Matrix matrix);
void FreeMatrix(Matrix *matrix);
void SwapValues(double *value_one, double *value_two);