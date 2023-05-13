#ifndef MYLIST_H
#define MYLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

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

// Функция для удаления узла из списка
Node* DeleteAtIndex(Node* head, int index);


// Функция для подсчета длины списка
int Length(Node* head);

// Функция для дополнения списка до указанной длины копиями переданного значения
Node* AddToLength(Node* head, Complex val, int k);

void DeleteList(Node* head);

Node* InsertAtIndex(Node* head, Complex val, int index);
 
#endif
