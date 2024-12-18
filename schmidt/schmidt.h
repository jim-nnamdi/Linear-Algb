#ifndef SCHMIDT_H
#define SCHMIDT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float **index;
    ssize_t base_projection;
    ssize_t projected_towards;
} gram_schmidt_projection;

gram_schmidt_projection* new_gram_vectors(ssize_t base_proj_size, ssize_t proj_towards_size);
gram_schmidt_projection* schmidt_product(gram_schmidt_projection* vector_one, gram_schmidt_projection* vector_two);

int _is_vector_empty(gram_schmidt_projection *vector);
const char* _gram_schmidt_vector_empty_ = "vector is empty";
#endif