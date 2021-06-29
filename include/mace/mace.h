// File:        mace.h
// Author:      Zakhary Kaplan <https://zakharykaplan.ca>
// Created:     25 Apr 2019
// SPDX-License-Identifier: NONE

#ifndef MACE_H
#define MACE_H

#include "matrix.h"

#define MAX 100
#define WORKSPACE_SIZE 64
#define ANS -99

// Function prototypes
void mace(void);
// Secondary functions
int validateInput(char *[]);
void printEntry(int, Matrix[], int);
void printAns(Matrix);
void addToWorkspace(int *, Matrix[], Matrix);
int tagExists(int *, char *[], char[]);
// Commands
void help(char[]);
void print(char[], int, Matrix[], Matrix);
void clr(int *, Matrix[], Matrix *);
Matrix mat(char[], Matrix);
Matrix ident(char input[]);
Matrix zeros(char[]);
Matrix add(char[], Matrix[], Matrix);
Matrix sub(char[], Matrix[], Matrix);
Matrix mul(char[], Matrix[], Matrix);
Matrix scl(char[], Matrix[], Matrix);
Matrix trnsp(char[], Matrix[], Matrix);
Matrix inv(char[], Matrix[], Matrix);
Matrix det(char[], Matrix[], Matrix);
Matrix trc(char[], Matrix[], Matrix);

#endif
