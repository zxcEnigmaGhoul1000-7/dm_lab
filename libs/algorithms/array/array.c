#include "array.h"

void inputArray_(int arr[], size_t size) {
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
}

void outputArray_(const int arr[], size_t size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

size_t getFirstIndexOfNumber_(const int *const a, const size_t n, const int x) {
    for (int i = 0; i < n; i++) {
        if (a[i] == x)
            return i;
    }

    return n;
}

// возвращает true если число находится в массиве, иначе false
bool isValueInArr( const int arr[], const size_t size, const int value) {
    return getFirstIndexOfNumber_(arr, size, value) < size;
}

bool isEven_(int x) {
    return x % 2 == 0;
}

bool isNegative_(int x) {
    return x < 0;
}

bool isPrime_(int x) {
    bool is_prime = true;
    int abs_x = abs(x);
    for (int i = 2; i <= (int) sqrt(abs_x); i++) {
        if (x % i == 0)
            is_prime = false;
    }

    return is_prime && abs_x != 1;
}

size_t getFirstIndexOfNumByPredicate_(const int *const a, const size_t n, bool (*predicate)(int)) {
    for (int i = 0; i < n; i++) {
        if (predicate(a[i]))
            return i;
    }

    return n;
}


size_t getLastIndexOfNumByPredicate_(const int *const a, const int n, bool (*predicate)(int)) {
    for (int i = n - 1; i >= 0; i--) {
        if (predicate(a[i]))
            return i;
    }

    return -1;
}

size_t countOfNumsSatisfiesPredicate_(const int *const a, const size_t n, bool (*predicate)(int)) {
    size_t result = 0;

    for (size_t i = 0; i < n; i++) {
        if (predicate(a[i]))
            result++;
    }

    return result;
}

void expandArray_(int *const a, const size_t n) {
    size_t untouched_left_elem_index = 0, untouched_right_elem_index = n - 1;
    int temp;

    while (untouched_left_elem_index < untouched_right_elem_index) {
        temp = a[untouched_left_elem_index];
        a[untouched_left_elem_index] = a[untouched_right_elem_index];
        a[untouched_right_elem_index] = temp;
        untouched_left_elem_index++;
        untouched_right_elem_index--;
    }
}

bool isPalindromeSequence_(const int *const a, const size_t n) {
    size_t compare_left_elem_index = 0, compare_right_elem_index = n - 1;

    while (compare_left_elem_index < compare_right_elem_index) {
        if (a[compare_left_elem_index] != a[compare_right_elem_index])
            return false;

        compare_left_elem_index++;
        compare_right_elem_index--;
    }

    return true;
}

void swapElemArr(int arr[], size_t i1, size_t i2) {
    int tmp =  arr[i1];
    arr[i1] = arr[i2];
    arr[i2] = tmp;
}

void selectionSortArray_(int *const a, const size_t n) {
    size_t min_elem_index;
    int tmp;

    for (size_t i = 0; i < n; i++) {
        min_elem_index = i;

        for (size_t j = 0; j < n; j++) {
            if (a[j] < a[min_elem_index]) {
                min_elem_index = j;
            }
        }

        tmp = a[min_elem_index];
        a[min_elem_index] = a[i];
        a[i] = tmp;
    }
}

void insertElem_(int *a, size_t *size, const size_t index, const int value) {
    for (size_t i = *size - 1; i >= index; i--)
        a[i + 1] = a[i];

    a[index] = value;
    (*size)++;
}

void appendElem_(int *a, size_t *n, int value) {
    a[*n] = value;
    (*n)++;
}

void deleteByIndexAndSaveOrder_(int *a, size_t *n, const size_t index) {
    for (size_t i = index; i < *n - 1; i++)
        a[i] = a[i + 1];

    (*n)--;
}

void deleteByIndexAndNotSaveOrder_(int *a, size_t *n, const size_t index) {
    a[index] = a[*n - 1];

    (*n)--;
}

void cyclicArrayShift_(int *a, size_t const n, size_t const k) {
    if (n != k) {
        size_t needed_shift = n > k ? k : k % n;
        int copy_of_first_elements[needed_shift];

        for (size_t i = 0; i < n - needed_shift; i++) {
            if (i < needed_shift) {
                copy_of_first_elements[i] = a[i];
            }
            a[i] = a[i + needed_shift];
        }

        for (size_t i = 0; i < needed_shift; i++) {
            a[n - i - 1] = copy_of_first_elements[needed_shift - i - 1];
        }
    }
}

void forEach_(int *a, const int size, int (*f)(int)) {
    for (int i = 0; i < size; i++)
        a[i] = f(a[i]);
}

bool any_(const int *a, const int size, bool (*predicate)(int)) {
    for (int i = 0; i < size; i++)
        if (predicate(a[i]))
            return true;

    return false;
}

bool all_(const int *a, const int size, bool (*predicate)(int)) {
    for (int i = 0; i < size; i++)
        if (!predicate(a[i]))
            return false;

    return true;
}

void arraySplit_(int *a, const size_t len_a, int *b, size_t *len_b, int *c, size_t *len_c, bool (*predicate)(int)) {
    for (size_t i = 0; i < len_a; i++) {
        if (predicate(a[i])) {
            b[*len_b - 1] = a[i];
            (*len_b)++;
        } else {
            c[*len_c - 1] = a[i];
            (*len_c)++;
        }
    }
}

int countIf_(const int *const a, const size_t n, int (*predicate)(int)) {
    int count = 0;
    for (size_t i = 0; i < n; i++)
        count += predicate(a[i]);
    return count;
}

void deleteIf_(int *const a, size_t *const n, int (*deletePredicate)(int)) {
    size_t i_read = 0;
    while (i_read < *n && !deletePredicate(a[i_read]))
        i_read++;
    size_t i_write = i_read;
    while (i_read < *n) {
        if (!deletePredicate(a[i_read])) {
            a[i_write] = a[i_read];
            i_write++;
        }
        i_read++;
    }
    *n = i_write;
}

size_t binarySearch_(const int *a, size_t n, int x) {
    if (n == 0 || a[0] > x || a[n - 1] < x)
        return n;
    size_t left, right;
    left = 0;
    right = n - 1;
    while (left <= right) {
        int middle = left + (right - left) / 2;
        if (a[middle] < x)
            left = middle + 1;
        else if (a[middle] > x)
            right = middle - 1;
        else
            return middle;
    }
    return n;
}

size_t binarySearchLower_(const int arr[], size_t size, int value) {
    if (value <= arr[0] || size == 0)
        return size;
    if (value > arr[size - 1])
        return size - 1;
    size_t low = 0;
    size_t high = size - 1;
    size_t middle;
    while (low + 1 < high) {
        middle = (low + high) / 2;
        if (arr[middle] < value)
            low = middle;
        else
            high = middle;
    }
    while (arr[low + 1] == arr[low])
        low++;

    return low;
}


size_t binarySearchMoreOrEqual_(const int *a, size_t n, int x) {
    if (a[0] >= x)
        return 0;
    size_t left = 0;
    size_t right = n;
    while (right - left > 1) {
        size_t middle = left + (right - left) / 2;
        if (a[middle] < x)
            left = middle;
        else
            right = middle;
    }
    return right;
}
