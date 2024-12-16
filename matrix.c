#include "matrix.h"

Matrix NewMatrix(size_t num_rows, size_t num_cols) {
    Matrix new_matrix = (Matrix)malloc(sizeof(matrix_struct));
    new_matrix->num_rows = num_rows;
    new_matrix->num_cols = num_cols;

    new_matrix->index = (double**) calloc(new_matrix->num_rows, sizeof(double *));
    for(int i = 0; i < num_rows; i++)
        new_matrix->index[i] = (double *)calloc(new_matrix->num_cols, sizeof(double *));
    return new_matrix;
}

Matrix MultiplyMatrices(Matrix matrix_A, Matrix matrix_B) {
    if(matrix_A->num_cols != matrix_B->num_rows)
        fprintf(stderr, "N x N matrix required for multiplication"); return NULL;
    Matrix result_matrix = NewMatrix(matrix_A->num_rows, matrix_B->num_cols);
    for(int i = 0; i < matrix_A->num_rows; i++){
        for(int j = 0; j < matrix_B->num_cols; j++){
            int multiplication_sum = 0;
            for(int m = 0; m < matrix_A->num_rows; m++)
                multiplication_sum += matrix_A->index[i][m] * matrix_B->index[m][j];
            result_matrix->index[i][j] = multiplication_sum;
        }
    }
    return result_matrix;
}