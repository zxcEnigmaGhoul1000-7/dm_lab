#ifndef COURSE_BITSET_H
#define COURSE_BITSET_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef struct bitset {
    uint32_t values; // множество
    uint32_t max_value; // максимальный элемент универсума
} bitset_t;

// возвращает пустое множество c универсумом 0, 1,..., max_value
bitset_t bitset_create(unsigned max_value);

void bitset_appendArray(int arr[], size_t size, bitset_t *set);

// возвращает значение ’истина’, если значение value имеется в множестве set
// иначе - ’ложь’
bool bitset_in(bitset_t set, unsigned int value);

// возвращает значение ’истина’, если множества set1 и set2 равны// иначе - ’ложь’
bool bitset_isEqual(bitset_t set1, bitset_t set2);

// возвращает значение ’истина’ если множество subset
// является подмножеством множества set, иначе - ’ложь’.
bool bitset_isSubset(bitset_t subset, bitset_t set);

// добавляет элемент value в множество set
void bitset_insert(bitset_t *set, unsigned int value);

// удаляет элемент value из множества set
void bitset_deleteElement(bitset_t *set, unsigned int value);

// возвращает объединение множеств set1 и set2
bitset_t bitset_union(bitset_t set1, bitset_t set2);

// возвращает пересечение множеств set1 и set2
bitset_t bitset_intersection(bitset_t set1, bitset_t set2);

// возвращает разность множеств set1 и set2
bitset_t bitset_difference(bitset_t minuend, bitset_t subtrahend);

// возвращает симметрическую разность множеств set1 и set2
bitset_t bitset_symmetricDifference(bitset_t set1, bitset_t set2);

// возвращает дополнение до универсума множества set
bitset_t bitset_complement(bitset_t set);

// вывод множества set
void bitset_print(bitset_t set);


#endif //COURSE_BITSET_H
