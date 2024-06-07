#include "tasks.h"
#include "../libs/algorithms/string/string_library.h"


void handleFileOpeningFail(FILE *file, char *filepath) {
    if (file == NULL) {
        fprintf(stderr, "The I/O stream could not be linked to the file: \"%s\"", filepath);

        exit(1);
    }
}


void handleFailMemAllocated(void *p) {
    if (p == NULL) {
        fprintf(stderr, "Fail memory allocated");

        exit(1);
    }
}


void task_01(char *full_filepath) {
    FILE *origin_matrix_file = fopen(full_filepath, "r");
    handleFileOpeningFail(origin_matrix_file, full_filepath);

    matrix_t *matrices = (matrix_t *) malloc(sizeof(matrix_t));
    handleFailMemAllocated(matrices);

    size_t n_matrices = 0;
    size_t size_of_malloc = 1;
    int order_of_cur_matrix;

    while (fscanf(origin_matrix_file, "%d", &order_of_cur_matrix) == 1) {
        matrix_t cur_matrix = getMemMatrix(order_of_cur_matrix, order_of_cur_matrix);

        for (size_t i = 0; i < order_of_cur_matrix; i++)
            for (size_t j = 0; j < order_of_cur_matrix; j++)
                fscanf(origin_matrix_file, "%d", &cur_matrix.values[i][j]);

        transposeSquareMatrix(&cur_matrix);

        if (n_matrices + 1 > size_of_malloc) {
            size_of_malloc *= 2;
            matrices = (matrix_t *) realloc(matrices, size_of_malloc * sizeof(matrix_t));
            handleFailMemAllocated(matrices);
        }

        matrices[n_matrices++] = cur_matrix;
    }

    fclose(origin_matrix_file);

    FILE *transposed_matrix_file = fopen(full_filepath, "w");

    for (size_t i_of_matrix = 0; i_of_matrix < n_matrices; i_of_matrix++) {
        fprintf(origin_matrix_file, "%d\n", (int) matrices[i_of_matrix].n_rows);

        for (size_t r = 0; r < matrices[i_of_matrix].n_rows; r++) {
            fprintf(origin_matrix_file, "%d", matrices[i_of_matrix].values[r][0]);

            for(size_t c = 1; c < matrices[i_of_matrix].n_cols; c++)
                fprintf(origin_matrix_file, " %d", matrices[i_of_matrix].values[r][c]);

            fprintf(origin_matrix_file, "\n");
        }
    }

    fclose(origin_matrix_file);
    for (size_t i = 0; i < n_matrices; i++)
        freeMemMatrix(&matrices[i]);
    free(matrices);
}


void task_02(char *full_filepath) {
    FILE *double_num_file = fopen(full_filepath, "r");
    handleFileOpeningFail(double_num_file, full_filepath);

    arr_of_double_t result_arr = {
            malloc(sizeof(double)),
            malloc(sizeof(int)),
            0,
            1
    };
    handleFailMemAllocated(result_arr.values_of_mantissa);
    handleFailMemAllocated(result_arr.values_of_order);

    double current_value;
    while (fscanf(double_num_file, "%lf", &current_value) == 1) {
        size_t i = result_arr.n_values;

        if (result_arr.n_values + 1 > result_arr.size_of_malloc) {
            result_arr.size_of_malloc *= 2;
            result_arr.values_of_mantissa = (double *) realloc(result_arr.values_of_mantissa, result_arr.size_of_malloc * sizeof(double));
            result_arr.values_of_order = (int *) realloc(result_arr.values_of_order, result_arr.size_of_malloc * sizeof(int));
            handleFailMemAllocated(result_arr.values_of_order);
            handleFailMemAllocated(result_arr.values_of_mantissa);
        }

        result_arr.values_of_order[i] = 0;

        while (fabs(current_value) < 1.0f - DBL_EPSILON) {
             current_value *= 10;
             result_arr.values_of_order[i]--;
        }

        while (fabs(current_value) >= 10.0f + DBL_EPSILON) {
            current_value /= 10;
            result_arr.values_of_order[i]++;
        }

        result_arr.values_of_mantissa[i] = current_value;
        result_arr.n_values++;
    }

    fclose(double_num_file);

    FILE *result_file = fopen(full_filepath, "w");

    fprintf(result_file, "%.2lfe%d", result_arr.values_of_mantissa[0], result_arr.values_of_order[0]);
    for (size_t i = 1; i < result_arr.n_values; i++) {
        fprintf(result_file, " %.2lfe%d", result_arr.values_of_mantissa[i], result_arr.values_of_order[i]);
    }


    fclose(double_num_file);
    free(result_arr.values_of_mantissa);
    free(result_arr.values_of_order);
}


int getOperationPriority(char operation) {
    if (operation == '^')
        return 3;
    if (operation == '/' || operation == '*' || operation == '%')
        return 2;
    if (operation == '+' || operation == '-')
        return 1;

    return 0;
}


bool isOperation(char symbol) {
    return (bool) getOperationPriority(symbol);
}


void swapChar(char *symbol1, char *symbol2) {
    char tmp = *symbol1;
    *symbol1 = *symbol2;
    *symbol2 = tmp;
}


double calcExpressionResult(double operand1, double operand2, char operation) {
    switch (operation) {
        case ('^'):
            return pow(operand1, operand2);
        case ('*'):
            return operand1 * operand2;
        case('/'):
            assert(!(fabs(operand2) < DBL_EPSILON));
            return operand1 / operand2;
        case ('%'):
            return (int) operand1 % (int) operand2;
        case ('-'):
            return operand1 - operand2;
        case ('+'):
            return operand1 + operand2;
    }
}


void task_03(char *full_filepath) {
    FILE *expression_file = fopen(full_filepath, "r");
    handleFileOpeningFail(expression_file, full_filepath);

    char operations[2];
    int operands[3];
    int num_of_operands = 0, num_of_operations = 0;
    char cur_sym = fgetc(expression_file);

    while (cur_sym != EOF) {
        if (isdigit(cur_sym))
            operands[num_of_operands++] = cur_sym - '0';
        else if (isOperation(cur_sym))
            operations[num_of_operations++] = cur_sym;

        cur_sym = fgetc(expression_file);
    }

    double result;
    if (num_of_operations == 2 && getOperationPriority(operations[0]) < getOperationPriority(operations[1]))
        result = calcExpressionResult(operands[0],
                                      calcExpressionResult(operands[1], operands[2], operations[1]),
                                      operations[0]);
    else {
        for (size_t i = 0; i < num_of_operations; i++)
            result = calcExpressionResult(operands[i], operands[i + 1], operations[i]);
    }

    fclose(expression_file);

    FILE *final_file = fopen(full_filepath, "a");

    fprintf(final_file, " = %lf", result);

    fclose(final_file);
}


static char _str_buff[MAX_STR_NUM][MAX_STR_SIZE];


bool isStrInWord(word_descriptor_t word, char *str) {
    if (strlen(str) > word.end - word.begin)
        return false;

    while (word.begin != word.end) {
        if (*word.begin == *str && memcmp(word.begin, str, strlen(str)) == 0)
            return true;
        word.begin++;
    }

    return false;
}


void task_04(char *full_filepath, char *symbol_sequence) {
    FILE *original_file = fopen(full_filepath, "r");
    handleFileOpeningFail(original_file, full_filepath);

    size_t num_of_strings = 0;
    while(!feof(original_file))
        fgets(_str_buff[num_of_strings++], MAX_STR_SIZE - 1, original_file);

    bag_of_words_t bag_of_bags[num_of_strings];
    for (size_t i = 0; i < num_of_strings; i++) {
        getBagOfWords(_str_buff[i], &bag_of_bags[i]);

        char *write_ptr = _str_buff[i];

        for (size_t j = 0; j < bag_of_bags[i].size; j++)
            if (isStrInWord(bag_of_bags[i].words[j], symbol_sequence)) {
                wordDescriptorToString(bag_of_bags[i].words[j], write_ptr);
                write_ptr += bag_of_bags[i].words[j].end - bag_of_bags[i].words[j].begin;
                *(write_ptr++) = ' ';
            }

        *(--write_ptr) = '\0';
    }

    fclose(original_file);

    FILE *result_file = fopen(full_filepath, "w");

    for (size_t i = 0; i < num_of_strings; i++) {
        fputs(_str_buff[i], result_file);
        fputc('\n', result_file);
    }

    fclose(result_file);
}


size_t getIndexOfMaxLenWord(bag_of_words_t bag) {
    size_t max_len = 0;
    size_t result = bag.size;
    for (size_t i = 0; i < bag.size; i++) {
        if (bag.words[i].end - bag.words[i].begin > max_len) {
            max_len = bag.words[i].end - bag.words[i].begin;
            result = i;
        }
    }

    return result;
}


void task_05(char *full_filepath) {
    FILE *original_file = fopen(full_filepath, "r");
    handleFileOpeningFail(original_file, full_filepath);

    size_t num_of_strings = 0;
    while(!feof(original_file))
        fgets(_str_buff[num_of_strings++], MAX_STR_SIZE - 1, original_file);

    bag_of_words_t bag_of_bags[num_of_strings];
    for (size_t i = 0; i < num_of_strings; i++) {
        getBagOfWords(_str_buff[i], &bag_of_bags[i]);

        word_descriptor_t max_word = bag_of_bags[i].words[getIndexOfMaxLenWord(bag_of_bags[i])];
        wordDescriptorToString(max_word, _str_buff[i]);

        *(_str_buff[i] + (max_word.end - max_word.begin)) = '\0';
    }

    fclose(original_file);

    FILE *result_file = fopen(full_filepath, "w");

    for (size_t i = 0; i < num_of_strings; i++) {
        fputs(_str_buff[i], result_file);
        fputc('\n', result_file);
    }

    fclose(result_file);
}


size_t getSizeOfFile(FILE *file) {
    fseek(file, 0, SEEK_END);
    size_t result = ftell(file);
    rewind(file);

    return result;
}


void task_06(char *full_filepath, double value) {
    FILE *original_file = fopen(full_filepath, "rb");
    handleFileOpeningFail(original_file, full_filepath);

    size_t num_of_elem = getSizeOfFile(original_file) / sizeof(polynomial_t);
    polynomial_t *origin_polynomials_seq = (polynomial_t *) malloc(sizeof(polynomial_t) * num_of_elem);
    handleFailMemAllocated(origin_polynomials_seq);

    if (fread(origin_polynomials_seq, sizeof(polynomial_t), num_of_elem, original_file) != num_of_elem) {
        fprintf(stderr, "File %s\n", __FILE__);
        fprintf(stderr, "%s - failed on line %d\n", __func__, __LINE__);
        fprintf(stderr, "read file fail");
    }

    fclose(original_file);

    polynomial_t *result_polynomials_seq = (polynomial_t *) malloc(sizeof(polynomial_t) * num_of_elem);
    handleFailMemAllocated(result_polynomials_seq);

    size_t result_size = 0;
    for (size_t i = 0; i < num_of_elem; i++) {
        if (origin_polynomials_seq[i].coefficient * pow(value, origin_polynomials_seq[i].pow) != value * value || origin_polynomials_seq[i].pow == 0)
            result_polynomials_seq[result_size++] = (polynomial_t ) {
                origin_polynomials_seq[i].pow,
                origin_polynomials_seq[i].coefficient
            };
    }

    FILE *result_file = fopen(full_filepath, "wb");
    fwrite(result_polynomials_seq, sizeof(polynomial_t), result_size, result_file);

    fclose(result_file);

    free(origin_polynomials_seq);
    free(result_polynomials_seq);
}


void task_07(char *full_filepath) {
    FILE *origin_file = fopen(full_filepath, "rb");
    handleFileOpeningFail(origin_file, full_filepath);

    size_t num_of_elem = getSizeOfFile(origin_file) / sizeof(int);

    int *origin_arr = (int *) malloc(sizeof(int) * num_of_elem);
    handleFailMemAllocated(origin_arr);
    fread(origin_arr, sizeof(int), num_of_elem, origin_file);

    fclose(origin_file);

    int *result_arr = (int *) malloc(sizeof(int) * num_of_elem);
    handleFailMemAllocated(result_arr);

    size_t rec = 0;

    for (size_t i = 0; i < num_of_elem; i++)
        if (origin_arr[i] > 0)
            result_arr[rec++] = origin_arr[i];

    for (size_t i = 0; i < num_of_elem; i++)
        if (origin_arr[i] < 0)
            result_arr[rec++] = origin_arr[i];

    FILE *result_file = fopen(full_filepath, "wb");

    fwrite(result_arr, sizeof(int), num_of_elem, result_file);
    fclose(result_file);

    free(origin_arr);
    free(result_arr);
}


void task_08(char *full_filepath) {
    FILE *matrix_file = fopen(full_filepath, "rb");
    handleFileOpeningFail(matrix_file, full_filepath);

    size_t num_of_matrices = getSizeOfFile(matrix_file) / sizeof(matrix_t);

    matrix_t *matrices = (matrix_t *) malloc(num_of_matrices * sizeof(matrix_t));
    handleFailMemAllocated(matrices);
    fread(matrices, sizeof(matrix_t), num_of_matrices, matrix_file);

    fclose(matrix_file);

    for (size_t i = 0; i < num_of_matrices; i++)
        if (!isSymmetricMatrix(matrices[i]))
            transposeSquareMatrix(matrices + i);

    matrix_file = fopen(full_filepath, "wb");

    fwrite(matrices, sizeof(matrix_t), num_of_matrices, matrix_file);

    fclose(matrix_file);
    free(matrices);
}



int compareParticipantsNonDecreasing(const void *a, const void *b) {
    participant_t *p1 = (participant_t *)a;
    participant_t *p2 = (participant_t *)b;

    if (p1->result < p2->result) return 1;
    if (p1->result > p2->result) return -1;

    return 0;
}


long getFirstStringAfterFilePoint(FILE *file, char *string) {
    fread(string, sizeof(char), 1, file);

    while (*string != '\0' && !feof(file)) {
        fread(++string, sizeof(char), 1, file);
    }

    return ftell(file);
}


void task_09(char *full_filepath, size_t n, size_t num_of_participants) {
    if (n >= num_of_participants) {

        return;
    }

    FILE *participants_file = fopen(full_filepath, "rb");
    handleFileOpeningFail(participants_file, full_filepath);

    participant_t *participants = (participant_t *) malloc(num_of_participants * sizeof(participant_t));
    handleFailMemAllocated(participants);

    for (size_t i = 0; i < num_of_participants; i++) {
        getFirstStringAfterFilePoint(participants_file, participants[i].full_name);
        fread(&participants[i].result, sizeof(participants[i].result), 1, participants_file);
    }

    qsort(participants, num_of_participants, sizeof(participant_t), compareParticipantsNonDecreasing);

    fclose(participants_file);

    participants_file = fopen(full_filepath, "wb");

    for (size_t i = 0; i < n; i++) {
        fwrite(participants[i].full_name, sizeof(char), strlen(participants[i].full_name) + 1, participants_file);
        fwrite(&participants[i].result, sizeof(participants[i].result), 1, participants_file);
    }

    fclose(participants_file);
    free(participants);
}


void task_10(char *full_commodity_filepath, char *full_order_filepath) {
    FILE *commodity_file = fopen(full_commodity_filepath, "rb+");
    FILE *orders_file = fopen(full_order_filepath, "rb+");
    commodity_t product;
    order_t order;

    while (!feof(commodity_file)) {
        getFirstStringAfterFilePoint(commodity_file, product.name);
        fread(&product.price, sizeof(product.price), 1, commodity_file);
        fread(&product.total_price, sizeof(product.total_price), 1, commodity_file);
        fread(&product.quantity, sizeof(product.quantity), 1, commodity_file);

        fseek(orders_file, 0, SEEK_SET);
        bool is_found = false;

        while (!feof(orders_file)) {
            getFirstStringAfterFilePoint(orders_file, order.name);
            fread(&order.quantity, sizeof(order.quantity), 1, orders_file);
            if (strcmp(product.name, order.name) == 0) {
                is_found = true;
                if (order.quantity < product.quantity) {
                    product.quantity -= order.quantity;
                    product.total_price -= product.price * order.quantity;
                } else {
                    product.quantity = 0;
                    product.total_price = 0;
                    break;
                }
            }
        }

        if (!is_found) {
            fseek(commodity_file, - (strlen(product.name) + 1 + (sizeof(product.quantity) * 3)), SEEK_CUR);
        } else {
            fwrite(product.name, strlen(product.name) + 1, 1, commodity_file);
            fwrite(&product.price, sizeof(product.price), 1, commodity_file);
            fwrite(&product.total_price, sizeof(product.total_price), 1, commodity_file);
            fwrite(&product.quantity, sizeof(product.quantity), 1, commodity_file);
        }
    }
}