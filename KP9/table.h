#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 100

// структура одной записи
typedef struct Node {
    char key[7];             //ключ записи (размер ключа - 6 символов + символ конца строки)
    char* data;              //данные записи
    struct Node* next;       //указатель на следующий элемент списка
    struct Node* prev;       //указатель на предыдущий элемент списка
} Node;

// структура всего списка
typedef struct List {
    Node* head;             //указатель на первый элемент списка
    int size;               //количество элементов списка
    int sorted;             // -1 - по убыванию, 0 - неотсортирован, 1 - по возрастанию
} List;

// создание списка
List* Create_List();

void Read_Table(List* l, FILE* fp);

// добавление записи в конец списка
void Add_To_List(List* list, const char* key, const char* data);

// удаление последней записи из списка
void Table_Pop(List* list);

// получение указателя на первый элемент списка
Node* Begin_List(List* list);

// печать списка
void Table_Print(List* list);

// удаление списка
void Free_List(List* list);

// получение размера списка
int List_Size (List* list);

// получение указателя на элемент списка на определенной позиции
Node* Plus(Node* n, int x);

// обмен двух элементов списка
void Swap (List* list, int x, int y);

// Функция для сравнения двух ключей. Возвращает 0, если ключи равны, отрицательное число, если первый ключ меньше второго, и положительное число, если первый ключ больше второго.
int Compare_Keys(char* key1, char* key2);

// Функция для поиска узла по заданной позиции в списке. Возвращает узел по данной позиции.
Node* Find(List* list, int position);

// Функция для сортировки элементов в списке методом пузырька.
void Bubble_Sort(List* list);

// Функция для бинарного поиска элемента в списке. Возвращает значение элемента, если он найден, и NULL, если элемент не найден.
char* Binary_Search(List* list, char key[7]);

// Функция для разворота списка.
void Reverse_List(List* list);

// Функция для записи списка в файл.
void Write_List(FILE* fp, List* list);

// Функция для проверки, отсортирован ли список. Возвращает true, если список отсортирован, и false, если список не отсортирован.
bool Is_List_Sorted(List* list, bool asc_order);

void print_menu();
