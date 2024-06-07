#include "matrix_alg.h"


static void memAllocFailProcess_(void *p, char *func_name) {
    if (p == NULL) {
        MessageBox(GetActiveWindow(), "Fail memory allocated", func_name, MB_ICONERROR);
        exit(1);
    }
}


matrix_t matrixCopy(matrix_t m) {
    matrix_t result = getMemMatrix(m.n_rows, m.n_cols);
    for (size_t i = 0; i < m.n_rows; i++)
        for (size_t j = 0; j < m.n_cols; j++)
            result.values[i][j] = m.values[i][j];

    return result;
}


matrix_t getProductOfMatrices(matrix_t m1, matrix_t m2) {
    if (m1.n_cols != m2.n_rows) {
        fprintf(stderr, "Error: Number of columns in the first matrix should \n"
                        "be equal to the number of rows in the second matrix\n");
        exit(1);
    }

    matrix_t result = getMemMatrix(m1.n_rows, m2.n_cols);

    for (size_t i = 0; i < m1.n_rows; i++)
        for (size_t j = 0; j < m2.n_cols; j++) {
            int sum = 0;
            for (size_t k = 0; k < m1.n_cols; k++)
                sum += m1.values[i][k] * m2.values[k][j];

            result.values[i][j] = sum;
        }

    return result;
}

matrix_t getMatrixRaisedToPower(matrix_t m, size_t degree) {
    matrix_t result = matrixCopy(m);

    for (size_t i = 1; i < degree; i++) {
        matrix_t tmp = matrixCopy(result);
        freeMemMatrix(&result);
        result = getProductOfMatrices(tmp, m);
    }
}


int determinant(matrix_t m) {
    if (m.n_rows != m.n_cols) {
        fprintf(stderr, "Error: the matrix to which the determinant is being searched is not square");
        exit(1);
    }


}