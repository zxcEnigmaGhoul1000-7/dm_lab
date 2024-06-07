#ifndef COURSE_TASKS_H
#define COURSE_TASKS_H

#include <stdio.h>
#include <stdint.h>
#include <float.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include "../libs/data_structures/matrix/matrix.h"
#include "../libs/algorithms/array/array.h"
#include "../libs/data_structures/vector/vector_void.h"
#include "../libs/algorithms/string/tasks/tasks.h"

#define MAX_STR_SIZE 100
#define MAX_STR_NUM 20
#define MAX_POLYNOMIAL_NUM 100
#define MAX_NAME_SIZE 30
#define MAX_COMMODITY_SIZE


// В текстовом файле хранятся целочисленные квадратные матрицы
//следующим образом: сначала целое число n – порядок матрицы, а
//затем ее элементы по строкам. Преобразовать файл так, чтобы
//элементы матрицы хранились по столбцам.
void task_01(char *full_filepath);

typedef struct arr_of_double {
    double *values_of_mantissa;
    int *values_of_order;
    size_t n_values;
    size_t size_of_malloc;
}arr_of_double_t;


void handleFileOpeningFail(FILE *file, char *filepath);


// В текстовом файле записаны вещественные числа в форме с
//фиксированной точкой. Преобразовать файл, представив каждое
//число в форме с плавающей точкой, сохранив две цифры после точки
//в мантиссе.
void task_02(char *full_filepath);

// Дан текстовый файл, представляющий собой запись
//арифметического выражения, операндами которого являются
//однозначные числа. Число операций в выражении не больше двух.
//Вычислить значение этого выражения и дописать его в конец этого
//файла
void task_03(char *full_filepath);

// Дан текстовый файл. Сохранить в файле только те слова, которые
//содержат данную последовательность символов.
void task_04(char *full_filepath, char *symbol_sequence);

// Дан текстовый файл. Преобразовать его, оставив в каждой строке
//только самое длинное слово. (доп) если таких слов несколько, оставляет первое.
void task_05(char *full_filepath);


typedef struct polynomial {
    int pow;
    int coefficient;
} polynomial_t;

// В бинарном файле структур хранятся многочлены в порядке
//убывания степеней. Каждая структура содержит два поля: показатель
//степени члена и коэффициент. Члены с нулевыми коэффициентами
//не хранятся. Свободный член присутствует обязательно, даже если он
//равен нулю. Удалить из файла многочлены, для которых данное x
//является корнем
void task_06(char *full_filepath, double value);

// Дан бинарный файл целых чисел. Нулевых компонент в файле нет.
//Число отрицательных компонент равно числу положительных.
//Преобразовать файл таким образом, чтобы сначала были
//положительные числа, а затем отрицательные. Порядок следования
//как положительных, так и отрицательных чисел сохранить.
void task_07(char *full_filepath);

// Дан бинарный файл квадратных матриц порядка n. Преобразовать
//его, заменив каждую матрицу, не являющуюся симметричной,
//транспонированной.
void task_08(char *full_filepath);


typedef struct participant {
    char full_name[MAX_NAME_SIZE];
    int result;
} participant_t;


long getFirstStringAfterFilePoint(FILE *file, char *string);

// В бинарном файле структур хранится информация о спортсменах:
//Ф.И.О., наилучший результат. Требуется сформировать команду из n
//лучших спортсменов. Преобразовать файл, сохранив в нем
//информацию только о членах команды.
void task_09(char *full_filepath, size_t n, size_t num_of_participants);


typedef struct commodity {
    char name[MAX_NAME_SIZE];
    int price;
    int total_price;
    int quantity;
} commodity_t;


typedef struct order {
    char name[MAX_NAME_SIZE];
    int quantity;
} order_t;

// В бинарном файле f структур хранится следующая информация о
//товарах, имеющихся на складе: наименование товара, цена единицы
//товара, общая стоимость и количество. В бинарном файле структур g
//хранится информация о заказах: наименование товара и его
//количество. Обновить файл f с учетом отпущенных товаров в
//соответствии с заказами из файла g. Если товар отпущен полностью,
//запись о нем из файла f удаляется.
void task_10(char *full_commodity_filepath, char *full_order_filepath);

#endif //COURSE_TASKS_H
