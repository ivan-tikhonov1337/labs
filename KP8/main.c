#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "two-sided_list.h"

// Главная функция
int main() {
    Node* head = NULL;
    Complex val;
    int choice, k, index;
    printf("*Вставка по индексу начинается с 0\n");
    printf("Введите номер операции:\n");
    bool running = true;
    while(running) {
        printf("1. Вывести список\n");
        printf("2. Вставить элемент по индексу\n");
        printf("3. Удалить элемент по индексу\n");
        printf("4. Подсчитать длину списка\n");
        printf("5. Дополнить список копиями\n");
        printf("6. Выход\n");
        scanf("%d", &choice);                     // ввод выбора пользователя
        switch(choice) {                          // выбор действия в зависимости от ввода пользователя
            case 1:                               // вывод списка
                printf("Текущий список:\n");
                PrintList(head);
                break;
            case 2:                               // добавление элемента в начало
                printf("Введите индекс на место которого хотите вставить элемент: ");
                scanf("%d", &index);
                printf("Введите комплексное число (действительную и мнимую части через пробел): ");
                scanf("%f %f", &val.real, &val.imaginary);
                head = InsertAtIndex(head, val, index);
                break;
            case 3:                               // добавление элемента в конец
                printf("Введите индекс элемента, который хотите удалить: ");
                scanf("%d", &index);
                if (head == NULL)
                    printf("Cписок пуст\n");
                else
                    head = DeleteAtIndex(head, index);
                break;
            case 4:                               // длина списка
                printf("Длина списка: %d\n", Length(head));
                break;
            case 5:                               // дополнение копиями
                printf("Введите желаемую длину списка:\n");
                scanf("%d", &k);
                printf("Введите комплексное число (действительную и мнимую части через пробел) для вставки: ");
                scanf("%f %f", &val.real, &val.imaginary);
                head = AddToLength(head, val, k); // дополнение списка копиями переданного значения
                break;
            case 6:
                running = false;                  // завершение программы
                break;
            default:
                printf("Некорректный ввод. Попробуйте еще раз\n"); 
        }
    }
    DeleteList(head);
    return 0;
}
