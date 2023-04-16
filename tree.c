#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {                    //структура узла дерева
    int data;
    struct node *left;
    struct node *right;
};

struct node* create_node(int data) {                                    //функция создания нового узла
    struct node *new_node = (struct node*) malloc(sizeof(struct node)); //выделение памяти под новый узел
    new_node->data = data;                                              //инициализация данных нового узла
    new_node->left = NULL;                                              //инициализация левого поддерева нового узла
    new_node->right = NULL;                                             //инициализация правого поддерева нового узла
    return new_node;                                                    //возвращаем указатель на новый узел
}

struct node* add_node(struct node *root, int data) {       //функция добавления нового узла в дерево
    if(root == NULL) {                                     //если дерево пустое, то создаем новый узел и возвращаем его
        return create_node(data);
    } else if(data < root->data){                          //если значение нового узла меньше значения текущего узла, то рекурсивно вызываем функцию для левого поддерева
        root->left = add_node(root->left, data);
    } else if(data > root->data){                          //если значение нового узла больше значения текущего узла, то рекурсивно вызываем функцию для правого поддерева
        root->right = add_node(root->right, data);
    }
    return root;                                           //возвращаем указатель на корень дерева
}

struct node* find_min_node(struct node *root) {            //функция поиска минимального элемента в дереве
    while(root->left != NULL){
        root = root->left;
    }
    return root;
}

struct node* delete_node(struct node *root, int data) {    //функция удаления узла из дерева
    if(root == NULL){                                      //если дерево пустое, то возвращаем NULL
        return NULL;
    } else if(data < root->data) {                         //если значение удаляемого узла меньше значения текущего узла, то рекурсивно вызываем функцию для левого поддерева
        root->left = delete_node(root->left, data);
    } else if(data > root->data) {                         //если значение удаляемого узла больше значения текущего узла, то рекурсивно вызываем функцию для правого поддерева
        root->right = delete_node(root->right, data);
    } else {                                               //если найден узел для удаления
        if(root->left == NULL && root->right == NULL) {    //если у удаляемого узла нет потомков
            free(root);                                    //освобождаем память
            return NULL;
        } else if(root->left == NULL) {                    //если у удаляемого узла есть только правый потомок
            struct node *temp = root->right;               //сохраняем правый потомок во временную переменную
            free(root);                                    //освобождаем память
            return temp;
        } else if(root->right == NULL) {                   //если у удаляемого узла есть только левый потомок
            struct node *temp = root->left;                //сохраняем левый потомок во временную переменную
            free(root);                                    //освобождаем память
            return temp;
        }
        else {                                                  //если у удаляемого узла есть оба потомка
            struct node *temp = find_min_node(root->right);     //находим минимальный узел в правом поддереве удаляемого узла
            root->data = temp->data;                            //заменяем значение удаляемого узла на значение минимального узла
            root->right = delete_node(root->right, temp->data); //рекурсивно вызываем функцию для удаления минимального узла в правом поддереве удаляемого узла
        }
    }
    return root;                                           //возвращаем указатель на корень дерева
}

void print_tree(struct node *root, int n) {                     // Функция вывода дерева
    if (root != NULL) {                                         // Если дерево не пустое, то
        print_tree(root->right, n + 1);                         // Функция рекурсивно будет открывать правое поддерево
        for (int i = 0; i < n; i++) printf("\t");               // в зависимости от глубины вершины, мы будем увеличивать отступы
        printf("%d\n", root->data);                             // печатаем значение вершины
        print_tree(root->left, n + 1);                          // Функция рекурсивно будет открывать левое поддерево
    }
}
