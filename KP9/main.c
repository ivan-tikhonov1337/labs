#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

int main() {
    struct node table[MAX_SIZE];
    int size, i, choice;
    char key[MAX_LENGTH];
    printf("Введите количество элементов таблицы (от 12 до 14): ");
    scanf("%d", &size);
    if (size < 12 || size > 14) {
        printf("Ошибка: неверное количество элементов таблицы\n");
        return 1;
    }
    printf("Введите элементы таблицы:\n");
    for (i = 0; i < size; i++) {
        printf("Ключ и значение элемена %d:\n", i + 1);
        scanf("%s %s", table[i].key, table[i].data);
        printf("%s %s %d\n",table[i].key, table[i].data, strlen(table[i].key));
        if (strlen(table[i].key) > MAX_LENGTH) {
            printf("Ошибка: длина ключа не может превышать %d символов\n", MAX_LENGTH);
            return 1;
        }
    }
    printf("\n");
    printf("Исходное состояние таблицы:\n");
    print_table(table, size);
    printf("\n");
    while(1) {
        printf("Выберите действие:\n");
        printf("1. Отсортировать таблицу\n");
        printf("2. Поиск по таблице\n");
        printf("3. Вывести таблицу\n");
        printf("4. Выйти из программы\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Сортировка методом пузырька:\n");
                bubble_sort(table, size);
                print_table(table, size);
                break;
            case 2:
                printf("Поиск по таблице:\n");
                printf("Введите ключ для поиска: ");
                scanf("%s", key);
                int result = binary_search(table, size, key);
                if (result == -1) {
                    printf("Запись с ключом %s не найдена\n", key);
                }
                else {
                    printf("Найденная запись: %s %s\n", table[result].key, table[result].data);
                }
                break;
            case 3:
                print_table(table, size);
                break;
            case 4:
                return 0;
            default:
                printf("Неверный ввод\n");
                break;
        }
    }
    return 0;
}
