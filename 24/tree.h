#ifndef tree_h
#define tree_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct unit {
       char data [50];
       struct unit *left;
       struct unit *right;
} unit;

int define_priority (char a);

unit *make_tree(char expr[], int first, int last);

void print_tree(unit *u, int l);

void print_expression(unit *u);

unit *spec_func(unit *u);

void tree_free(unit *u);

#endif
