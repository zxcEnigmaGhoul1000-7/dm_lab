#ifndef STR_STRING_LIBRARY_H
#define STR_STRING_LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>

// возвращает количество символов в строке не считая ноль-символ
size_t strlen_(char *begin);

// возвращает указатель на первый элемент с кодом ch, расположенным на ленте памяти между
//адресами begin и end не включая end. Если символ не найден, возвращается значение end
char* find(char *begin, char *end, int ch);

// возвращает указатель на первый символ, отличный от пробельных,
// расположенный на ленте памяти, начиная с begin и заканчивая ноль-символом.
// Если символ не найден, возвращается адрес первого ноль-символа
char* findNonSpace(char *begin);

// возвращает указатель на первый пробельный символ,
// расположенный на ленте памяти начиная с адреса begin
// или на первый ноль-символ
char* findSpace(char *begin);

// возвращает указатель на первый справа символ, отличный от пробельных,
// расположенный на ленте памяти, начиная с rbegin (последний символ
// строки, за которым следует ноль-символ) и заканчивая rend (адрес символа перед началом строки).
// Если символ не найден, возвращается адрес rend.
char* findNonSpaceReverse(char *rbegin, const char *rend);

//  возвращает указатель на первый пробельный символ справа, расположенный на ленте памяти,
//  начиная с rbegin и заканчивая rend. Если символ не найден, возвращается адрес rend.
char* findSpaceReverse(char *rbegin, const char *rend);

// возвращает отрицательное значение, если lhs располагается до rhs
// в лексикографическом порядке (как в словаре), значение 0, если lhs и rhs
// равны, иначе – положительное значение.
int strcmp_(const char *lhs, const char *rhs);

// записывает по адресу begin_destination
// фрагмент памяти, начиная с адреса begin_source до end_source.
// Возвращает указатель на следующий свободный фрагмент памяти в destination
char* copy(const char *begin_source, const char *end_source,
           char *begin_destination);

// записывает по адресу begin_destination элементы из фрагмента памяти начиная с begin_source
// заканчивая end_source, удовлетворяющие функции-предикату f. Функция возвращает
// указатель на следующий свободный для записи фрагмент в памяти.
char* copyIf(char *begin_source, const char *end_source,
             char *begin_destination, int (*f)(int));

// записывает по адресу begin_destination элементы из фрагмента памяти
// начиная с rbegin_source заканчивая rend_source, удовлетворяющие функции-предикату f.
// Функция возвращает значение begin_destination по окончанию работы функции.
char* copyIfReverse(char *rbegin_source, const char *rend_source,
                    char *begin_destination, int (*f)(int));

// функция обработки ошибок
void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName, int line);

#define ASSERT_STRING(expected, got) assertString(expected, got, __FILE__, \
__func__, __LINE__)

#endif //STR_STRING_LIBRARY_H
