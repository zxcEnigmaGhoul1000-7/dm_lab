#include "ordered_set.h"


ordered_array_set_t ordered_array_set_create(size_t capacity) {
    int *data = (int *) malloc(sizeof(int) * capacity);
    if (data == NULL && capacity != 0) {
        fprintf(stderr, "Fail memory allocated in unordered_array_set_create.\n");
        exit(1);
    }

    return (ordered_array_set_t) {
            data,
            0,
            capacity
    };
}


void ordered_array_set_shrinkToFit(ordered_array_set_t *set) {
    if (set->size != set->capacity) {
        set->data = (int *) realloc(set->data, sizeof(int) * set->size);
        if (set->data == NULL && set->size != 0) {
            fprintf(stderr, "Fail memory allocated in ordered_array_set_shrinkToFit\n");
            exit(1);
        }
        set->capacity = set->size;
    }
}


ordered_array_set_t ordered_array_set_create_from_array(const int *a,
                                                        size_t size) {
    ordered_array_set_t set = ordered_array_set_create(size);
    for (size_t i = 0; i < size; i++)
        ordered_array_set_insert(&set, a[i]);
    ordered_array_set_shrinkToFit(&set);

    return set;
}


size_t ordered_array_set_ind(ordered_array_set_t *set, int value) {
    return binarySearch_(set->data, set->size, value);
}

bool ordered_array_set_isValueIn(ordered_array_set_t set, int value) {
    return ordered_array_set_ind(&set, value) != set.size;
}

bool ordered_array_set_isEqual(ordered_array_set_t set1, ordered_array_set_t set2) {
    if (set1.size != set2.size)
        return false;

    return memcmp(set1.data, set2.data, set1.size) == 0;
}

bool ordered_array_set_isSubset(ordered_array_set_t subset,
                                ordered_array_set_t set) {
    if (subset.size > set.size)
        return 0;

    size_t matches = 0;
    for (size_t i = 0; i < subset.size; i++) {
        if (ordered_array_set_isValueIn(set, subset.data[i]))
            matches++;
    }

    return matches == subset.size;
}


void ordered_array_set_isAbleAppend(ordered_array_set_t *set) {
    assert(set->size < set->capacity);
}


void ordered_array_set_insert(ordered_array_set_t *set, int value) {
    if (ordered_array_set_ind(set, value) == set->size) {
        ordered_array_set_isAbleAppend(set);
        if (set->size - 1 >= set->capacity) {
            set->data[set->size++] = value;
        } else {
            size_t reserved_index = binarySearchMoreOrEqual_(set->data, set->size, value);

            for (size_t i = set->size; i > reserved_index; i--)
                set->data[i] = set->data[i - 1];

            set->data[reserved_index] = value;
            set->size++;
        }
    }
}

void ordered_array_set_deleteElement(ordered_array_set_t *set, int value) {
    size_t index_of_value = ordered_array_set_ind(set, value);

    if (index_of_value < set->size)
        deleteByIndexAndSaveOrder_(set->data, &set->size, index_of_value);
}

ordered_array_set_t ordered_array_set_union(ordered_array_set_t set1,
                                            ordered_array_set_t set2) {
    ordered_array_set_t result = ordered_array_set_create(set1.size + set2.size);

    memcpy(result.data, set1.data, set1.size * sizeof(int));
    result.size = set1.size;

    for (size_t i = 0; i < set2.size; i++) {
        ordered_array_set_insert(&result, set2.data[i]);
    }

    ordered_array_set_shrinkToFit(&result);

    return result;
}


ordered_array_set_t ordered_array_set_intersection(ordered_array_set_t set1,
                                                   ordered_array_set_t set2) {
    ordered_array_set_t result = ordered_array_set_create(set1.size);
    for (size_t i = 0; i < set1.size; i++) {
        if (ordered_array_set_isValueIn(set2, set1.data[i]))
            ordered_array_set_insert(&result, set1.data[i]);
    }

    if (result.size)
        ordered_array_set_shrinkToFit(&result);

    return result;
}


ordered_array_set_t ordered_array_set_difference(ordered_array_set_t set1,
                                                 ordered_array_set_t set2) {
    if (set2.size == 0)
        return set1;

    ordered_array_set_t result = ordered_array_set_create(set1.size);

    for (size_t i = 0; i < set1.size; i++) {
        if (!ordered_array_set_isValueIn(set2, set1.data[i]))
            result.data[result.size++] = set1.data[i];
    }

    ordered_array_set_shrinkToFit(&result);

    return result;
}


ordered_array_set_t ordered_array_set_symmetricDifference(ordered_array_set_t set1,
                                                          ordered_array_set_t set2) {

    ordered_array_set_t l_diff = ordered_array_set_difference(set1, set2);
    ordered_array_set_t r_diff = ordered_array_set_difference(set2, set1);

    ordered_array_set_t result = ordered_array_set_union(l_diff, r_diff);

    ordered_array_set_delete(&l_diff);
    ordered_array_set_delete(&r_diff);

    return result;
}

ordered_array_set_t ordered_array_set_complement(ordered_array_set_t set,
                                                 ordered_array_set_t universumSet) {
    assert(ordered_array_set_isSubset(set, universumSet));
    return ordered_array_set_difference(universumSet, set);
}

void ordered_array_set_print(ordered_array_set_t set) {
    outputArray_(set.data, set.size);
}

void ordered_array_set_delete(ordered_array_set_t *set) {
    free(set->data);
    set->data = NULL;
    set->capacity = 0;
    set->size = 0;
}