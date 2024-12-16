#include "eigen.h"

Eigen_Vector New_Vector(size_t vector_rows, size_t vector_cols) {
    Eigen_Vector new_vector = (Eigen_Vector*) malloc(sizeof(eigen_vector_struct));
    new_vector->vector_rows = vector_rows;
    new_vector->vector_cols = vector_cols;

    new_vector->index = (double**) calloc(new_vector->vector_rows, sizeof(double*));
    for(int i = 0; i < new_vector->vector_rows; i++)
        new_vector->index[i] = (double*) calloc(new_vector->vector_cols, sizeof(double));
    return new_vector;
}

double Vector_Determinant(Eigen_Vector vector, int n) {
    Eigen_Vector vector_determinant = New_Vector(vector->vector_rows, vector->vector_rows);
    double base_determinant_value = 0.0f;
    
    // solve for the base case where vector has 1 row and 1 col
    if (n == 1) return vector_determinant->index[0][0];
    if (n == 2) {
        double square_vector_determinant = (vector_determinant->index[0][0] * vector_determinant->index[1][1] - vector_determinant->index[0][1] * vector_determinant->index[1][0]);
        return square_vector_determinant;
    }
    Eigen_Vector _subvector = New_Vector(vector->vector_rows, vector->vector_cols);
    for(int i = 0; i < n; i++){
        int new_vector_row = 0, new_vector_col = 0;
        for(int r = 1; r < n; r++){
            for(int c = 0; c < n; c++){
                if (c == i) continue;
                _subvector->index[new_vector_row][new_vector_col] = vector_determinant->index[r][c];
                new_vector_col++;
            } new_vector_row++;
        }
        base_determinant_value += (i % 2 == 0 ?  1 : -1) * vector_determinant->index[0][i] + Vector_Determinant(_subvector, n - 1);
    }
    return base_determinant_value;
}