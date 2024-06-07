#include "vector_void.h"


vector_void_t createVectorV(size_t capacity, size_t base_type_size) {
    void *data = NULL;
    if (capacity != 0) {
        data = malloc(capacity * base_type_size);
        if (data == NULL) {
            MessageBox(GetActiveWindow(), "Fail memory allocated", "createVectorV", MB_ICONERROR);
            exit(1);
        }
    }

    return (vector_void_t) {
            data,
            0,
            capacity,
            base_type_size
    };
}


void reserveV(vector_void_t *v, size_t new_capacity) {
    v->capacity = new_capacity;

    if (v->capacity == 0) {
        free(v->data);
        v->data = NULL;
    } else {
        v->data = realloc(v->data, v->capacity * v->base_type_size);
        if (v->data == NULL) {
            MessageBox(GetActiveWindow(), "Fail memory allocated", "reserveV", MB_ICONERROR);
            exit(1);
        }
    }

    if (v->capacity < v->size)
        v->size = v->capacity;
}


void clearV(vector_void_t *v) {
    v->size = 0;
}


void shrinkToFitV(vector_void_t *v) {
    reserveV(v, v->size);
}


void deleteVectorV(vector_void_t *v) {
    reserveV(v, 0);
}


bool isEmptyV(vector_void_t v) {
    return v.size == 0;
}


bool isFullV(vector_void_t v) {
    return v.size == v.capacity;
}


void getVectorValueV(vector_void_t v, size_t i, void *destination) {
    if (i >= v.size ) {
        MessageBox(GetActiveWindow(), "Access error: going beyond the vector", "getVectorValueV", MB_ICONERROR);
        exit(1);
    }

    char *source = (char *) v.data + i * v.base_type_size;
    memcpy(destination, source, v.base_type_size);
}


void pushBackV(vector_void_t *v, void *px) {
    if (isFullV(*v)) {
        if (v->capacity == 0)
            reserveV(v, v->capacity + 1);
        else
            reserveV(v, v->capacity * 2);
    }
    char *destination = (char *) v->data + v->size++ * v->base_type_size;
    memcpy(destination, px, v->base_type_size);
}

void popBackV(vector_void_t *v) {
    if (isEmptyV(*v)) {
        MessageBox(GetActiveWindow(),
                   "Error: the vector is empty, it is impossible to delete the last element",
                   "popBackV", MB_ICONERROR);
        exit(1);
    } else
        v->size--;
}