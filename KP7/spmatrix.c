#include "spmatrix.h"

void Add_To_List(sparseMatrix** matrixList, sparseMatrix* matrix) {
    for (int index = 0; index < MAX_SIZE; index++) {
        if ( matrixList[index] == NULL && !Is_Nil_Element( &matrix->vector[0] ) ) {
            matrixList[index] = matrix;
            return;
        }
    }
}

//Функция создает и возвращает пустую разреженную матрицу
sparseMatrix* Init_Sparse_Matrix(void) {
    //Выделяем память под структуру sparseMatrix
    sparseMatrix* matrix = malloc( sizeof(sparseMatrix) );
    //Задаем количество элементов вектора по умолчанию
    matrix->vectorAllocatedSize = VECTOR_DEFAULT_SIZE;
    //Выделяем память под вектор
    matrix->vector = calloc( matrix->vectorAllocatedSize, sizeof(vectorElement) );
    //Задаем начальные значения для матрицы
    matrix->rows = 0;
    matrix->cols = 0;
    matrix->vectorSize = 0;
    return matrix;
}

int Is_Nil_Element(vectorElement* element) {
    return memcmp(element, &NilElem, sizeof(vectorElement)) == 0;
}


//Функция добавляет элемент в конец разреженной матрицы
int Push_Back(sparseMatrix* matrix, int row, int col, double data) {
    //Если вектор полностью заполнен, возвращаем ошибку
    if ( matrix->vectorSize == VECTOR_MAX_ELEMENTS ) {
        return -1;
    }
    //Если добавляемый элемент равен 0 и его столбец не совпадает с последним столбцом матрицы, возвращаем 0
    if ( data == 0 && matrix->cols != col ) {
        return 0;
    }

    //Объявляем указатель на вектор matrux->vector
    vectorElement* vector = matrix->vector;

    //Если вектор почти заполнен, увеличиваем его размер в два раза
    if ( matrix->vectorSize + 1 >= matrix->vectorAllocatedSize ) {
        matrix->vectorAllocatedSize *= 2;
        matrix->vector = realloc(matrix->vector, matrix->vectorAllocatedSize * sizeof(vectorElement));
    }

    //Если вектор пуст, добавляем первый элемент
    if ( memcmp(&vector[0], &NilElem, sizeof(vectorElement) ) == 0) {
        // предыдущий элемент равен нулю
        vectorElement initElement = { 0, { .row = 1 } };
        matrix->vector[0] = initElement;
        matrix->vectorSize++;
    }

    int index = matrix->vectorSize;

    vectorElement prevElement = vector[index - 1];
    vectorElement newElement     = { col, { .value  = data } };
    vectorElement closureElement = {   0, { .row = row + 1 } };

    //Если добавляемый элемент равен 0 и его столбец совпадает с последним столбцом матрицы, добавляем элемент-заполнитель
    if ( data == 0 && matrix->cols == col ) {
        vector[index - 1] = closureElement;
        return 1;
    }

    //Добавляем элемент-заполнитель
    if ( prevElement.qualifier == 0 && prevElement.data.row == row ) {
        vector[index] = newElement;
        matrix->vectorSize++;
        vector[index + 1] = closureElement;
        matrix->vectorSize++;
    } else {
        vector[index - 1] = newElement;
        matrix->vectorSize++;
        vector[index] = closureElement;
    }

    return 1;
}

//Функция возвращает значение элемента матрицы по его индексам
double Get(sparseMatrix* matrix, int row, int col) {
    int index = Find(matrix, row, col);
    if (index == -1) {
        return 0;
    } else {
        return matrix->vector[index].data.value;
    }
}

//Функция ищет индекс элемента матрицы по его индексам
int Find(sparseMatrix* matrix, int row, int col) {
    int currentRow = 0;
    for (int index = 0; index < matrix->vectorSize; index++) {
        vectorElement currentElement = matrix->vector[index];
        if (currentElement.qualifier == 0) {
            currentRow = currentElement.data.row;
            continue;
        }
        if (currentElement.qualifier != col) {
            continue;
        }
        if (currentRow == row) {
            return index;
        }
    }
    return -1;
}

//Функция умножает каждый элемент матрицы на заданную константу
int Multiply_By_Constant(sparseMatrix* matrix, double constant) {
    vectorElement* vector = matrix->vector;
    for (int i = 0; i < matrix->vectorSize; i++) {
        if (vector[i].qualifier == 0) {
            continue;
        }
        vector[i].data.value *= constant;
    }
    return 0;
}

int Multiply_Column_By_Constant(sparseMatrix* matrix, double constant, int column) {
    vectorElement* vector = matrix->vector;
    for (int i = 0; i < matrix->vectorSize; i++) {
        if (vector[i].qualifier == 0) {
            continue;
        }
        if (vector[i].qualifier == column)
            vector[i].data.value *= constant;
    }
    return 0;
}

//Функция считывает разреженную матрицу из файла
int Read_Sparse_Matrix(sparseMatrix* matrix, FILE* stream) {
    if (stream == NULL) {
        perror("Не удалось прочитать матрицу\n");
        return -1;
    }
    if (feof(stream)) {
        return -2;
    }
    int rows, cols;
    if (stream == stdin) {
        printf("Введите количество строк и столбцов: ");
        fflush(stream);
    }
    if (fscanf(stream, "%d %d", &rows, &cols) != 2) {
        return -2; // Не удалось прочитать размер матрицы, поэтому предположим, что это конец файла
    }
    if (stream == stdin) {
        printf("Введите матрицу в стандартном формате:\n");
    }
    matrix->rows = rows;
    matrix->cols = cols;
    int pushRet = 0;
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            double value;
            fscanf(stream, "%lf", &value);
            pushRet = Push_Back(matrix, i, j, value);
        }
    }
    if (pushRet == -1) {
        fprintf(stderr, "Error: Vector '%p' has reached element limit.\n", matrix->vector);
        return -3;
    }
    //Добавляем в конец вектора элемент-заполнитель NilElem
    matrix->vector[matrix->vectorSize - 1] = NilElem;
    matrix->vectorAllocatedSize = matrix->vectorSize;
    matrix->vector = realloc(matrix->vector, matrix->vectorAllocatedSize * sizeof(vectorElement));
    return 1;
}

//Функция находит максимальный элемент и его столбец
secondCell Find_Max_In_Matrix(sparseMatrix* matrix) {
    int count = 1;
    secondCell a,b;
    vectorElement elem = matrix->vector[0];
    a.row = elem.qualifier;
    a.value = elem.data.value;
    for (int i = 1; i < VECTOR_DEFAULT_SIZE; i++) {
        vectorElement elem = matrix->vector[i];
        if (elem.data.value == a.value)
            b = a;
        if (elem.data.value >= a.value) {
            a.value = elem.data.value;
            a.row = elem.qualifier;
        }
        if ( Is_Nil_Element(&elem) ) {
            // элемент равен нулю 
            break;
        }
    }
    if (count > 1)
        return b;
    else
        return a;
}

//Функция выводит разреженную матрицу на экран
int Print_Sparse_Matrix(sparseMatrix* matrix) {
    for (int i = 0; i < VECTOR_DEFAULT_SIZE; i++) {
        vectorElement elem = matrix->vector[i];
        if (elem.qualifier == 0) {
            // данные представляют собой int (хранятся в поле "столбец").
            int row = elem.data.row;
            if ( row ) {
                printf("(следующая строка: %d)\n", row);
            }
            else {
                printf("(Размер вектора: %d)\n", matrix->vectorSize);
            }
        } else {
            // данные являются двойными (хранятся в поле `значение`)
            double value = elem.data.value;
            printf("(Столбец: %d, значение: %.2lf)\n", elem.qualifier, value);
        }
        if ( Is_Nil_Element(&elem) ) {
            // элемент равен нулю 
            break;
        }
    }
    return 0;
}

//Функция выводит разреженную матрицу на экран в плотном формате
int Print_Sparse_As_Dense(sparseMatrix* matrix) {
    for (int i = 1; i <= matrix->rows; i++) {
        for (int j = 1; j <= matrix->cols; j++) {
            printf("%5.1lf  ", Get(matrix, i, j));
        }
        printf("\n");
    }
    return 0;
}

//Функция освобождает память, выделенную под разреженную матрицу
int Free_Sparse_Matrix(sparseMatrix* matrix) {
    if (matrix == NULL) {
        return -1;
    }
    free(matrix->vector);
    matrix->vector = NULL;
    free(matrix);
    return 0;
}
