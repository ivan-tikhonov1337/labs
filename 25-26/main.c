#include <stdio.h>
#include <string.h>
#include "deque.h"
#include <limits.h>

#define INF INT_MAX

int procedure(udt *d) {                      // Находит максимальный элемент в деке и удаляет его, перемещая все остальные элементы влево или вправо,
    int t, a;                                // чтобы сохранить порядок элементов. Затем он возвращает максимальный элемент.
    int max = -INF - 1;
    int size = d->size;
    for (int i = 0; i < size; i++) {
        a = udt_top_left(d);        
        if (a > max) {                    // Сравниваем ключи
            max = udt_top_left(d);        // Обновляем максимальный ключ
            t = udt_top_left(d);              // Сохраняем текущий элемент как максимальный
        }
        udt_pop_front(d);                     // Удаляем первый элемент
        udt_push_back(d, a);                  // Добавляем его в конец
    }
    udt *d1 = create_udt(NULL);
    while (udt_top_left(d) != t && udt_top_right(d) != t) {
        a = udt_top_left(d);
        udt_push_front(d1, a);                // Добавляем элемент в начало вспомогательного дека
        udt_pop_front(d);                     // Удаляем первый элемент
        if (!udt_empty(d)) {
            a = udt_top_right(d);
            udt_push_back(d1, a);             // Добавляем элемент в конец вспомогательного дека
            udt_pop_back(d);                  // Удаляем последний элемент
        }
    }
    if (udt_top_left(d) == t) {
        udt_pop_front(d);                     // Удаляем максимальный элемент
    } else {
        udt_pop_back(d);                      // Удаляем максимальный элемент
    }
    while (!udt_empty(d1)){
        udt_push_front(d, udt_top_left(d1));  // Возвращаем элементы из вспомогательного дека в изначальный дек
        udt_pop_front(d1);
    }
    return t;                                 // Возвращаем максимальный элемент
}

udt* sort(udt *d) {                           // Использует procedure, чтобы находить максимальный элемент и добавлять его
    int size = udt_size(d);                   // в новый дек в порядке убывания. Он повторяет эту операцию до тех пор, пока 
    udt *d1 = create_udt(NULL);               // все элементы не будут перемещены в новый дек. На выходе он возвращает новый дек, 
    int t;                                   // содержащий все элементы в порядке убывания.
    for (int i = 0; i < size; i++) {
        t = procedure(d);                     // Получаем максимальный элемент и удаляем его
        udt_push_front(d1, t);                // Добавляем максимальный элемент в начало нового дека
    }
    return d1;                                // Возвращаем отсортированный дек
}

int main() {
    int c = 1, ans;
    udt *d = NULL;
    while (c) {
        printf("\n1. Create deque\n2. Empty\n3. Size\n4. Push back\n5. Push front\n6. Top left\n7. Top right\n8. Pop back\n9. Pop front\n10. Print\n11. Sort\n12. Exit\n");
        printf("Enter an action:\n");
        scanf("%d", &ans);
        switch (ans) {
            case 1: {
                d = create_udt(d);                                                             // Создаем дек
                printf("Deque created\n");
                break;
            }
            case 2: {
                if (d == NULL) {
                    printf("Deque doesn't exist\n");
                } else {
                    udt_empty(d) ? printf("Deque is empty\n") : printf("Deque isn't empty\n");   // Проверяем, пуст ли дек
                }
                break;
            }
            case 3: {
                if (d == NULL) {
                    printf("Deque doesn't exist\n");
                } else {
                    printf("%d\n", udt_size(d));                                              // Выводим размер дека
                }
                break;
            }
            case 4: {
                if (d == NULL) {
                    printf("Deque doesn't exist\n");
                } else {
                    int tb;
                    printf("Enter a value:\n");
                    scanf("%d", &tb);
                    if (!udt_push_back(d, tb)) {                                              // Добавляем элемент в конец дека
                        printf("Deque is full\n");
                    }
                }
                break;
            }
            case 5: {
                if (d == NULL) {
                    printf("Deque doesn't exist\n");
                } else {
                    int tf;
                    printf("Enter a value:\n");
                    scanf("%d", &tf);
                    if (!udt_push_front(d, tf)) {                                             // Добавляем элемент в начало дека
                        printf("Deque is full\n");
                    }
                }
                break;
            }
            case 6: {
                if (d == NULL) {
                    printf("Deque doesn't exist\n");
                } else {
                    if (udt_empty(d)) {
                        printf("Deque is empty\n");
                    } else {
                        int a = udt_top_left(d);                                           // Получаем первый элемент
                        printf("Value: %d\n", a);                 // Выводим ключ и значение элемента
                    }
                }
                break;
            }
            case 7: {
                if (d == NULL) {
                    printf("Deque doesn't exist\n");
                } else {
                    if (udt_empty(d)) {
                        printf("Deque is empty\n");
                    } else {
                        int a = udt_top_right(d);                                          // Получаем последний элемент
                        printf("Value: %d\n", a);                 // Выводим ключ и значение элемента
                    }
                }
                break;
            }
            case 8: {
                if (d == NULL) {
                    printf("Deque doesn't exist\n");
                } else {
                    if (!udt_pop_back(d)) {                                                // Удаляем последний элемент
                        printf("Deque is empty\n");
                    }
                }
                break;
            }
            case 9: {
                if (d == NULL) {
                    printf("Deque doesn't exist\n");
                } else {
                    if (!udt_pop_front(d)) {                                               // Удаляем первый элемент
                        printf("Deque is empty\n");
                    }
                }
                break;
            }
            case 10: {
                if (d == NULL) {
                    printf("Deque doesn't exist\n");
                } else {
                    udt_print(d);                                                         // Выводим все элементы дека
                    printf("\n");
                }
                break;
            }
            case 11: {
                if (d == NULL) {
                    printf("Deque doesn't exist\n");
                } else {
                    d = sort(d);                                                          // Сортируем дек
                }
                break;
            }
            case 12: {
                c = 0;                                                                    // Выходим из цикла
                break;
            }
            default: {
                printf("Wrong answer\n");                                                // Выводим сообщение об ошибке
            }
        }
    }
    return 0;
}
