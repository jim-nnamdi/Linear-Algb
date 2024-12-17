#ifndef MATRIX_H
#define MATRIX_H

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
Matrix InverseMatrices(Matrix matrix);
Matrix TransposeMatrices(Matrix matrix);
float Determinant(Matrix matrix, int n);
Matrix ScalarMatrix(Matrix matrix, int scalar);
void PrintMatrix(Matrix matrix);

Matrix _swap_matrix_indices(Matrix matrix);
int _is_empty(Matrix matrix);
void _free_matrix(Matrix *matrix);
void _swap_values(double *value_one, double *value_two);

const char* _empty_matrix = "cannot work with an empty matrix\n";

#endif