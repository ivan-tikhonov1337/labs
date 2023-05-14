#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 7
#define MAX_SIZE 14

struct node {
    char key[MAX_LENGTH];
    char data[MAX_LENGTH];
};

void print_table(struct node table[], int size);

void bubble_sort(struct node table[], int size);

int binary_search(struct node table[], int size, char key[]);
