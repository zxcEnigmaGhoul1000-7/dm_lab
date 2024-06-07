#ifndef COURSE_VECTOR_VOID_H
#define COURSE_VECTOR_VOID_H

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <memory.h>
#include <windows.h>
#include "../../algorithms/array/array.h"

typedef struct vector_void {
    void *data; // указатель на нулевой элемент вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
    size_t base_type_size; // размер базового типа:
} vector_void_t;


// возвращает вектор вместимости capacity и размером size 0
vector_void_t createVectorV(size_t capacity, size_t base_type_size);

// изменяет количество памяти, выделенное под хранение элементов вектора
void reserveV(vector_void_t *v, size_t new_capacity);

// удаляет элементы из контейнера, но не освобождает выделенную память
void clearV(vector_void_t *v);

//  освобождает память, выделенную под неиспользуемые элементы
void shrinkToFitV(vector_void_t *v);

// освобождает память, выделенную вектору и приравнивает указателю на массив data NULL,
// размеру и вместимости size и capacity соответственно нули
void deleteVectorV(vector_void_t *v);

// возвращает true, если вектор пуст, иначе false
bool isEmptyV(vector_void_t v);

// возвращает true, если вектор заполнен, иначе false
bool isFullV(vector_void_t v);

// записывает по адресу destination i-ый элемент вектора v
void getVectorValueV(vector_void_t v, size_t i, void *destination);

// добавляет элемент по указателю *x в конец вектора v
void pushBackV(vector_void_t *v, void *x);

// удаляет последний элемент вектора
void popBackV(vector_void_t *v);

// возвращает указатель на index-ый элемент вектора, а в случае если элемента с таким индексом
// не существует - NULL
int *atVectorV(vector_void_t *v, size_t index);

// возвращает указатель на последний элемент вектора
int *backV(vector_void_t *v);

// возвращает указатель на нулевой элемент вектора
int *frontV(vector_void_t *v);


#endif //COURSE_VECTOR_VOID_H
