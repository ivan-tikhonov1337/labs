#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"


int main(int argc, char *argv[]) {
    List* l = Create_List();
    FILE *in = fopen(argv[1], "r"); // открытие файла для чтения
    if (!in) {
        printf("I/O Error: can't open file.\n");
        Free_List(l);
        exit(1);
    }
    char *filename = argv[1];
    Read_Table(l, in); // чтение таблицы из файла
    fclose(in);
    if (Is_List_Sorted(l, true)) { // проверка на порядок сортировки
        l->sorted = 1;
    } else if (Is_List_Sorted(l, false)) {
        l->sorted = -1;
    } else {
        l->sorted = 0;
    }

    char what_do[STR_SIZE];
    print_menu();
    while (!feof(stdin)) {
        fscanf(stdin, "%s", what_do);
        if (feof(stdin)) {
            break;
        }
        if (!strcmp(what_do, "print")) {
            Table_Print(l);
        }else if (!strcmp(what_do, "add")) {
            char key[7];
            char data[STR_SIZE];
            scanf("%s", key);
            fgets(data, STR_SIZE, stdin);
            Add_To_List(l, key, data);
            l->sorted = 0;
            printf("Запись добавлена.\n");
        } else if (!strcmp(what_do, "remove")) {
            Table_Pop(l);
            printf("Последняя запись удалена.\n");
        } else if (!strcmp(what_do, "exit")) {
            break;
        } else if (!strcmp(what_do, "overwriting")) {
            FILE *out = fopen(filename, "w");
            Write_List(out, l);
            fclose(out);
        } else if (!strcmp(what_do, "find")) {
            char key[7];
            scanf("%s", key);
            if (l->sorted == 0) {
                printf("Отсортируйте, пожалуйста, список!\n");
            } else if (l->sorted == -1) {
                Reverse_List(l);
                char* result = Binary_Search(l, key);
                if (result == NULL) {
                    printf("Введённый ключ не найден.\n");
                } else {
                    printf("%s\n", result);
                }
            } else {
                char* result = Binary_Search(l, key);
                if (result == NULL) {
                    printf("Введённый ключ не найден.\n");
                } else {
                    printf("%s\n", result);
                }
            }
        } else if (!strcmp(what_do, "sort")) {
            Bubble_Sort(l);
            l->sorted = 1;
            printf("Список отсортирован:)\n");
        } else if (!strcmp(what_do, "issort")) {
            if (l->sorted == 1) {
                printf("Список отсортирован по возрастанию.\n");
            } else if (l->sorted == -1) {
                printf("Список отсортирован по убыванию.\n");
            } else {
                printf("Список не отсортирован.\n");
            }
        } else {
            printf("Введена неправильная команда.\n");
        }
        print_menu();
    }
    Free_List(l); // освобождение памяти, занятой списком
}
