// File:        matrix.c
// Author:      Zakhary Kaplan <https://zakharykaplan.ca>
// Created:     28 Apr 2019
// SPDX-License-Identifier: NONE

#include "mace/matrix.h"

#include <stdio.h>
#include <stdlib.h>

#define NULL_MATRIX \
    (Matrix) {      \
        0, 0, 0     \
    }

// TODO: Function descriptions
// TODO: Fix memory leaks on all functions that return a matrix

Matrix identityMat(int n) {
    // Return NULL for invalid dimenstion
    if (n < 1)
        return NULL_MATRIX;

    Matrix I;
    // Initialize dimensions of matrix
    I.m = I.n = n;

    // Create data pointer
    double **data = malloc(n * sizeof(double *));
    // Assign rows pointed to by each column
    for (int i = 0; i < n; i++) {
        data[i] = malloc(n * sizeof(double));

        // Set value of each element in row to zero
        for (int j = 0; j < n; j++) {
            if (i == j)
                data[i][j] = 1;
            else
                data[i][j] = 0;
        }
    }

    // Initialize data of matrix
    I.data = data;

    // Return matrix
    return I;
}

Matrix emptyMat(int m, int n) {
    // Return NULL for invalid dimenstions
    if (m < 1 || n < 1)
        return NULL_MATRIX;

    Matrix A;
    // Initialize dimensions of matrix
    A.m = m;
    A.n = n;

    // Create data pointer
    double **data = malloc(m * sizeof(double *));
    // Assign rows pointed to by each column
    for (int i = 0; i < m; i++) {
        data[i] = malloc(n * sizeof(double));

        // Set value of each element in row to zero
        for (int j = 0; j < n; data[i][j++] = 0)
            ;
    }

    // Initialize data of matrix
    A.data = data;

    // Return matrix
    return A;
}

Matrix doubleToMat(double x) {
    Matrix A = emptyMat(1, 1);
    A.data[0][0] = x; // set value of data field to input
    return A;
}

Matrix copyMat(Matrix A) {
    Matrix copyA = emptyMat(A.m, A.n);

    for (int i = 0; i < A.m; i++) {
        for (int j = 0; j < A.n; j++) {
            copyA.data[i][j] = A.data[i][j];
        }
    }

    return copyA;
}

void deleteMat(Matrix *A) {
    // Free memory allocated by malloc
    for (int i = 0; i < A->m; free(A->data[i++]))
        ;
    free(A->data);

    // Reset fields
    A->m = A->n = 0;
    A->data = NULL;
}

void printMat(Matrix A) {
    // Iterate through rows and columns
    for (int i = 0; i < A.m; i++) {
        for (int j = 0; j < A.n; j++) {
            printf("% 6.3g", A.data[i][j]);

            if (j + 1 < A.n)
                printf(" ");
        }
        printf("\n");
    }
}

int isNull(Matrix A) {
    return (A.m == 0) && (A.n == 0) && (A.data == 0);
}

int isSquare(Matrix A) {
    return (A.m == A.n);
}

// -- Unary operations --
Matrix transpose(Matrix A) {
    Matrix transpA = emptyMat(A.n, A.m);

    for (int i = 0; i < A.m; i++) {
        for (int j = 0; j < A.n; j++) {
            transpA.data[j][i] = A.data[i][j];
        }
    }

    return transpA;
}

Matrix inverse(Matrix A) {
    double detA = determinant(A); // calculate determinant of matrix

    // Return early on non-invertible matricies
    if (!detA)
        return NULL_MATRIX;

    // Calculate cofactor matrix
    Matrix cofactorA = copyMat(A);
    for (int i = 0; i < A.m; i++) {
        for (int j = 0; j < A.n; j++) {
            int sign = ((i + j) % 2) ? -1 : 1; // determine sign of term
            Matrix minorA = minor(A, i, j); // create minor at index

            // Add determinant of minor to total
            cofactorA.data[i][j] = sign * determinant(minorA);

            deleteMat(&minorA); // delete minor
        }
    }

    // Calculate adjugate matrix
    Matrix adjugateA = transpose(cofactorA);

    // Calculate inverse matrix
    Matrix inverseA = coeffMat((1 / detA), adjugateA);

    // Delete intermediate matricies
    deleteMat(&cofactorA);
    deleteMat(&adjugateA);

    // Return inverse matrix
    return inverseA;
}

Matrix minor(Matrix A, int row, int col) {
    // Return early on bad minor indicies
    if (row >= A.m || row < 0 || col >= A.n || col < 0)
        return NULL_MATRIX;

    // Return [1] on matrix with dimension of 1
    if (A.m == 1 || A.n == 1)
        return doubleToMat(1);

    Matrix minorA = emptyMat(A.m - 1, A.n - 1);

    // Copy data to minor
    for (int i = 0; i < minorA.m; i++) {
        for (int j = 0; j < minorA.n; j++) {
            // For data or original matrix, add 1 to indicies after row, col
            // to be removed
            minorA.data[i][j] = A.data[i + (i >= row)][j + (j >= col)];
        }
    }

    return minorA;
}

// -- Binary operations --
Matrix coeffMat(double coeff, Matrix A) {
    Matrix coeffA = copyMat(A);

    for (int i = 0; i < coeffA.m; i++) {
        for (int j = 0; j < coeffA.n; j++) {
            coeffA.data[i][j] *= coeff;
        }
    }

    return coeffA;
}

Matrix addMat(Matrix A, Matrix B) {
    // Return early on mismatched dimenstions
    if ((A.m != B.m) || (A.n != B.n))
        return NULL_MATRIX;

    Matrix C = emptyMat(A.m, A.n);

    for (int i = 0; i < A.m; i++) {
        for (int j = 0; j < A.n; j++) {
            C.data[i][j] = A.data[i][j] + B.data[i][j];
        }
    }

    return C; // must be freed
}

Matrix mulMat(Matrix A, Matrix B) {
    // Return early on mismatched dimenstions
    if (A.n != B.m)
        return NULL_MATRIX;

    Matrix C = emptyMat(A.m, B.n);

    // Iterate through rows and cols of new matrix
    for (int row = 0; row < A.m; row++) {
        for (int col = 0; col < B.n; col++) {
            // Calculate product
            for (int i = 0; i < A.n; i++) {
                C.data[row][col] += A.data[row][i] * B.data[i][col];
            }
        }
    }

    return C; // must be freed
}

// -- Special arithmetic --
double determinant(Matrix A) {
    // Return early on bad dimenstions
    if (!isSquare(A))
        return 0;

    // Base cases (1x1 or 2x2)
    if (A.m == 1) { // Determinant of 1x1 is itself
        return A.data[0][0];
    } else if (A.m == 2) { // Determinant of 2x2 is "ad - bc"
        return (A.data[0][0] * A.data[1][1]) - (A.data[0][1] * A.data[1][0]);
    }

    // Recursive case (nxn, n > 2)
    double detA = 0;

    // Uses first row for determinant
    for (int i = 0; i < A.n; i++) {
        int sign = (i % 2) ? -1 : 1; // determine sign of term
        Matrix minorA = minor(A, 0, i); // create minor at index

        // Add determinant of minor to total
        detA += sign * A.data[0][i] * determinant(minorA);

        deleteMat(&minorA); // delete minor
    }

    return detA;
}

double trace(Matrix A) {
    // Return early on bad dimenstions
    if (!isSquare(A))
        return 0;

    double traceA = 0;

    for (int i = 0; i < A.m; i++)
        traceA += A.data[i][i];

    return traceA;
}
