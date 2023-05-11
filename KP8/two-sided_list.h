#ifndef MYLIST_H
#define MYLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Структура для представления комплексных чисел
struct complex {
    float real;
    float imaginary;
};

// Структура для представления узлов списка
struct node {
    struct complex data;
    struct node* next;
    struct node* prev;
};

// Функция для создания нового узла
struct node* CreateNode(struct complex val);

// Функция для вставки нового узла в начало списка
struct node* InsertAtBeginning(struct node* head, struct complex val);

// Функция для вставки нового узла в конец списка
struct node* InsertAtEnd(struct node* head, struct complex val);

// Функция для удаления узла из списка
struct node* DeleteNode(struct node* head, struct complex val);

// Функция для подсчета длины списка
int Length(struct node* head);

// Функция для дополнения списка до указанной длины копиями переданного значения
struct node* AddToLength(struct node* head, struct complex val, int k);
 
#endif
