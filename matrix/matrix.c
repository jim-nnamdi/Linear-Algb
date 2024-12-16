#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Matrix NewMatrix(size_t num_rows, size_t num_cols) {
    Matrix new_matrix = (Matrix) malloc(sizeof(matrix_struct));
    new_matrix->num_rows = num_rows;
    new_matrix->num_cols = num_cols;

    new_matrix->index = (double **) calloc(new_matrix->num_rows, sizeof(double *));
    for(int i = 0; i < new_matrix->num_rows; i++)
        new_matrix->index[i] = (double *) calloc(new_matrix->num_cols, sizeof(double));
    return new_matrix;
}

Matrix AddMatrices(Matrix matrix_A, Matrix matrix_B) {
    if(IsEmpty(matrix_A)  || IsEmpty(matrix_B))
        fprintf(stderr, "Empty matrices");
    if(matrix_A->num_rows != matrix_B->num_rows || matrix_A->num_cols != matrix_B->num_cols) 
        fprintf(stderr, "N x N matrices needed for matrix addition");
    Matrix result_matrix = NewMatrix(matrix_A->num_rows, matrix_A->num_cols);
    for(int r = 0; r < matrix_A->num_rows; r++){
        for(int c = 0; c < matrix_A->num_cols; c++)
            result_matrix->index[r][c] = matrix_A->index[r][c] + matrix_B->index[r][c];
    }
    return result_matrix;
}

Matrix SubMatrices(Matrix matrix_A, Matrix matrix_B) {
    if(IsEmpty(matrix_A) || IsEmpty(matrix_B))
        fprintf(stderr, "One matrix is Empty");
    if(matrix_A->num_rows != matrix_B->num_rows || matrix_A->num_cols != matrix_B->num_cols)
        fprintf(stderr, "N x N matrix needed for matrix subtraction");
    Matrix result_matrix = NewMatrix(matrix_B->num_rows, matrix_B->num_cols);
    for(int r = 0; r < matrix_B->num_rows; r++) {
        for(int c = 0; c < matrix_B->num_cols; c++)
            result_matrix->index[r][c] = matrix_A->index[r][c] - matrix_B->index[r][c];
    }
    return result_matrix;
}

Matrix MultiplyMatrices(Matrix matrix_A, Matrix matrix_B){
    if(IsEmpty(matrix_A) || IsEmpty(matrix_B))
        fprintf(stderr, "One matrix is empty");
    if(matrix_A->num_rows != matrix_B->num_cols)
        fprintf(stderr, "m_A rows must have same dimensions as m_B cols");
    Matrix result_matrix = NewMatrix(matrix_A->num_rows, matrix_B->num_cols);
    for(int r = 0; r < matrix_A->num_rows; r++){
        for(int c = 0; c < matrix_B->num_cols; c++){
            int multiplication_sum = 0;
            for(int i =0; i < matrix_A->num_rows; i++)
                multiplication_sum += matrix_A->index[r][i] * matrix_B->index[i][c];
            result_matrix->index[r][c] = multiplication_sum;
        }
    }
    return result_matrix;
}

Matrix TransposeMatrices(Matrix matrix) {
    if(IsEmpty(matrix)) 
        fprintf(stderr, "One matrix is empty");
    Matrix transpose_result = NewMatrix(matrix->num_rows, matrix->num_cols);
    for(int r = 0; r < matrix->num_rows; r++){
        for(int c = 0; c < matrix->num_cols; c++)
            transpose_result->index[c][r] = matrix->index[r][c];
    }
    return transpose_result;
}

void FreeMatrix(Matrix *matrix) {
    if(!IsEmpty(*matrix)){
        for(int i = 0; i < (*matrix)->num_rows; i++)
            free((*matrix)->index[i]);
        free((*matrix)->index);
        free((*matrix));
        *matrix = NULL;
    }
}

int IsEmpty(Matrix matrix) {
    if(!matrix || matrix->num_rows <= 0 || matrix->num_rows <= 0)
        return 1;
    return 0;
}