#include "vector.h"


vector_t createVector(size_t capacity) {
    int *data = NULL;
    if (capacity != 0) {
        data = (int *) malloc(capacity * sizeof(int));
        if (data == NULL) {
            MessageBox(GetActiveWindow(), "Fail memory allocated", "createVector", MB_ICONERROR);
            exit(1);
        }
    }

    return (vector_t) {
        data,
        0,
        capacity
    };
}



void reserve(vector_t *v, size_t new_capacity) {
    v->capacity = new_capacity;

    if (v->capacity == 0) {
        free(v->data);
        v->data = NULL;
    } else {
        v->data = (int *) realloc(v->data, v->capacity * sizeof(int));
        if (v->data == NULL) {
            MessageBox(GetActiveWindow(), "Fail memory allocated", "reserve", MB_ICONERROR);
            exit(1);
        }
    }

    if (v->capacity < v->size)
        v->size = v->capacity;
}


void clear(vector_t *v) {
    v->size = 0;
}


void shrinkToFit(vector_t *v) {
    reserve(v, v->size);
}


void deleteVector(vector_t *v) {
    reserve(v, 0);
}


bool isEmpty(vector_t v) {
    return v.size == 0;
}


bool isFull(vector_t v) {
    return v.size == v.capacity;
}


int getVectorValue(vector_t v, size_t i) {
    if (i >= v.size ) {
        MessageBox(GetActiveWindow(), "Access error: going beyond the vector", "getVectorValue", MB_ICONERROR);
        exit(1);
    }
    return v.data[i];
}


void pushBack(vector_t *v, int x) {
    if (isFull(*v)) {
        if (v->capacity == 0)
            reserve(v, v->capacity + 1);
        else
            reserve(v, v->capacity * 2);
    }

    v->data[v->size++] = x;
}


void popBack(vector_t *v) {
    if (isEmpty(*v)) {
        MessageBox(GetActiveWindow(),
                   "Error: the vector is empty, it is impossible to delete the last element",
                   "popBack", MB_ICONERROR);
        exit(1);
    } else
        v->size--;
}


int *atVector(vector_t *v, size_t index) {
    if (index >= v->size) {
        fprintf(stderr, "IndexError: a[%llu] is not exists", index);
        return NULL;
    }

    return &v->data[index];
}


int *back(vector_t *v) {
    return &v->data[v->size - 1];
}


int *front(vector_t *v) {
    return v->data;
}


void printVector(vector_t v) {
    outputArray_(v.data, v.size);
}