void print_table(struct node table[], int size) {
    int i;
    printf("Таблица:\n");
    for (i = 0; i < size; i++) {
        printf("%s %s\n", table[i].key, table[i].data);
    }
}

void bubble_sort(struct node table[], int size) {
    int i, j;
    struct node temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (strcmp(table[j].key, table[j+1].key) > 0) {
                temp = table[j];
                table[j] = table[j+1];
                table[j+1] = temp;
            }
        }
    }
}

int binary_search(struct node table[], int size, char key[]) {
    int first = 0;
    int last = size - 1;
    int middle = (first + last) / 2;
    while (first <= last) {
        if (strcmp(table[middle].key, key) < 0) {
            first = middle + 1;
        }
        else if (strcmp(table[middle].key, key) == 0) {
            return middle;
        }
        else {
            last = middle - 1;
        }
        middle = (first + last) / 2;
    }
    return -1;
}
