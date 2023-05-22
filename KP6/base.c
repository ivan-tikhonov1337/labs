int passenger_read_txt(Passenger *s, FILE *in)
{
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

int passenger_read_bin(Passenger *s, FILE *in)
{
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

void passenger_write_bin(Passenger *s, FILE *out)
{
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

void insert_passenger(Passenger *passengers, int *n) {
    Passenger p;
    printf("Введите данные о новом пассажире:\n");
    printf("Фамилия: ");
    scanf("%s", p.surname);
    printf("Инициалы: ");
    scanf("%s", p.initials);
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
}

void delete_passenger(Passenger *passengers, int *n) {
    printf("Введите фамилию пассажира, которого нужно удалить: ");
    char surname[STR_SIZE];
    scanf("%s", surname);
    int i = 0;
    for (; i < *n; i++) {
        if (strcmp(passengers[i].surname, surname) == 0) {
            break;
        }
    }
    if (i == *n) {
        printf("Пассажир с такой фамилией не найден.\n");
        return;
    }
    for (int j = i; j < *n - 1; j++) {
        passengers[j] = passengers[j + 1];
    }
    (*n)--;
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
    printf("| %-10s | %-10s | %-5s | %-7s | %-15s | %-5s | %-8s | %-5s |\\\\n", "Surname", "Initials", "Items", "Weight", "To", "Time", "Transfer", "Child");
    printf("+------------+------------+-------+---------+-----------------+-------+----------+-------+\\\\n");
    for (int i = 0; i < n; i++) {
        if (passengers[i].num > num_items) {
            print_passenger(passengers[i]);
        }
    }
    printf("+------------+------------+-------+---------+-----------------+-------+----------+-------+\\\\n");
}
