#include <stdio.h>
#include <string.h>
#include "deq.h"
#include <limits.h>

#define INF INT_MAX

data procedure(udt *d) {
    data t, a;
    int max = -INF - 1;
    int size = d->size;
    for (int i = 0; i < size; i++) {
        a = udt_top_left(d);        
        if (a.key > max) {                    // Сравниваем ключи
            max = udt_top_left(d).key;        // Обновляем максимальный ключ
            t = udt_top_left(d);              // Сохраняем текущий элемент как максимальный
        }
        udt_pop_front(d);                     // Удаляем первый элемент
        udt_push_back(d, a);                  // Добавляем его в конец
    }
    udt *d1 = create_udt(NULL);
    while (udt_top_left(d).key != t.key && udt_top_right(d).key != t.key) {
        a = udt_top_left(d);
        udt_push_front(d1, a);                // Добавляем элемент в начало вспомогательного дека
        udt_pop_front(d);                     // Удаляем первый элемент
        if (!udt_empty(d)) {
            a = udt_top_right(d);
            udt_push_back(d1, a);             // Добавляем элемент в конец вспомогательного дека
            udt_pop_back(d);                  // Удаляем последний элемент
        }
    }
    if (udt_top_left(d).key == t.key) {
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

udt* sort(udt *d) {
    int size = udt_size(d);
    udt *d1 = create_udt(NULL);
    data t;
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
        printf("1. Create deq\\t 2. Empty\\t 3. Size\\t 4. Push back\\t 5. Push front\\t 6. Top left\\t 7. Top right\\t 8.Pop back\\t 9. Pop front\\t 10.Print\\t 11. Sort\\t 12. Exit\\n");
        scanf("%d", &ans);
        switch (ans) {
            case 1: {
                d = create_udt(d);                                                             // Создаем дек
                break;
            }
            case 2: {
                if (d == NULL) {
                    printf("Deq doesn't exist\\n");
                } else {
                    udt_empty(d) ? printf("Deq is empty\\n") : printf("Deq isn't empty\\n");   // Проверяем, пуст ли дек
                }
                break;
            }
            case 3: {
                if (d == NULL) {
                    printf("Deq doesn't exist\\n");
                } else {
                    printf("%d\\n", udt_size(d));                                              // Выводим размер дека
                }
                break;
            }
            case 4: {
                if (d == NULL) {
                    printf("Deq doesn't exist\\n");
                } else {
                    data tb;
                    printf("Print key\\n");
                    scanf("%d", &tb.key);
                    printf("Print string\\n");
                    scanf("%s", tb.value);
                    if (!udt_push_back(d, tb)) {                                              // Добавляем элемент в конец дека
                        printf("Deq is full\\n");
                    }
                }
                break;
            }
            case 5: {
                if (d == NULL) {
                    printf("Deq doesn't exist\\n");
                } else {
                    data tf;
                    printf("Print key\\n");
                    scanf("%d", &tf.key);
                    printf("Print string\\n");
                    scanf("%s", tf.value);
                    if (!udt_push_front(d, tf)) {                                             // Добавляем элемент в начало дека
                        printf("Deq is full\\n");
                    }
                }
                break;
            }
            case 6: {
                if (d == NULL) {
                    printf("Deq doesn't exist\\n");
                } else {
                    if (udt_empty(d)) {
                        printf("Deq is empty\\n");
                    } else {
                        data a = udt_top_left(d);                                           // Получаем первый элемент
                        printf("Key\\n%d\\nValue\\n%s\\n", a.key, a.value);                 // Выводим ключ и значение элемента
                    }
                }
                break;
            }
            case 7: {
                if (d == NULL) {
                    printf("Deq doesn't exist\\n");
                } else {
                    if (udt_empty(d)) {
                        printf("Deq is empty\\n");
                    } else {
                        data a = udt_top_right(d);                                          // Получаем последний элемент
                        printf("Key\\n%d\\nValue\\n%s\\n", a.key, a.value);                 // Выводим ключ и значение элемента
                    }
                }
                break;
            }
            case 8: {
                if (d == NULL) {
                    printf("Deq doesn't exist\\n");
                } else {
                    if (!udt_pop_back(d)) {                                                // Удаляем последний элемент
                        printf("Deq is empty\\n");
                    }
                }
                break;
            }
            case 9: {
                if (d == NULL) {
                    printf("Deq doesn't exist\\n");
                } else {
                    if (!udt_pop_front(d)) {                                               // Удаляем первый элемент
                        printf("Deq is empty\\n");
                    }
                }
                break;
            }
            case 10: {
                if (d == NULL) {
                    printf("Deq doesn't exist\\n");
                } else {
                    udt_print(d);                                                         // Выводим все элементы дека
                }
                break;
            }
            case 11: {
                if (d == NULL) {
                    printf("Deq doesn't exist\\n");
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
                printf("Wrong answer\\n");                                                // Выводим сообщение об ошибке
            }
        }
    }
    return 0;
}
