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
    if(_is_empty(matrix_A)  || _is_empty(matrix_B))
        fprintf(stderr, _empty_matrix);
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
    if(_is_empty(matrix_A) || _is_empty(matrix_B))
        fprintf(stderr, _empty_matrix);
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
    if(_is_empty(matrix_A) || _is_empty(matrix_B))
        fprintf(stderr, _empty_matrix);
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
    if(_is_empty(matrix)) 
        fprintf(stderr, "matrix is empty");
    Matrix transpose_result = NewMatrix(matrix->num_rows, matrix->num_cols);
    for(int r = 0; r < matrix->num_rows; r++){
        for(int c = 0; c < matrix->num_cols; c++)
            transpose_result->index[c][r] = matrix->index[r][c];
    }
    return transpose_result;
}

Matrix ScalarMatrix(Matrix scala_matrix, int scalar) {
    Matrix scalar_matrix = NewMatrix(scala_matrix->num_rows, scala_matrix->num_cols);
    for(int r = 0; r < scala_matrix->num_rows; r++){
        for(int c = 0; c < scala_matrix->num_cols; c++)
            scalar_matrix->index[r][c] *= scalar;
    }
    return scalar_matrix;
}

Matrix InverseMatrices(Matrix matrix) {
     if(_is_empty(matrix))
        fprintf(stderr, "matrix is empty");
    /*
     1
     ---        | d -b |
     a.d - b.c  | -c a |
     det(A) = (a.d - b.c)
    */
   Matrix inverse_matrix = NewMatrix(matrix->num_rows, matrix->num_cols);
   float scalar_determinant = 1/(Determinant(matrix, matrix->num_rows));
   
   // if matrix is a 2 by 2 matrix then swap [0][0] and [1][1]
   // and then add negative signs to [0][1] and [1][0]
   Matrix swapped_matrix = _swap_matrix_indices(matrix);
   Matrix m_final_inverse = ScalarMatrix(swapped_matrix,(int)scalar_determinant);
   return m_final_inverse;
}

float Determinant(Matrix matrix, int n) {
    if(_is_empty(matrix))
        fprintf(stderr, "matrix is empty");
    float det = 0.0f;
    
    //det(A) = (a.d - b.c)
    if(n == 1) return (float) matrix->index[0][0];
    if(n == 2) {
        double m_determinant = matrix->index[0][0] * matrix->index[1][1] - 
        matrix->index[0][1] * matrix->index[1][0] ; 
        return m_determinant;
    }
    
    /*
        | 2 3 4 |
        | 5 6 7 | 
        | 8 9 1 |

        Find the determinant (det(A)) by
        creating submatrices by omitting the first row
        and the first column at indices [0][0]

        2 | 6 7 | recall (a.d - b.c) submatrix determinant
          | 9 1 |        (6.1 - 7.9 = 6 - 63 = -57 . 2 = 114)
    */
    Matrix submatrix = NewMatrix(matrix->num_rows, matrix->num_cols);
    for(int i = 0; i < n; i++) {
        int subi = 0, subj = 0;
        for(int r = 1; r < n; r++){
            for(int c = 0; c < n; c++){
                if(c == i) continue;
                 /* 
                    skip the column of the chosen row to work.
                    for submatrices generation this is the part
                    of the matrix to be cancelled out from the data.
                        | 2 3 4 |
                        | 5 * * |
                        | 8 * * |
                */
                submatrix->index[subi][subj] = matrix->index[r][c]; subj++;
            } 
            subi++;
        }

        det += (i % 2 == 0 ? 1 : -1) * matrix->index[0][i] * Determinant(submatrix, n - 1);
    }
    return det;
}

void _free_matrix(Matrix *matrix) {
    if(!_is_empty(*matrix)){
        for(int i = 0; i < (*matrix)->num_rows; i++)
            free((*matrix)->index[i]);
        free((*matrix)->index);
        free((*matrix));
        *matrix = NULL;
    }
}

Matrix _swap_matrix_indices(Matrix matrix) {
    Matrix _new_swap_matrix = NewMatrix(2, 2);
    size_t _new_swap_temp = _new_swap_matrix->index[0][0];
    _new_swap_matrix->index[0][0] = _new_swap_matrix->index[1][1];
    _new_swap_matrix->index[1][1] = _new_swap_temp;

    _new_swap_matrix->index[0][1] = -_new_swap_matrix->index[0][1];
    _new_swap_matrix->index[1][0] = -_new_swap_matrix->index[1][0];
    return _new_swap_matrix;
} 

int _is_empty(Matrix matrix) {
    if(!matrix || matrix->num_rows <= 0 || matrix->num_rows <= 0)
        return 1;
    return 0;
}