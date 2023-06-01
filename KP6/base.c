#include "base.h"

int passenger_read_txt(Passenger *s, FILE *in) {
    fscanf(in, "%s", s->surname);
    fscanf(in, "%s", s->initials);
    fscanf(in, " %d", &(s->num));
    fscanf(in, "%d", &(s->weight));
    fscanf(in, "%s", s->to);
    fscanf(in, "%d:%d", &(s->time.hour), &(s->time.minute));
    fscanf(in, "%d", &(s->transfer));
    fscanf(in, "%d", &(s->child));
    return !feof(in);
}

int passenger_write_txt(Passenger *s, FILE *out) {
    fprintf(out, "%s ", s->surname);
    fprintf(out, "%s ", s->initials);
    fprintf(out, " %d ", (s->num));
    fprintf(out, "%d ", (s->weight));
    fprintf(out, "%s ", s->to);
    fprintf(out, "%d:%d ", (s->time.hour), (s->time.minute));
    fprintf(out, "%d ", (s->transfer));
    fprintf(out, "%d \n", (s->child));
    return !feof(out);
}

int passenger_read_bin(Passenger *s, FILE *in) {
    fread(s->surname,  sizeof(char), STR_SIZE, in);
    fread(s->initials, sizeof(char), STR_SIZE, in);
    fread(&(s->num), sizeof(int), 1, in);
    fread(&(s->weight), sizeof(int), 1, in);
    fread(s->to, sizeof(char), STR_SIZE, in);
    fread(&(s->time), sizeof(int), 2, in);
    fread(&(s->transfer), sizeof(int), 1, in);
    fread(&(s->child), sizeof(int), 1, in);

    return !feof(in);
}

void passenger_write_bin(Passenger *s, FILE *out) {
    fwrite(s->surname,  sizeof(char), STR_SIZE, out);
    fwrite(s->initials, sizeof(char), STR_SIZE, out);
    fwrite(&(s->num), sizeof(int), 1, out);
    fwrite(&(s->weight), sizeof(int), 1, out);
    fwrite(s->to, sizeof(char), STR_SIZE, out);
    fwrite(&(s->time), sizeof(int), 2, out);
    fwrite(&(s->transfer), sizeof(int), 1, out);
    fwrite(&(s->child), sizeof(int), 1, out);
}

void print_passenger(Passenger p) {
    printf("| %-10s | %-10s | %-5d | %-7d | %-15s | %02d:%02d | %-8d | %-5d |\n", p.surname, p.initials, p.num, p.weight, p.to, p.time.hour, p.time.minute, p.transfer, p.child);
}

void print_passengers(Passenger *passengers, int n) {
    printf("| %-10s | %-10s | %-5s | %-7s | %-15s | %-5s | %-8s | %-5s |\n", "Surname", "Initials", "Items", "Weight", "To", "Time", "Transfer", "Child");
    printf("+------------+------------+-------+---------+-----------------+-------+----------+-------+\n");
    for (int i = 0; i < n; i++) {
        print_passenger(passengers[i]);
    }
    printf("+------------+------------+-------+---------+-----------------+-------+----------+-------+\n");
}

void insert_passenger(Passenger *passengers, int *n, char *filename) {
    int go = 1;
    Passenger p;
    printf("Введите данные о новом пассажире:\n");
    printf("Фамилия: ");
    scanf("%s", p.surname);
    printf("Инициалы: ");
    scanf("%s", p.initials);
    for (int i = 0; i < *n; i++) {
        if (strcmp(passengers[i].surname, p.surname) == 0) {
            if (strcmp(passengers[i].initials, p.initials) == 0) {
                printf("Такой пассажир уже существует.");
            go = 0;
            break;
            }
        }
    }
    if (go) {
        printf("Количество вещей: ");
        scanf("%d", &p.num);
        printf("Вес багажа: ");
        scanf("%d", &p.weight);
        printf("Куда: ");
        scanf("%s", p.to);
        printf("Время (чч:мм): ");
        scanf("%d:%d", &p.time.hour, &p.time.minute);
        printf("Пересадки: ");
        scanf("%d", &p.transfer);
        printf("Дети: ");
        scanf("%d", &p.child);
        passengers[*n] = p;
        (*n)++;
        FILE *out = fopen(filename, "a");
        passenger_write_txt(&p, out);
        fclose(out); 
    }   
}

void delete_passenger(Passenger *passengers, int *n, char *filename) {
    char surname[STR_SIZE], initials[STR_SIZE];
    printf("Введите фамилию пассажира, которого нужно удалить: \n");
    scanf("%s", surname);
    printf("Введите инициалы пассажира, которого нужно удалить: \n");
    scanf("%s", initials);
    int i = 0;
    for (; i < *n; i++) {
        if (strcmp(passengers[i].surname, surname) == 0) {
            if (strcmp(passengers[i].initials, initials) == 0)
                break;
        }
    }
    if (i == *n) {
        printf("Пассажир не найден.\n");
        return;
    }
    for (int j = i; j < *n - 1; j++) {
        passengers[j] = passengers[j + 1];
    }
    (*n)--;
    FILE *out = fopen(filename, "w");
    for (int i = 0; i < *n; i++) {
        passenger_write_txt(&passengers[i], out);
    }
    fclose(out);
}

void select_passenger(Passenger *passengers, int n) {
    printf("Введите фамилию пассажира, информацию о котором нужно вывести: ");
    char surname[STR_SIZE];
    scanf("%s", surname);
    printf("| %-10s | %-10s | %-5s | %-7s | %-15s | %-5s | %-8s | %-5s |\n", "Surname", "Initials", "Items", "Weight", "To", "Time", "Transfer", "Child");
    printf("+------------+------------+-------+---------+-----------------+-------+----------+-------+\n");
    for (int i = 0; i < n; i++) {
        if (strcmp(passengers[i].surname, surname) == 0) {
            print_passenger(passengers[i]);
            return;
        }
    }
    printf("Пассажир с такой фамилией не найден.\n");
}

void filter_by_num(Passenger *passengers, int n, int num_items) {
    printf("| %-10s | %-10s | %-5s | %-7s | %-15s | %-5s | %-8s | %-5s |\n", "Surname", "Initials", "Items", "Weight", "To", "Time", "Transfer", "Child");
    printf("+------------+------------+-------+---------+-----------------+-------+----------+-------+\n");
    for (int i = 0; i < n; i++) {
        if (passengers[i].num > num_items) {
            print_passenger(passengers[i]);
        }
    }
    printf("+------------+------------+-------+---------+-----------------+-------+----------+-------+\n");
}
