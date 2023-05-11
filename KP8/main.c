#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "two-sided_list.h"

// Главная функция
int main() {
    Node* head = NULL;
    Complex val;
    int choice, k;

    printf("\nВведите номер операции:\n");
    while(1) {
        printf("1. Вывести список\n");
        printf("2. Вставить в начало\n");
        printf("3. Вставить в конец\n");
        printf("4. Удалить элемент\n");
        printf("5. Подсчитать длину списка\n");
        printf("6. Дополнить список копиями\n");
        printf("7. Выход\n");

        scanf("%d", &choice);                     // ввод выбора пользователя
        switch(choice) {                          // выбор действия в зависимости от ввода пользователя
            case 1:                               // вывод списка
                printf("Текущий список:\n");
                PrintList(head);
                break;
            case 2:                               // добавление элемента в начало
                printf("Введите комплексное число (действительную и мнимую части через пробел): ");
                scanf("%f %f", &val.real, &val.imaginary);
                head = InsertAtBeginning(head, val);
                break;
            case 3:                               // добавление элемента в конец
                printf("Введите комплексное число (действительную и мнимую части через пробел): ");
                scanf("%f %f", &val.real, &val.imaginary);
                head = InsertAtEnd(head, val);
                break;
            case 4:                               // удаление элемента
                printf("Введите комплексное число (действительную и мнимую части через пробел) для удаления: ");
                scanf("%f %f", &val.real, &val.imaginary);
                head = DeleteNode(head, val);
                break;
            case 5:                               // длина списка
                printf("Длина списка: %d\n", Length(head));
                break;
            case 6:                               // дополнение копиями
                printf("Введите желаемую длину списка:\n");
                scanf("%d", &k);
                printf("Введите комплексное число (действительную и мнимую части через пробел) для вставки: ");
                scanf("%f %f", &val.real, &val.imaginary);
                head = AddToLength(head, val, k); // дополнение списка копиями переданного значения
                break;
            case 7:
                exit(0);                          // завершение программы
            default:
                printf("Некорректный ввод. Попробуйте еще раз\n");
        }
    }
    return 0;
}
