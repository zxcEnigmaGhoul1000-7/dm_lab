#ifndef PROJECT_TASKS_H
#define PROJECT_TASKS_H

#define MAX_STRING_SIZE 100
#define MAX_N_WORDS_IN_STRING 100
#define MAX_WORD_SIZE 20
#define ASCII_SYMBOLS_AMOUNT 256

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>


typedef struct word_descriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа слова
} word_descriptor_t;


typedef enum WordBeforeFirstWordWithAReturnCode {
    FIRST_WORD_WITH_A,
    NOT_FOUND_A_WORD_WITH_A,
    WORD_FOUND,
    EMPTY_STRING
} WordBeforeFirstWordWithAReturnCode;


typedef enum WordPrecedingFirstCommonWordReturnCode {
    WORD_PRECEDING_EMPTY_STRING,
    WORD_PRECEDING_FIRST_WORDS_IS_COMMON,
    WORD_PRECEDING_WORD_FOUND,
    WORD_PRECEDING_NOT_FOUND_COMMON_WORD
} WordPrecedingFirstCommonWordReturnCode;


typedef struct bag_of_words {
    word_descriptor_t words[MAX_N_WORDS_IN_STRING];
    size_t size;
} bag_of_words_t;


void removeNonLetters(char *s);


void removeExtraSpaces(char *s);


int getWord(char *begin_search, word_descriptor_t *word);


int getWordReverse(char *search_end, char *search_start, word_descriptor_t *word);


void forEachWord(char *string, void (*function)(word_descriptor_t));


void lettersToStartDigitsToEnd(word_descriptor_t word);


void replaceDigitsWithSpaces(char *string);


int wordscmp(word_descriptor_t word1, word_descriptor_t word2);


void replace(char *string, char *replaceable, char *replacement);


bool areWordsSorted(char *string);


void getBagOfWords(char *begin_search, bag_of_words_t *bag);


void printWord(word_descriptor_t word);


void printWordsInReverseOrder(char *string);


int countPalindromes(char *string);


void shuffleWords(char *s1, char *s2, char *destination);


void reverseWordsOrder(char *string);


WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(
        char *s, word_descriptor_t *w);


void printWordBeforeFirstWordWithA(char *s);


char* getLastWordInFirstStringInSecondString(char *s1, char *s2);


bool hasStringEqualWords(char *string);


bool hasStrWordsFromEqualSymbols(char *string);


void getStrFromWordsNotEqualToTheLast(char *string, char *result);


void wordDescriptorToString(word_descriptor_t word, char *destination);


WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordInBothStr(
        char *string, char *word, word_descriptor_t *word_dst);

void removePalindromes(char *string);


void addWordsToShorterStr(char *string1, char *string2);


bool isStringContainedAllSymbolOfWords(char *src, char *word);


#endif //PROJECT_TASKS_H
