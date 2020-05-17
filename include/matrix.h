//
//  matrix.h
//  Header for matrix arithmetic operations.
//
//  Created by Zakhary Kaplan on 2019-04-28.
//  Copyright © 2019 Zakhary Kaplan. All rights reserved.
//

#ifndef MATRIX_H
#define MATRIX_H

#define NULL_MATRIX \
    (Matrix) { 0, 0, 0 }

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
