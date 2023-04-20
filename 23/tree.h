#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {                    //структура узла дерева
    int data;
    struct node *left;
    struct node *right;
};

struct node* create_node(int data);

struct node* add_node(struct node *root, int data);

struct node* find_min_node(struct node *root);

struct node* delete_node(struct node *root, int data);

void print_tree(struct node *root, int n);

void free_tree(struct node* root);

void print_menu();

#endif
