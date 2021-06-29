// File:        matrix.h
// Author:      Zakhary Kaplan <https://zakharykaplan.ca>
// Created:     28 Apr 2019
// SPDX-License-Identifier: NONE

#ifndef MATRIX_H
#define MATRIX_H

#define NULL_MATRIX \
    (Matrix) {      \
        0, 0, 0     \
    }

// Declare matrix structure
typedef struct matrix {
    int m, n;
    double **data;
} Matrix;

// Function prototypes
Matrix identityMat(int);
Matrix emptyMat(int, int);
Matrix doubleToMat(double);
Matrix copyMat(Matrix);
void deleteMat(Matrix *);
void printMat(Matrix);
int isNull(Matrix);
int isSquare(Matrix);
// Unary Operations
Matrix transpose(Matrix);
Matrix inverse(Matrix);
Matrix minor(Matrix, int, int);
// Binary Operations
Matrix coeffMat(double, Matrix);
Matrix addMat(Matrix, Matrix);
Matrix mulMat(Matrix, Matrix);
// Special Arithmetic
double determinant(Matrix);
double trace(Matrix);

#endif
