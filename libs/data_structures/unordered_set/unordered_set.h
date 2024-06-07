//изменить по надобности действие при ошибке выделения памяти

#ifndef COURSE_UNORDERED_SET_H
#define COURSE_UNORDERED_SET_H


#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../algorithms/array/array.h"

typedef struct unordered_array_set {
    int *data; // элементы множества
    size_t size; // количество элементов в множестве
    size_t capacity; // максимальное количество элементов в множестве
} unordered_array_set_t;

// возвращает пустое множество для capacity элементов
unordered_array_set_t unordered_array_set_create(size_t capacity);

// изменяет размер массива data до размера size и присваивает capacity размер множества
void unordered_array_set_shrinkToFit(unordered_array_set_t *set);

// возвращает множество, состоящее из элементов массива arr размера arr_size
unordered_array_set_t unordered_array_set_create_from_array(
        const int *arr, size_t arr_size
);

// возвращает позицию элемента в множестве,
// если значение value имеется в множестве set, иначе - n
size_t unordered_array_set_ind(unordered_array_set_t set, int value);

// возвращает true если value имеется в множестве set, иначе false
bool unordered_array_set_isValueIn(unordered_array_set_t set, int value);

// возвращает true если subset является подмножеством множества set,
// иначе false
bool unordered_array_set_isSubset(
        unordered_array_set_t subset,
        unordered_array_set_t set
);


// возвращает значение ’истина’, если элементы множеств set1 и set2 равны
// иначе - ’ложь’
bool unordered_array_set_isEqual(
        unordered_array_set_t set1,
        unordered_array_set_t set2
);

// возбуждает исключение, если в множество по адресу set
// нельзя вставить элемент
void unordered_array_set_isAbleAppend(unordered_array_set_t *set);

// добавляет элемент value в множество set
void unordered_array_set_insert(unordered_array_set_t *set, int value);

// удаляет элемент value из множества set
void unordered_array_set_deleteElement(
        unordered_array_set_t *set,
        int value
);

// возвращает объединение множеств set1 и set2.
unordered_array_set_t unordered_array_set_union(
        unordered_array_set_t set1,
        unordered_array_set_t set2
);

// возвращает пересечение множеств set1 и set2
unordered_array_set_t unordered_array_set_intersection(
        unordered_array_set_t set1,
        unordered_array_set_t set2
);

// возвращает разность множеств set1 и set2
unordered_array_set_t unordered_array_set_difference(
        unordered_array_set_t set1,
        unordered_array_set_t set2
);


// возвращает дополнение до универсума множества set25
unordered_array_set_t unordered_array_set_complement(
        unordered_array_set_t set,
        unordered_array_set_t universumSet
);

// возвращает симметрическую разность множеств set1 и set2
unordered_array_set_t unordered_array_set_symmetricDifference(
        unordered_array_set_t set1,
        unordered_array_set_t set2
);

// вывод множества set
void unordered_array_set_print(unordered_array_set_t set);

// освобождает память, занимаемую множеством set
void unordered_array_set_delete(unordered_array_set_t *set);

#endif //COURSE_UNORDERED_SET_H
