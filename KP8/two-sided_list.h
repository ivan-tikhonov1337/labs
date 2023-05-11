#ifndef MYLIST_H
#define MYLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Структура для представления комплексных чисел
typedef struct complexes {
    float real;
    float imaginary;
} Complex;

// Структура для представления узлов списка
typedef struct node {
    Complex data;
    struct node* next;
    struct node* prev;
} Node;

// Функция для создания нового узла
Node* CreateNode(Complex val);

// Функция для вывода списка на экран
void PrintList(Node* head);

// Функция для вставки нового узла в начало списка
Node* InsertAtBeginning(Node* head, Complex val);

// Функция для вставки нового узла в конец списка
Node* InsertAtEnd(Node* head, Complex val);

// Функция для удаления узла из списка
Node* DeleteNode(Node* head, Complex val);
// Функция для подсчета длины списка
int Length(Node* head);

// Функция для дополнения списка до указанной длины копиями переданного значения
Node* AddToLength(Node* head, Complex val, int k);
 
#endif
