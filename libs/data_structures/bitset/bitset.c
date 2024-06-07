#include "bitset.h"


bitset_t bitset_create(unsigned max_value) {
    assert(max_value < 32);
    return (bitset_t) {0, max_value};
}

void bitset_appendArray(int arr[], size_t size, bitset_t *set) {
    for (size_t i = 0; i < size; i++) {
        bitset_insert(set, arr[i]);
    }
}

bool bitset_in(bitset_t set, unsigned int value) {
    return (value < set.max_value) && set.values & (1 << value);
}

bool bitset_isEqual(bitset_t set1, bitset_t set2) {
    return set1.values == set2.values;
}

bool bitset_isSubset(bitset_t subset, bitset_t set) {
    return (set.values & subset.values) == subset.values;
}

void bitset_insert(bitset_t *set, unsigned int value) {
    assert(value <= set->max_value);
    set->values |= (1 << value);
}

void bitset_deleteElement(bitset_t *set, unsigned int value) {
    assert(value <= set->max_value);
    set->values &= ~(1 << value);
}

bitset_t bitset_union(bitset_t set1, bitset_t set2) {
    return (bitset_t) {
        set1.values | set2.values,
        set1.max_value
        };
}

bitset_t bitset_intersection(bitset_t set1, bitset_t set2) {
    return (bitset_t) {
        set1.values & set2.values,
        set1.max_value
    };
}

bitset_t bitset_difference(bitset_t minuend, bitset_t subtrahend) {
    return (bitset_t) {
        minuend.values & ~subtrahend.values,
        minuend.max_value
    };
}

bitset_t bitset_symmetricDifference(bitset_t set1, bitset_t set2) {
    return (bitset_t) {
        set1.values ^ set2.values,
        set1.max_value
    };
}

bitset_t bitset_complement(bitset_t set) {
    uint32_t n = 32 - (set.max_value + 1);
    return (bitset_t) {
        (~set.values << n) >> n,
        set.max_value
    };
}

void bitset_print(bitset_t set) {
    if (!set.values)
        printf("{}");
    else {
        printf("{");
        for (uint32_t elem_of_sequence = 0; elem_of_sequence <= set.max_value; elem_of_sequence++) {
            if (bitset_in(set, elem_of_sequence))
                printf("%u, ", elem_of_sequence);
        }

        printf("\b\b}\n");
    }
}