#include "string_library.h"


size_t strlen_(char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;

    return end - begin;
}


char *find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch)
        begin++;

    return begin;
}


char *findNonSpace(char *begin) {
    while (*begin != '\0' && isspace(*begin))
        begin++;

    return begin;
}


char *findSpace(char *begin) {
    while (*begin != '\0' && !isspace(*begin))
        begin++;

    return begin;
}


char *findNonSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin != rend && isspace(*rbegin))
        rbegin--;

    return rbegin;
}


char *findSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin != rend && !isspace(*rbegin))
        rbegin--;

    return rbegin;
}


int strcmp_(const char *lhs, const char *rhs) {
    while (*lhs == *rhs && *lhs != '\0') {
        lhs++;
        rhs++;
    }

    return *lhs - *rhs;
}


char *copy(const char *begin_source, const char *end_source, char *begin_destination) {
    size_t size = end_source - begin_source;
    memcpy(begin_destination, begin_source, size);

    return begin_destination + size;
}


char *copyIf(char *begin_source, const char *end_source, char *begin_destination, int (*f)(int)) {
    while (begin_source != end_source) {
        if (f(*begin_source)) {
            *begin_destination = *begin_source;
            begin_destination++;
        }

        begin_source++;
    }

    return begin_destination;
}


char *copyIfReverse(char *rbegin_source, const char *rend_source, char *begin_destination, int (*f)(int)) {
    while (rbegin_source != rend_source) {
        if (f(*rbegin_source)) {
            *begin_destination = *rbegin_source;
            begin_destination++;
        }

        rbegin_source--;
    }

    return begin_destination;
}


void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line) {
    if (strcmp_(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}

