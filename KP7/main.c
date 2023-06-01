#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "spmatrix.h"

void startMenu(void) {
    printf("1. Ввести новую матрицу.\n");
    printf("2. Выбрать матрицу из списка.\n");
    printf("3. Выход.\n");
}

void chooseMatrix(sparseMatrix** matrixList) {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (matrixList[i] == NULL || isNilElement(&matrixList[i]->vector[0])) {
            break;
        }
        printf("%3d)\n", i + 1);
        printSparseAsDense(matrixList[i]);
    }
    printf("Выберите матрицу: ");
}

void actionMenu(void)
{
    printf("    1. Умножить матрицу на число.\n");
    printf("    2. Разделить на максимальный элемент матрицы.\n");
    printf("    3. Напечатать разреженную матрицу.\n");
    printf("    4. Напечатать матрицу.\n");
    printf("    5. Выход.\n");
}

int main(int argc, char** argv)
{
    bool isFile = false;
    char filename[MAX_LEN];
    FILE* inputStream;
    if (argc == 2) {
        isFile = true;
        strncpy(filename, argv[1], MAX_LEN);
        inputStream = fopen(filename, "r");
        if (inputStream == NULL) {
            perror("Error");
            exit(ENOENT);
        }
    }
    else if (argc == 1) {
        inputStream = stdin;
    }
    else {
        exit(1);
    }

    sparseMatrix** matrixList = calloc( MAX_SIZE, sizeof(sparseMatrix*) );

    if ( isFile ) {
        while ( true ) {
            sparseMatrix* matrix = initSparseMatrix();
            int readRet = 0;
            readRet = readSparseMatrix(matrix, inputStream);
            if ( readRet != 1 ) {
                if ( readRet == -3 ) { // Matrix was too big
                    freeSparseMatrix(matrix);
                    continue;
                }
                break;
            }
            addToList(matrixList, matrix);
        }
        fclose(inputStream);
    } 
    int option;
    do {
        startMenu();
        scanf("%d", &option);
        switch (option) {
            case 1: {
                sparseMatrix* matrix = initSparseMatrix();
                readSparseMatrix(matrix, stdin);
                addToList(matrixList, matrix);
                printf("Added.\n");
                break;
            }
            case 2: {
                int matrixChoice;
                chooseMatrix(matrixList);
                scanf("%d", &matrixChoice);
                if (matrixChoice < 1) {
                    fprintf(stderr, "Неправильный ввод.\n");
                    break;
                }
                sparseMatrix* currentMatrix; 
                if ( ( currentMatrix = matrixList[matrixChoice - 1] ) == NULL ) {
                    printf("В списке такой матрицы нет.\n");
                    break;
                }
                do {
                    actionMenu();
                    scanf("%d", &matrixChoice);
                    switch (matrixChoice) {
                        case 1: { // Multiply by a value
                            int coeff;
                            printf("Введите коэффициент: ");
                            scanf("%d", &coeff);
                            multiplyByConstant(currentMatrix, coeff);
                            break;
                        }
                        case 2: {
                            double a; // Coefficient
                            a = findMaxInMatrix(currentMatrix);
                            multiplyByConstant(currentMatrix, 1/a);
                            addToList(matrixList, currentMatrix);
                            break;
                        }
                        case 3: {
                            printSparseMatrix(currentMatrix);
                            break;
                        }
                        case 4: {
                            printSparseAsDense(currentMatrix);
                            break;
                        }
                        case 5: {
                            break;
                        }
                    }
                } while (matrixChoice != 0);
                break;
            }
            case 3: {
                break;
            }
        }
    } while (option != 0);

    for (int i = 0; i < MAX_SIZE; i++) {
        if ( matrixList[i] == NULL ) {
            break;
        }
        freeSparseMatrix(matrixList[i]);
    }
    free(matrixList);
    
    return 0;
}
