#include "schmidt.h"

gram_schmidt_projection* new_gram_vectors(ssize_t base_proj_size, ssize_t proj_towards_size){
    gram_schmidt_projection* new_gram_schmidt = (gram_schmidt_projection *) malloc(sizeof(gram_schmidt_projection));
    new_gram_schmidt->base_projection = base_proj_size;
    new_gram_schmidt->projected_towards = proj_towards_size;

    new_gram_schmidt->index = (float **) calloc(new_gram_schmidt->base_projection, sizeof(float *));
    for(int i = 0; i < base_proj_size; i++)
        new_gram_schmidt->index[i] = calloc(new_gram_schmidt->projected_towards, sizeof(float));
    return new_gram_schmidt;
}

gram_schmidt_projection* schmidt_product(gram_schmidt_projection* vector_one, gram_schmidt_projection* vector_two) {
    if(_is_vector_empty(vector_one) || _is_vector_empty (vector_two))
        fprintf(stderr, _gram_schmidt_vector_empty_);
    if(vector_one->projected_towards != vector_two->base_projection) perror('0');
    gram_schmidt_projection* schmidt_product_new = new_gram_vectors(vector_one->projected_towards, vector_two->base_projection);
    for(size_t i = 0; i < vector_one->projected_towards; i++){
        for(size_t j = 0; j < vector_two->base_projection; j++){
            int _gram_schmidt_multiplier = 0;
            for(size_t nr = 0; nr < vector_one->base_projection; nr++)
                _gram_schmidt_multiplier += vector_one->index[i][nr] + vector_two->index[nr][j];
            schmidt_product_new->index[i][j] = _gram_schmidt_multiplier;
        }
    }
    return schmidt_product_new;
}

int _is_vector_empty(gram_schmidt_projection *vector){
    if(vector->base_projection <= 0 || vector->projected_towards <= 0) return 1;
    else return 0;
}