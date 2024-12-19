#ifndef EIGEN_H
#define EIGEN_H

#include <stdio.h>

typedef struct {
    double **index;
    size_t vector_rows;
    size_t vector_cols;
} eigen_vector_struct;

typedef struct {
    double a;
    double b;
    double c;
} eigen_vector_equation;

typedef eigen_vector_struct* Eigen_Vector;
typedef eigen_vector_equation* Eigen_Vector_Equation;

Eigen_Vector New_Vector(size_t vector_rows, size_t vector_cols);
Eigen_Vector Vector_Cross_Product(Eigen_Vector vector);
Eigen_Vector Vector_Scalar_Mult(Eigen_Vector vector, int scalar);
Eigen_Vector_Equation Vector_Determinant(Eigen_Vector vector, int n);
void PrintEigen_Vectors(Eigen_Vector vector);

void _swap_vector_values(Eigen_Vector on_vector);
int _is_vector_empty(Eigen_Vector vector);
const char* _empty_eigen_matrix = "eigen matrix is empty";
#endif