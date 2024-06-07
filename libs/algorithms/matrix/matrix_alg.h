#ifndef COURSE_MATRIX_ALG_H
#define COURSE_MATRIX_ALG_H

#include "../../data_structures/matrix/matrix.h"


matrix_t matrixCopy(matrix_t m);


matrix_t getProductOfMatrices(matrix_t m1, matrix_t m2);


matrix_t getMatrixRaisedToPower(matrix_t m, size_t degree);

int determinant(matrix_t m);


#endif //COURSE_MATRIX_ALG_H
