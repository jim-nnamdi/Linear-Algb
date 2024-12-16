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

Eigen_Vector Vector_Determinant(Eigen_Vector vector, int n) {
    if(_is_vector_empty(vector)) fprintf(stderr,_empty_eigen_matrix);
    Eigen_Vector vector_determinant = New_Vector(vector->vector_rows, vector->vector_rows);
    double base_determinant_value = 0.0f;
    
    // solve for the base case where vector has 1 row and 1 col
    if (n == 1) return vector_determinant;
    if (n == 2) {
        double first_row_determinant = (vector_determinant->index[0][0] * vector_determinant->index[1][1]);
        double second_row_determinant = (vector_determinant->index[0][1] * vector_determinant->index[1][0]);
        Eigen_Vector new_eigen_vector_determinant = New_Vector(first_row_determinant, second_row_determinant);
        return new_eigen_vector_determinant;
    }
    Eigen_Vector _subvector_eigen_determinant = New_Vector(vector->vector_rows, vector->vector_cols);
    for(int i = 0; i < n; i++){
        int new_vector_row = 0, new_vector_col = 0;
        for(int r = 1; r < n; r++){
            for(int c = 0; c < n; c++){
                if (c == i) continue;
                _subvector_eigen_determinant->index[new_vector_row][new_vector_col] = vector_determinant->index[r][c];
                new_vector_col++;
            } new_vector_row++;
        }
    }
    // the determinant of a vector has to be a new vector
    // which is regarded perpendicular to the previous vectors;
    return _subvector_eigen_determinant;
}

Eigen_Vector Vector_Cross_Product(Eigen_Vector vector) {
    /*
        a = 3i + 4j + 5k
        b = 2i + 6j + 8k
        a x b = | i j k |
                | 3 4 5 |
                | 2 6 8 |
        find the determinant of the vector matrix
        and then generate a new vector (c) which
        is perpendicular to the ¬ a and ¬ b
    */
    if(_is_vector_empty(vector)) fprintf(stderr,_empty_eigen_matrix);
    Eigen_Vector vector_cproduct = New_Vector(vector->vector_rows, vector->vector_cols);
    Eigen_Vector cross_product_det = Vector_Determinant(vector_cproduct, (vector_cproduct->vector_rows * vector_cproduct->vector_cols));
    return cross_product_det;
}

Eigen_Vector Eigen_Value_Computation(Eigen_Vector *computational_vector) {
    /*
    Av = λv
    Av - λv = 0 -> v(A - λ) = 0
    Av = λIv    -> Av - λIv = 0 -> v(A - λI) = 0 

    A =     | 3 -1 |   
            | 2  4 |

   A-λI =   | 3 - λ   -1 | 
            | 2     4- λ |

    (3 - λ)(4 - λ) - ( -1 . 2) = 0 
    [12 - 3λ - 4λ + λ^2 - 2] = 0
    [12 - 3λ - 4λ + λ^2 - 2] = 0
    12 -7λ + λ^2 - 2 = 0
    λ^2 - 7λ + 10 = 0
*/
}

int _is_vector_empty(Eigen_Vector vector) {
    if (vector->vector_rows <= 0 || vector->vector_cols <= 0) return 1;
    else return 0;
}