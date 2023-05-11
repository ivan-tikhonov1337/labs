#include <stdio.h>
#include <stdlib.h>
#include "two-sided_list.h"

// Главная функция
int main() {
    struct node* head = NULL;                  // указатель на первый узел списка = NULL (список пуст)
    float val;                                 // значение, которое будет передаваться функциям
    int choice, k;                             // выбор пользователя и заданная длина списка
    while(1) {                                 // бесконечный цикл
        printf("\n1. Вывести список\n");
        printf("2. Вставить в начало\n");
        printf("3. Вставить в конец\n");
        printf("4. Удалить элемент\n");
        printf("5. Подсчитать длину списка\n");
        printf("6. Дополнить список копиями\n");
        printf("7. Выход\n");
        printf("Введите номер операции:");
        scanf("%d", &choice);                 // ввод выбора пользователя

        switch(choice) {                      // выбор действия в зависимости от ввода пользователя
            case 1:                           // вывод списка
                printf("Текущий список:\n");
                PrintList(head);
                break;
            case 2:                           // добавление элемента в начало
                printf("Введите значение: ");
                scanf("%f", &val);
                head = InsertAtBeginning(head, val);
                break;
            case 3:                           // добавление элемента в конец
                printf("Введите значение: "); 
                scanf("%f", &val);
                head = InsertAtEnd(head, val);
                break;
            case 4:                           // удаление элемента
                printf("Введите значение для удаления: ");
                scanf("%f", &val);
                head = DeleteNode(head, val);
                break;
            case 5:                           // длина списка
                printf("Длина списка: %d\n", Length(head));
                break;
            case 6:                          // дополнение копиями
                printf("Введите желаемую длину списка ");
                scanf("%d", &k);
                printf("Введите значение для вставки: ");
                scanf("%f", &val);
                head = AddToLength(head, val, k); // дополнение списка копиями переданного значения
                break;
            case 7:
                exit(0);                          // завершение программы
            default:
                printf("\nНекорректный ввод. Попробуйте еще раз\n");
        }
    }
    return 0;
}
