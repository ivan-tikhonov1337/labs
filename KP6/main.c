#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <base.h>

int main(int argc, char *argv[]) {
    int number;
    if (argc != 2) {
        printf("Usage:\n\t./execute DB_FILE\n");
        exit(0);
    }

    Passenger passengers[DB_SIZE];
    int n = 0;

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        printf("I/O Error: can't open file.\n");
        exit(1);
    }
    while (passenger_read_txt(&passengers[n], in)) {
        n++;
    }

    while (1) {
        printf("Выберите действие, которое хотите выполнить:\n");
        printf("1. Добавить пассажира\n");
        printf("2. Удалить пассажира\n");
        printf("3. Вывести информацию о пассажире\n");
        printf("4. Вывести всю базу данных\n");
        printf("5. Вывести всех пассажиров с количеством вещей больших, чем p\n");
        printf("6. Выход\n");
        printf("Ваш выбор: ");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                insert_passenger(passengers, &n);
                break;
            case 2:
                delete_passenger(passengers, &n);
                break;
            case 3:
                select_passenger(passengers, n);
                break;
            case 4:
                print_passengers(passengers, n);
                break;
            case 5:
                printf("Введите количество вещей: ");
                int num_items;
                scanf("%d", &num_items);
                filter_by_num(passengers, n, num_items);
                break;
            case 6:
                return 0;
            default:
                printf("Выбрано не существующие действие.\n");
        }
    }

    return 0;
}
