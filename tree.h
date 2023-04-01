#ifndef MYTREE_H
#define MYTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct binaryTree {                      //Создаем структуру узла для дерева
    int data;                                    //Значение узла
    struct Tree *left;                           //Левая ветка
    struct Tree *right;                          //Правая ветка
    struct Tree *parent;                         //Родитель
}Tree;                                           //запишем так, чтобы не писать каждый раз struct ...

Tree *node_create(int value);

Tree *add_Node(Tree *node, int value);

void tree_print(Tree *root, int n);

Tree *search_in_tree(Tree *root, int value);

Tree *minimum(Tree *tree);

Tree *delete_element(Tree *tree, int value;

void print_menu();

bool is_Level_Leaf(Tree *tree, int level, int *leafLevel;

#endif
