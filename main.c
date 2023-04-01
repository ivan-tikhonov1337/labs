#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print_menu() {                                             // Функция для печати меню
    printf("\nВыберите дейтвие и введите его номер:\n0) Выход\n");
    printf("1) Ввести в дерево элемент.\n");
    printf("2) Распечатать дерево.\n");
    printf("3) Удалить элемент из дерева.\n");
    printf("4) Проверить все ли листья на одном уровне.\n");
    printf("5) Вывести меню.\n");
}


int main(void) {
    Tree *t = NULL;
    int value;
    int action;
    int leafLevel = 0;
    print_menu();
    while (action) {
        value = 0;
        printf("\nДействие:");
        scanf("%d", &action);
        switch (action) {
            case 1:
                printf("Введите значение элемента: ");
                scanf("%d", &value);
                t = add_Node(t, value);
                break;
            case 2:
                printf("\n-------------------------\n");
                tree_print(t, 1); // печатаем дерево
                printf("\n-------------------------\n");
                break;
            case 3:
                printf("\nВведите значение элемента: ");
                scanf("%d", & value);
                t = delete_element(t, value); // удаляем элемент из дерева
                break;
            case 4:
                if (is_Level_Leaf(t, 1, &leafLevel))  //Вывод об уровне деревьев
                    printf("Все листья находятся НА ОДНОМ уровне\n");
                else
                    printf("Все листья находятся НЕ на одном уровне\n");
                break;
            case 5:
                print_menu();
            case 0:
                exit(1);
            default:
                printf("Действия с таким номерам нет\n");
                break;
        }
    }
}
