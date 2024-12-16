#ifndef EIGEN_H
#define EIGEN_H

#include <stdio.h>

typedef struct {
    double **index;
    size_t vector_rows;
    size_t vector_cols;
} eigen_vector_struct;

typedef eigen_vector_struct* Eigen_Vector;

// public methods to access
Eigen_Vector New_Vector(size_t vector_rows, size_t vector_cols);
Eigen_Vector Vector_Cross_Product(Eigen_Vector vector);
Eigen_Vector Vector_Scalar_Mult(Eigen_Vector vector);
double Vector_Determinant(Eigen_Vector vector, int n);

// private methods abstracted
void _swap_vector_values(Eigen_Vector on_vector);
void _is_vector_empty(Eigen_Vector vector);

#endif