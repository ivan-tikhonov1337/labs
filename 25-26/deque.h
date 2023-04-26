#ifndef _UDT_H_
#define _UDT_H_

#include <stdbool.h>

typedef struct {
    int first;
    int last;
    int size;
    int arr[10];
} udt;

udt* create_udt(udt *);

bool udt_empty(const udt *);

bool udt_push_front(udt *, int);

bool udt_push_back(udt *, int);

bool udt_pop_front(udt *);

bool udt_pop_back(udt *);

int udt_top_left(udt *);

int udt_top_right(udt *);

void udt_print(udt *);

int udt_size(const udt *);

#endif
