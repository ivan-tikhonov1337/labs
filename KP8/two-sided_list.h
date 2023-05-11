#ifndef MYLIST_H
#define MYLIST_H

#include <stdio.h>
#include <stdlib.h>

// Определение структуры узла списка
struct node {
    float data;                                 // данные, которые хранятся в узле
    struct node *next;                          // указатель на следующий узел
    struct node *prev;                          // указатель на предыдущий узел
};

// Функция для создания нового узла списка
struct node* CreateNode(float val);

// Функция для вывода списка на экран
void PrintList(struct node* head);

// Функция для вставки нового узла в начало списка
struct node* InsertAtBeginning(struct node* head, float val;

// Функция для вставки нового узла в конец списка
struct node* InsertAtEnd(struct node* head, float val);
                               
// Функция для удаления узла из списка
struct node* DeleteNode(struct node* head, float val);

// Функция для подсчета длины списка
int Length(struct node* head;

struct node* AddToLength(struct node* head, float val, int k);
 
#endif
