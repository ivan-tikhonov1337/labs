#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "spmatrix.h"

void Start_Menu(void) {
    printf("\n1. Ввести новую матрицу.\n");
    printf("2. Выбрать матрицу из списка.\n");
    printf("3. Выход.\n");
}

void Choose_Matrix(sparseMatrix** matrixList) {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (matrixList[i] == NULL || Is_Nil_Element(&matrixList[i]->vector[0])) {
            break;
        }
        printf("%3d)\n", i + 1);
        Print_Sparse_As_Dense(matrixList[i]);
    }
    printf("Выберите матрицу: ");
}

void Action_Menu(void) {
    printf("\n1. Умножить матрицу на число.\n");
    printf("2. Разделить на максимальный элемент матрицы.\n");
    printf("3. Напечатать разреженную матрицу.\n");
    printf("4. Напечатать матрицу.\n");
    printf("5. Выход.\n");
}

int main(int argc, char** argv) {
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
    } else if (argc == 1) {
        inputStream = stdin;
    } else {
        exit(1);
    }

    sparseMatrix** matrixList = calloc( MAX_SIZE, sizeof(sparseMatrix*) );

    if (isFile) {
        while (true) {
            sparseMatrix* matrix = Init_Sparse_Matrix();
            int readRet = 0;
            readRet = Read_Sparse_Matrix(matrix, inputStream);
            if ( readRet != 1 ) {
                if ( readRet == -3 ) { // Матрица слишком большая
                    Free_Sparse_Matrix(matrix);
                    continue;
                }
                Free_Sparse_Matrix(matrix);
                break;
            }
            Add_To_List(matrixList, matrix);
        }
        fclose(inputStream);
    } 
    int option;
    do {
        Start_Menu();
        scanf("%d", &option);
        switch (option) {
            case 1: {
                sparseMatrix* matrix = Init_Sparse_Matrix();
                Read_Sparse_Matrix(matrix, stdin);
                Add_To_List(matrixList, matrix);
                printf("Матрица добавлена.\n");
                break;
            }
            case 2: {
                int matrixChoice;
                Choose_Matrix(matrixList);
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
                    Action_Menu();
                    scanf("%d", &matrixChoice);
                    switch (matrixChoice) {
                        case 1: { 
                            double coeff;
                            printf("Введите коэффициент: ");
                            scanf("%lf", &coeff);
                            Multiply_By_Constant(currentMatrix, coeff);
                            break;
                        }
                        case 2: {
                            secondCell b;
                            b = Find_Max_In_Matrix(currentMatrix);
                            Multiply_Column_By_Constant(currentMatrix, 1/(b.value), b.row);
                            break;
                        }
                        case 3: {
                            Print_Sparse_Matrix(currentMatrix);
                            break;
                        }
                        case 4: {
                            Print_Sparse_As_Dense(currentMatrix);
                            break;
                        }
                        case 5: {
                            break;
                        }
                    }
                } while (matrixChoice != 5);
                break;
            }
            case 3: {
                break;
            }
        }
    } while (option != 3);
    for (int i = 0; i < MAX_SIZE; i++) {
        if ( matrixList[i] != NULL ) {
            Free_Sparse_Matrix(matrixList[i]);
        }        
    }
    free(matrixList);
    return 0;
}
