#include "tasks.h"
#include "../string_library.h"


char _string_buffer[MAX_STRING_SIZE + 1];
bag_of_words_t bag1;
bag_of_words_t bag2;


static void clearStringBuff() {
    char *write_ptr = _string_buffer;
    while (write_ptr != _string_buffer + MAX_STRING_SIZE + 1 && *write_ptr != '\0')
        *(write_ptr++) = '\0';
}

// task1
char* getEndOfString(char *s) {
    return s + strlen_(s);
}


void removeNonLetters(char *s) {
    char *end_source = getEndOfString(s);
    char *destination = copyIf(s, end_source, s, isgraph);
    *destination = '\0';
}

// task2
void removeExtraSpaces(char *source) {
    char* write_pointer = source;
    while (*source != '\0') {
        if (!isspace(*source) || (isspace(*source) && !isspace(*(source - 1)))) {
            *write_pointer = *source;
            write_pointer++;
        }
        source++;
    }

    *write_pointer = '\0';
}

// task3
int getWord(char *begin_search, word_descriptor_t* word) {
    word->begin = findNonSpace(begin_search);

    if (*word->begin == '\0') {
        return 0;
    }

    word->end = findSpace(word->begin);

    return 1;
}


void forEachWord(char *string, void (*function)(word_descriptor_t)) {
    char* search_point = string;
    word_descriptor_t word;

    while (getWord(search_point, &word)) {
        function(word);

        search_point = word.end;
    }
}


void lettersToStartDigitsToEnd(word_descriptor_t word) {
    char* string_buffer_end = copy(word.begin, word.end, _string_buffer);
    char* digits_end = copyIf(_string_buffer, string_buffer_end, word.begin, isalpha);

    copyIf(_string_buffer, string_buffer_end, digits_end, isdigit);
    clearStringBuff();
}

// task4
void replaceDigitsWithSpaces(char *string) {
    char *buffer_begin = _string_buffer;
    char *buffer_end = copy(string, getEndOfString(string), buffer_begin);
    while (buffer_begin < buffer_end) {
        if (isdigit(*buffer_begin)) {
            unsigned char a = *buffer_begin - '0';
            while (a--)
                *string++ = ' ';
        } else
            *string++ = *buffer_begin;

        buffer_begin++;
    }

    *string = '\0';
}

// task5
int wordscmp(word_descriptor_t word1, word_descriptor_t word2) {
    char w1[word1.end - word1.begin + 1];
    char w2[word2.end - word2.begin + 1];
    *copy(word1.begin, word1.end, w1) = '\0';
    *copy(word2.begin, word2.end, w2) = '\0';

    return strcmp_(w1, w2);
}


void replace(char *string, char *replaceable, char *replacement) {
    size_t replaceable_length = strlen_(replaceable);
    size_t replacement_length = strlen_(replacement);
    word_descriptor_t replaceable_word = {replaceable, replaceable + replaceable_length};
    word_descriptor_t replacement_word = {replacement, replacement + replacement_length};

    char *read_ptr, *write_ptr;
    if (replaceable_length > replacement_length) {
        read_ptr = string;
    } else {
        *copy(string, string + strlen_(string), _string_buffer) = '\0';
        read_ptr = _string_buffer;
    }

    write_ptr = string;
    word_descriptor_t cur_word;

    while (getWord(read_ptr, &cur_word)) {
        write_ptr = copy(read_ptr, cur_word.begin, write_ptr);

        if (wordscmp(cur_word, replaceable_word) == 0) {
            write_ptr = copy(replacement_word.begin, replacement_word.end, write_ptr);
        } else {
            write_ptr = copy(cur_word.begin, cur_word.end, write_ptr);
        }

        read_ptr = cur_word.end;
    }

    *write_ptr = '\0';
}

//task6
bool areWordsSorted(char *string) {
    word_descriptor_t previous_word;

    if (getWord(string, &previous_word)) {
        word_descriptor_t current_word;

        while (getWord(previous_word.end, &current_word)) {
            if (wordscmp(previous_word, current_word) > 0) {
                return false;
            }

            previous_word = current_word;
        }
    }

    return true;
}

// task7
void getBagOfWords(char *begin_search, bag_of_words_t *bag) {
    size_t word_index = 0;

    while (getWord(begin_search, bag->words + word_index)) {
        begin_search = bag->words[word_index].end;
        word_index++;
    }

    bag->size = word_index;
}


void printWord(word_descriptor_t word) {
    while (word.begin != word.end) {
        putchar(*word.begin);
        word.begin++;
    }
}


void printWordsInReverseOrder(char* string) {
    getBagOfWords(string, &bag1);

    for (size_t i = bag1.size - 1; i != -1; i--) {
        printWord(bag1.words[i]);
        putchar('\n');
    }
    bag1.size = 0;
}

// task8
static bool _isPalindrome(char *begin, char *end) {
    end--;

    if (*end == ',')
        end--;

    while (end > begin) {
        if (*begin != *end)
            return false;

        begin++;
        end--;
    }

    return true;
}


int countPalindromes(char *string) {
    int count = 0;
    char* search_ptr = string;
    word_descriptor_t word;

    while (getWord(search_ptr, &word)) {
        if (_isPalindrome(word.begin, word.end)) {
            count++;
        }

        search_ptr = word.end;
    }

    return count;
}

//task9
void shuffleWords(char *s1, char *s2, char *destination) {
    word_descriptor_t word1, word2;
    bool is_word_1_found, is_word_2_found;
    char* begin_search_1 = s1;
    char* begin_search_2 = s2;
    char* dst = destination;

    while ((is_word_1_found = getWord(begin_search_1, &word1)),
            (is_word_2_found = getWord(begin_search_2, &word2)),
            is_word_1_found || is_word_2_found) {
        if (is_word_1_found) {
            dst = copy(word1.begin, word1.end, dst);
            *dst++ = ' ';
            begin_search_1 = word1.end;
        }

        if (is_word_2_found) {
            dst = copy(word2.begin, word2.end, dst);
            *dst++ = ' ';
            begin_search_2 = word2.end;
        }
    }

    *(dst - (dst != destination)) = '\0';
}

//task10
void reverseWordsOrder(char* string) {
    getBagOfWords(string, &bag1);
    char *result = _string_buffer;

    for (size_t i = bag1.size; i > 0; i--) {
        char *s = bag1.words[i - 1].begin;
        while (s != bag1.words[i - 1].end)
            *(result++) = *s++;

        if (i != 1)
            *(result++) = ' ';
    }

    *copy(_string_buffer, result, string) = '\0';
}

// task11
static bool isSymbolInWord(word_descriptor_t word, const char symbol) {
    return find(word.begin, word.end, symbol) != word.end;
}


WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(
        char *string, word_descriptor_t *word) {
    word_descriptor_t previous_word;

    if (getWord(string, &previous_word)) {
        if (!isSymbolInWord(previous_word, 'A') &&
        !isSymbolInWord(previous_word, 'a')) {
            string = previous_word.end;
            word_descriptor_t next_word;

            while (getWord(string, &next_word)) {
                if (isSymbolInWord(previous_word, 'A') ||
                    isSymbolInWord(previous_word, 'a')) {
                    *word = previous_word;
                    return WORD_FOUND;
                }

                previous_word = next_word;
                string = previous_word.end;
            }

            return NOT_FOUND_A_WORD_WITH_A;
        }

        return FIRST_WORD_WITH_A;
    }

    return EMPTY_STRING;
}


void printWordBeforeFirstWordWithA(char *s) {
    word_descriptor_t word;
    WordBeforeFirstWordWithAReturnCode code = getWordBeforeFirstWordWithA(s,&word);
    if (code == EMPTY_STRING)
        printf("The string is empty.\n");
    else if (code == NOT_FOUND_A_WORD_WITH_A)
        printf("The letter 'a' or 'A' was not founded.\n");
    else if (code == FIRST_WORD_WITH_A)
        printf("The letter 'a' or 'A' was founded in first word.\n");
    else {
        char *beginSearch = s;
        char result[MAX_WORD_SIZE];

        while (getWord(beginSearch, &word)) {
            copy(word.begin, word.end, result);

            getWord(word.end, &word);
            if (find(word.begin, word.end, 'A') != word.end ||
                find(word.begin, word.end, 'a') != word.end) {
                printf("%s\n", result);

                return;
            }

            beginSearch = word.begin;
        }
    }
}

// task12
void wordDescriptorToString(word_descriptor_t word, char *destination) {
    *copy(word.begin, word.end, destination);
}


char* getLastWordInFirstStringInSecondString(char *s1, char *s2) {
    getBagOfWords(s1, &bag1);
    getBagOfWords(s2, &bag2);
    char *result = _string_buffer;

    for (int i = bag1.size; i > 0; i--) {
        for (int j = bag2.size; j > 0; j--) {
            if (wordscmp(bag1.words[i - 1], bag2.words[j - 1]) == 0) {
                wordDescriptorToString(bag1.words[i - 1], result);
                *(result + (bag1.words[i - 1].end - bag1.words[i - 1].begin)) = '\0';

                return result;
            }
        }
    }

    return "";
}


//task 13
bool hasStringEqualWords(char *string) {
    getBagOfWords(string, &bag1);

    for (int i = 0; i < bag1.size; i++)
        for (int j = i + 1; j < bag1.size; j++)
            if (wordscmp(bag1.words[i], bag1.words[j]) == 0)
                return true;

    return false;
}

// task14
static int wordcompare(const void *left, const void *right) {
    return wordscmp(*(word_descriptor_t *)left, *(word_descriptor_t *)right);
}


static int charcompare(const void *left, const void *right) {
    return *(char *)left - *(char *)right;
}


static void removeAdjacentEqualLettersInWord(word_descriptor_t *word) {
    char *begin_dst = word->begin;
    char *begin_source = word->begin;

    while (begin_source != word->end) {
        if (*begin_source != *(begin_source + 1)) {
            *begin_dst = *begin_source;
            begin_dst++;
        }

        begin_source++;
    }

    word->end = begin_dst;
}


bool hasStrWordsFromEqualSymbols(char *string) {
    *copy(string, string + strlen_(string), _string_buffer) = '\0';
    getBagOfWords(_string_buffer, &bag1);

    for (size_t i = 0; i < bag1.size; i++) {
        qsort(bag1.words[i].begin, bag1.words[i].end - bag1.words[i].begin,
              sizeof(char), charcompare);

        removeAdjacentEqualLettersInWord(&bag1.words[i]);
    }

    qsort(bag1.words, bag1.size, sizeof(*bag1.words), wordcompare);

    for (size_t i = 1; i < bag1.size; i++)
        if (wordscmp(bag1.words[i], bag1.words[i - 1]) == 0)
            return true;

    return false;
}

// task 15
void getStrFromWordsNotEqualToTheLast(char *string, char *result) {
    getBagOfWords(string, &bag1);
    char *write_ptr = result;

    if (bag1.size == 0)
        return;

    for (int i = 0; i < bag1.size - 1; i++) {
        if (wordscmp(bag1.words[i], bag1.words[bag1.size - 1]) != 0) {
            wordDescriptorToString(bag1.words[i], write_ptr);
            write_ptr += bag1.words[i].end - bag1.words[i].begin;
            *(write_ptr++) = ' ';
        }
    }

    if (write_ptr == result) {
        *write_ptr = '\0';

        return;
    }

    *(--write_ptr) = '\0';
}

// task16
static bool isWordFound(char *string, word_descriptor_t word) {
    word_descriptor_t current_word;

    while (getWord(string, &current_word)) {
        if (wordscmp(word, current_word) == 0) {
            return true;
        }

        string = current_word.end;
    }

    return false;
}


WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordInBothStr(
        char *string, char *word, word_descriptor_t *word_dst) {
    word_descriptor_t previous_word;

    if (getWord(string, &previous_word)) {
        if (isWordFound(word, previous_word)) {
            string = previous_word.end;
            word_descriptor_t next_word;

            while (getWord(string, &next_word)) {
                if (isWordFound(word, next_word)) {
                    *word_dst = previous_word;

                    return WORD_FOUND;
                }

                previous_word = next_word;
                string = previous_word.end;
            }

            return NOT_FOUND_A_WORD_WITH_A;
        }

        return FIRST_WORD_WITH_A;
    }

    return EMPTY_STRING;
}

// task17
void removePalindromes(char *string) {
    getBagOfWords(string, &bag1);
    char *write_ptr = _string_buffer;

    for (int i = 0; i < bag1.size; i++)
        if (!_isPalindrome(bag1.words[i].begin, bag1.words[i].end)) {
            wordDescriptorToString(bag1.words[i], write_ptr);
            write_ptr += bag1.words[i].end - bag1.words[i].begin;
            *(write_ptr++) = ' ';
        }

    *copy(_string_buffer, --write_ptr, string) = '\0';
}

// task18
void addWordsToShorterStr(char *string1, char *string2) {
    getBagOfWords(string1, &bag1);
    getBagOfWords(string2, &bag2);
    char *write_ptr = _string_buffer;

    if (bag1.size > bag2.size) {
        for (size_t i = bag2.size; i < bag1.size; i++) {
            *(write_ptr++) = ' ';

            wordDescriptorToString(bag1.words[i], write_ptr);
            write_ptr += bag1.words[i].end - bag1.words[i].begin;
        }

        *copy(_string_buffer, write_ptr, getEndOfString(string2)) = '\0';
    } else if (bag2.size > bag1.size) {
        for (size_t i = bag1.size; i < bag2.size; i++) {
            *(write_ptr++) = ' ';

            wordDescriptorToString(bag2.words[i], write_ptr);
            write_ptr += bag2.words[i].end - bag2.words[i].begin;
        }

        *copy(_string_buffer, write_ptr, getEndOfString(string1)) = '\0';
    }
}

// task19
static void getSymbolSet(char *src, bool letters[]) {
    while (*src != '\0') {
        letters[*src] = true;
        src++;
    }
}


bool isStringContainedAllSymbolOfWords(char *src, char *word) {
    bool letters[ASCII_SYMBOLS_AMOUNT] = {false};

    getSymbolSet(word, letters);

    while (*src != '\0') {
        if (!letters[*src]) {
            return false;
        }

        src++;
    }

    return true;
}

