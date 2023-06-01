#ifndef __SPMATRIX_H__
#define __SPMATRIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define VECTOR_DEFAULT_SIZE 20
#define VECTOR_MAX_ELEMENTS 100
#define MAX_LEN 250
#define MAX_SIZE 100

typedef union {
    int row;
    double value;
} secondCell;

typedef struct {
    int qualifier;
    secondCell data;
} vectorElement;

typedef struct _sparse_matrix {
    vectorElement* vector;
    int vectorSize;
    size_t vectorAllocatedSize;
    int rows, cols;
    int (*pushBack)(struct _sparse_matrix*, int, int, double);
} sparseMatrix;

static const vectorElement NilElem = { 0, {0} };

void addToList(sparseMatrix** matrixList, sparseMatrix* matrix);

sparseMatrix* initSparseMatrix(void);

int pushBack(sparseMatrix* matrix, int row, int col, double data);

double get(sparseMatrix* matrix, int row, int col);

int find(sparseMatrix* matrix, int row, int col);

int isNilElement(vectorElement* element);

int multiplyByConstant(sparseMatrix* matrix, double constant);

int findMaxInMatrix(sparseMatrix* matrix);

int readSparseMatrix(sparseMatrix* matrix, FILE* stream);

int printSparseMatrix(sparseMatrix* matrix);

int printSparseAsDense(sparseMatrix* matrix);

int freeSparseMatrix(sparseMatrix* matrix);

#endif  
