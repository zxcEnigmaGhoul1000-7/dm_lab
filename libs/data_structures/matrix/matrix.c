#include "matrix.h"


static void memAllocFailProcess_(void *p, char *func_name) {
    if (p == NULL) {
        MessageBox(GetActiveWindow(), "Fail memory allocated", func_name, MB_ICONERROR);
        exit(1);
    }
}

matrix_t getMemMatrix(size_t n_rows, size_t n_cols) {
    int **values = (int **) malloc(sizeof(int *) * n_rows);
    memAllocFailProcess_(values, "getMemMatrix");

    for (size_t i = 0; i < n_rows; i++) {
        values[i] = (int *) malloc(sizeof(int) * n_cols);
        memAllocFailProcess_(values[i], "getMemMatrix");
    }

    return (matrix_t) {
        values,
        n_rows,
        n_cols
    };
}


matrix_t *getMemArrayOfMatrices(size_t n_matrices, size_t n_rows, size_t n_cols) {
    matrix_t *mx_arr = (matrix_t *) malloc(sizeof(matrix_t) * n_matrices);
    memAllocFailProcess_(mx_arr, "getMemArrayOfMatrices");

    for (size_t i = 0; i < n_matrices; i++) {
        mx_arr[i] = getMemMatrix(n_rows, n_cols);
        memAllocFailProcess_(mx_arr, "getMemArrayOfMatrices");
    }

    return mx_arr;
}


void freeMemMatrix(matrix_t *m) {
    for (; m->n_rows > 0; m->n_rows--) {
        free(m->values[m->n_rows - 1]);
    }

    m->n_cols = 0;
    free(m->values);
    m->values = NULL;
}


void freeMemMatrices(matrix_t *ms, size_t n_matrices) {
    for (size_t i = 0; i < n_matrices; i++) {
        freeMemMatrix(&ms[i]);
    }

    free(ms);
    ms = NULL;
}


void inputMatrix(matrix_t *m) {
    for (size_t i = 0; i < m->n_rows; i++)
        for (size_t j = 0; j < m->n_cols; j++)
            scanf("%d", &m->values[i][j]);
}


void inputMatrices(matrix_t *ms, size_t n_matrices) {
    for (size_t i = 0; i < n_matrices; i++)
        inputMatrix(&ms[i]);
}


void outputMatrix(matrix_t m) {
    for (size_t i = 0; i < m.n_rows; i++) {
        printf("[%d", m.values[i][0]);
        for (size_t j = 1; j < m.n_cols; j++)
            printf(", %d", m.values[i][j]);
        printf("]\n");
    }
}


void outputMatrices(matrix_t *ms, size_t n_matrices) {
    for (size_t i = 0; i < n_matrices; i++) {
        printf("%zu elem:\n", i);
        outputMatrix(ms[i]);
    }
}

void swapRows(matrix_t m, size_t i1, size_t i2) {
    if (i1 >= m.n_rows || i2 >= m.n_rows) {
        fprintf(stderr, "Access error: going beyond the matrix");
        exit(1);
    }

    int *temp = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = temp;
}


void swapColumns(matrix_t m, size_t j1, size_t j2) {
    if (j1 >= m.n_cols || j2 >= m.n_cols) {
        fprintf(stderr, "Access error: going beyond the matrix");
        exit(1);
    }

    for (size_t i = 0; i < m.n_rows; i++) {
        int temp = m.values[i][j1];
        m.values[i][j1] = m.values[i][j2];
        m.values[i][j2] = temp;
    }
}


static int *getArrRowsNumByCriteria(matrix_t m, int (*criteria)(int*, size_t)) {
    int *res = (int *) malloc(sizeof(int) * m.n_rows);
    memAllocFailProcess_(res, "getArrRowsNumByCriteria");

    for (size_t i = 0; i < m.n_rows; i++) {
        res[i] = criteria(m.values[i], m.n_cols);
    }

    return res;
}


void insertionSortRowsMatrixByRowCriteria(matrix_t m, int (*criteria)(int*, size_t)) {
    int *rows_num_by_criteria = getArrRowsNumByCriteria(m, criteria);

    for (int i = 1; i < (int) (m.n_rows); i++) {
        int sorted = i - 1;

        while (sorted >= 0 && rows_num_by_criteria[sorted] > rows_num_by_criteria[sorted + 1]) {
            swapRows(m, sorted, sorted + 1);
            swapElemArr(rows_num_by_criteria, sorted, sorted + 1);
            sorted--;
        }
    }

    free(rows_num_by_criteria);
}


int *getColumn(matrix_t m, size_t index) {
    int *column = (int *) malloc(sizeof(int) * m.n_rows);
    memAllocFailProcess_(column, "getColumns");

    for (size_t i = 0; i < m.n_rows; i++) {
        column[i] = m.values[i][index];
    }

    return column;
}


static int *getArrColumnsNumByCriteria(matrix_t m, int (*criteria)(int*, size_t)) {
    int *res = (int *) malloc(sizeof(int) * m.n_cols);
    memAllocFailProcess_(res, "getArrColumnNumByCriteria");

    for (size_t i = 0; i < m.n_cols; i++) {
        int *column = getColumn(m, i);
        res[i] = criteria(column, m.n_rows);
        free(column);
    }

    return res;
}


void selectionSortColsMatrixByColCriteria(matrix_t m, int (*criteria)(int*, size_t)) {
    for (size_t i = 0; i < m.n_cols - 1; i++) {
        int *columns_num_by_criteria = getArrColumnsNumByCriteria(m, criteria);
        size_t min_index = i;
        int min_num_by_criteria = columns_num_by_criteria[min_index];

        for (size_t j = i + 1; j < m.n_cols; j++)
            if (columns_num_by_criteria[j] < min_num_by_criteria) {
                min_index = j;
                min_num_by_criteria = columns_num_by_criteria[j];
            }

        if (min_index != i) {
            swapColumns(m, i, min_index);
            swapElemArr(columns_num_by_criteria, i, min_index);
        }

        free(columns_num_by_criteria);
    }
}


bool isSquareMatrix(matrix_t m) {
    return m.n_rows == m.n_cols;
}


bool areTwoMatricesEqual(matrix_t m1, matrix_t m2) {
    if (m1.n_rows != m2.n_rows || m1.n_cols != m2.n_cols)
        return false;

    for (size_t i = 0; i < m1.n_rows; i++) {
        if (memcmp(m1.values[i], m2.values[i], sizeof(int) * m1.n_cols) != 0)
            return false;
    }

    return true;
}

bool isEMatrix(matrix_t m) {
    if (!isSquareMatrix(m))
        return false;

    for (size_t i = 0; i < m.n_rows; i++)
        for (size_t j = 0; j < m.n_cols; j++)
            if (m.values[i][j] != (i==j))
                return false;

    return true;
}


bool isSymmetricMatrix(matrix_t m) {
    if (!isSquareMatrix(m))
        return false;

    for (size_t i = 0; i < m.n_rows; i++)
        for (size_t j = 0; j < m.n_cols; j++)
            if (m.values[i][j] != m.values[j][i])
                return false;

    return true;
}

static void swap_(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void transposeSquareMatrix(matrix_t *m) {
    assert(isSquareMatrix(*m));

    for (size_t i = 0; i < m->n_rows; i++)
        for (size_t j = 0; j < m->n_cols; j++)
            if (i <= j)
                swap_(&m->values[j][i], &m->values[i][j]);
}


void transposeMatrix(matrix_t *m) {
    matrix_t tm = getMemMatrix(m->n_cols, m->n_rows);

    for (size_t i = 0; i < m->n_rows; i++)
        for (size_t j = 0; j < m->n_cols; j++)
            tm.values[j][i] = m->values[i][j];

    freeMemMatrix(m);
    *m = tm;
}


position_t getMinValuePos(matrix_t m) {
    position_t res;
    int min_elem = INT_MAX;

    for (size_t i = 0; i < m.n_rows; i++)
        for (size_t j = 0; j < m.n_cols; j++)
            if (m.values[i][j] < min_elem) {
                res.row_index = i;
                res.col_index = j;
                min_elem = m.values[i][j];
            }
    return res;
}


position_t getMaxValuePos(matrix_t m) {
    position_t res;
    int max_elem = INT_MIN;

    for (size_t i = 0; i < m.n_rows; i++)
        for (size_t j = 0; j < m.n_cols; j++)
            if (m.values[i][j] > max_elem) {
                res.row_index = i;
                res.col_index = j;
                max_elem = m.values[i][j];
            }

    return res;
}


matrix_t createMatrixFromArray(const int *arr,
                               int n_rows, int n_cols) {
    matrix_t m = getMemMatrix(n_rows, n_cols);

    int k = 0;
    for (int i = 0; i < n_rows; i++)
        for (int j = 0; j < n_cols; j++)
            m.values[i][j] = arr[k++];

    return m;
}


matrix_t *createArrayOfMatrixFromArray(const int *values,
                                       size_t n_matrices, size_t n_rows, size_t n_cols) {
    matrix_t *ms = getMemArrayOfMatrices(n_matrices, n_rows, n_cols);

    int l = 0;
    for (size_t k = 0; k < n_matrices; k++)
        for (size_t i = 0; i < n_rows; i++)
            for (size_t j = 0; j < n_cols; j++)
                ms[k].values[i][j] = values[l++];

    return ms;
}

