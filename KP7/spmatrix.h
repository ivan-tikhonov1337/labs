#ifndef __SPMATRIX_H__
#define __SPMATRIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

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
} sparseMatrix;

static const vectorElement NilElem = { 0, {0} };

void Add_To_List(sparseMatrix** matrixList, sparseMatrix* matrix);

sparseMatrix* Init_Sparse_Matrix(void);

int Push_Back(sparseMatrix* matrix, int row, int col, double data);

double Get(sparseMatrix* matrix, int row, int col);

int Find(sparseMatrix* matrix, int row, int col);

int Is_Nil_Element(vectorElement* element);

int Multiply_By_Constant(sparseMatrix* matrix, double constant);

int Multiply_Column_By_Constant(sparseMatrix* matrix, double constant, int column);

secondCell Find_Max_In_Matrix(sparseMatrix* matrix);

int Read_Sparse_Matrix(sparseMatrix* matrix, FILE* stream);

int Print_Sparse_Matrix(sparseMatrix* matrix);

int Print_Sparse_As_Dense(sparseMatrix* matrix);

int Free_Sparse_Matrix(sparseMatrix* matrix);

#endif  
