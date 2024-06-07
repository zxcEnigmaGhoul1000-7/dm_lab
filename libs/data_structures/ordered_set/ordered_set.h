#ifndef COURSE_ORDERED_SET_H
#define COURSE_ORDERED_SET_H


#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../algorithms/array/array.h"


typedef struct ordered_array_set {
    int *data; // элементы множества
    size_t size; // количество элементов в множестве
    size_t capacity; // максимальное количество элементов в множестве
} ordered_array_set_t;

// возвращает пустое множество, в которое можно вставить capacity элементов
ordered_array_set_t ordered_array_set_create(size_t capacity);

// изменяет размер массива data до размера size и присваивает capacity размер множества
void ordered_array_set_shrinkToFit(ordered_array_set_t *set);

// возвращает множество, состоящее из элементов массива a размера size
ordered_array_set_t ordered_array_set_create_from_array(const int *a,
                                                        size_t size);

// возвращает значение позицию элемента в множестве,
// если значение value имеется в множестве set,
// иначе - size
size_t ordered_array_set_ind(ordered_array_set_t *set, int value);

// возращает true если элемент value имеется в множестве set, иначе false
bool ordered_array_set_isValueIn(ordered_array_set_t set, int value);

// возвращает значение ’истина’, если элементы множеств set1 и set2 равны
// иначе - ’ложь’
bool ordered_array_set_isEqual(ordered_array_set_t set1, ordered_array_set_t set2);

// возвращает значение ’истина’, если subset является подмножеством set
// иначе - ’ложь’
bool ordered_array_set_isSubset(ordered_array_set_t subset, ordered_array_set_t set);

// возбуждает исключение, если в множество по адресу set
// нельзя вставить элемент
void ordered_array_set_isAbleAppend(ordered_array_set_t *set);

// добавляет элемент value в множество set
void ordered_array_set_insert(ordered_array_set_t *set, int value);

// удаляет элемент value из множества set
void ordered_array_set_deleteElement(ordered_array_set_t *set, int value);

// возвращает объединение множеств set1 и set2
ordered_array_set_t ordered_array_set_union(ordered_array_set_t set1,
                                            ordered_array_set_t set2);

// возвращает пересечение множеств set1 и set2
ordered_array_set_t ordered_array_set_intersection(ordered_array_set_t set1,
                                                   ordered_array_set_t set2);

// возвращает разность множеств set1 и set2
ordered_array_set_t ordered_array_set_difference(ordered_array_set_t set1,
                                                 ordered_array_set_t set2);

// возвращает симметрическую разность множеств set1 и set2
ordered_array_set_t ordered_array_set_symmetricDifference(ordered_array_set_t set1,
                                                          ordered_array_set_t set2);

// возвращает дополнение до универсума universumSet множества set
ordered_array_set_t ordered_array_set_complement(ordered_array_set_t set,
                                                 ordered_array_set_t universumSet);

// вывод множества set
void ordered_array_set_print(ordered_array_set_t set);

// освобождает память, занимаемую множеством set
void ordered_array_set_delete(ordered_array_set_t *set);


#endif //COURSE_ORDERED_SET_H
