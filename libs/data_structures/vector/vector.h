#ifndef COURSE_VECTOR_H
#define COURSE_VECTOR_H

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <memory.h>
#include <windows.h>
#include "../../algorithms/array/array.h"

typedef struct vector {
    int *data; // указатель на элементы вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
} vector_t;

// возвращает вектор вместимости capacity и размером size 0
vector_t createVector(size_t capacity);

// изменяет количество памяти, выделенное под хранение элементов вектора
void reserve(vector_t *v, size_t new_capacity);

// удаляет элементы из контейнера, но не освобождает выделенную память
void clear(vector_t *v);

//  освобождает память, выделенную под неиспользуемые элементы
void shrinkToFit(vector_t *v);

// освобождает память, выделенную вектору и приравнивает указателю на массив data NULL,
// размеру и вместимости size и capacity соответственно нули
void deleteVector(vector_t *v);

// возвращает true, если вектор пуст, иначе false
bool isEmpty(vector_t v);

// возвращает true, если вектор заполнен, иначе false
bool isFull(vector_t v);

// которая возвращает i-ый элемент вектора v
int getVectorValue(vector_t v, size_t i);

// добавляет элемент x в конец вектора v
void pushBack(vector_t *v, int x);

// удаляет последний элемент вектора
void popBack(vector_t *v);

// возвращает указатель на index-ый элемент вектора, а в случае если элемента с таким индексом
// не существует - NULL
int *atVector(vector_t *v, size_t index);

// возвращает указатель на последний элемент вектора
int *back(vector_t *v);

// возвращает указатель на нулевой элемент вектора
int *front(vector_t *v);

// осуществляет вывод вектора в консоль
void printVector(vector_t v);

#endif //COURSE_VECTOR_H
