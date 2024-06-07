#ifndef CODE_ARRAY_H
#define CODE_ARRAY_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

// осуществляет ввод массива arr размера size
void inputArray_(int arr[], size_t size);

//осуществляет вывод массива arr размера size
void outputArray_(const int arr[], size_t size);

// возвращает индекс первого совпадения с числом x в массиве а размера n, а если совпадений нет возвращает n
size_t getFirstIndexOfNumber_(const int *const a, const size_t n, const int x);

// возвращает true если число находится в массиве, иначе false
bool isValueInArr( const int arr[], const size_t size, const int value);

// возвращает true если число является простым, иначе false
bool isPrime_(int x);

// возвращает индекс первого значения, удовлетворяющего функции предикату в массиве a размера n, если такового не имеется то n
size_t getFirstIndexOfNumByPredicate_(const int *const a, const size_t n, bool (*predicate)(int));

// возвращает индекс последнего удовлетворяющего функции предикату в массиве a размера n, если такового не имеется то n
size_t getLastIndexOfNumByPredicate_(const int *const a, const int n, bool (*predicate)(int));

// возвращает количество элементов массива a размера n, удовлетворяющих функции предикату
size_t countOfNumsSatisfiesPredicate_(const int *const a, const size_t n, bool (*predicate)(int));

// изменяет порядок элементов массива a размера n на обратный
void expandArray_(int *const a, const size_t n);

// возвращает значение 'true' если массив а размера n является палиндромом, иначе - 'false'
bool isPalindromeSequence_(const int *const a, const size_t n);

// обменивает между собой два элемента массива по индексам
void swapElemArr(int arr[], size_t i1, size_t i2);

// cортирует массив a размера n по возрастанию выбором
void selectionSortArray_(int *const a, const size_t n);

// осуществляет вставку элемента value в массив a размера n по индексу index
void insertElem_(int *a, size_t *size, const size_t index, const int value);

// добавляет в конец массива а размера по указателю *n элемент value
void appendElem_(int *a, size_t *n, int value);

// удаляет элемент по индексу index из массива a размера по указателю *n с сохранением относительного порядка других элементов
void deleteByIndexAndSaveOrder_(int *a, size_t *n, const size_t index);

// удаляет элемент по индексу index из массива a размера по указателю *n с без сохранения относительного порядка других элементов
void deleteByIndexAndNotSaveOrder_(int *a, size_t *n, const size_t index);

// осуществляет циклический сдвиг массива a размера n на k элементов влево
void cyclicArrayShift_(int *a, size_t const n, size_t const k);

//применяет функцию f ко всем элементам массива a размера size
void forEach_(int *a, const int size, int (*f)(int));

//возвращает значение 'true', если хотя бы один элемент массива a размера size удовлетворяет функции-предикату, иначе - 'false'
bool any_(const int *a, const int size, bool (*predicate)(int));

//возвращает значение 'true', если все элементы массива a размера size удовлетворяют функции-предикату, иначе - 'false'
bool all_(const int *a, const int size, bool (*predicate)(int));

//сохраняет элементы массива a размера len_a в массиве b размера по указателю *len_b если они удовлетворяют функции предикату,
//а иначе в массиве c размера по указателю *len_c
void arraySplit_(int *a, const size_t len_a, int *b, size_t *len_b, int *c, size_t *len_c, bool (*predicate)(int));

// возвращает позицию последнюю позицию вхождения элемента меньшего x
// в отсортированном массиве a размера n при его наличии, иначе - n
size_t binarySearchLower_(const int arr[], size_t size, int value);

// возвращает позицию вхождения элемента x
// в отсортированном массиве a размера n при его наличии, иначе - n
size_t binarySearch_(const int *a, const size_t n, int x);

// возвращает позицию первого элемента равного или большего x в отсортированном массиве a размера n
// при отсутствии такого элемента возвращает n
size_t binarySearchMoreOrEqual_(const int *a, const size_t n, int x);

// возвращает количество элементов массива, удовлетворяющих условию функции - предиката
int countIf_(const int *const a, const size_t n, int (*predicate)(int));

// удаляет из массива элементы, удовлетворяющие условию функции - предиката, записывает в n новый размер массива
void deleteIf_(int *const a, size_t *const n, int (*deletePredicate)(int));




#endif //CODE_ARRAY_H
