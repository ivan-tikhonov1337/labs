#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define STR_SIZE 24
#define DB_SIZE 100

typedef struct{
    int hour, minute;
} TIME;

typedef struct {
    char surname[STR_SIZE];
    char initials[STR_SIZE];
    int num;
    int weight;
    char to[STR_SIZE];
    TIME time;
    int transfer;
    int child;
} Passenger;

int passenger_read_txt(Passenger *s, FILE *in);

int passenger_read_bin(Passenger *s, FILE *in);

void passenger_write_bin(Passenger *s, FILE *out);

void print_passenger(Passenger p);

void print_passengers(Passenger *passengers, int n);

void insert_passenger(Passenger *passengers, int *n);

void delete_passenger(Passenger *passengers, int *n;

void select_passenger(Passenger *passengers, int n);

void filter_by_num(Passenger *passengers, int n, int num_items);

#endif
