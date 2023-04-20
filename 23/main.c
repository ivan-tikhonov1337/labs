#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int max_depth = -1;

void dfs(struct node *root, int depth) {
    if (root == NULL)                                     //Если NULL, то завершим выполнение функции
        return;
    if (root->left == NULL && root->right == NULL) {     //Если лист, то узнаем глубину
        if (max_depth == -1)                             //Проверка на первый лист
            max_depth = depth;
        else if (depth != max_depth) {                   //Проверка на тот же уровень остальных листов
            max_depth = -2;
            return;                                      //Если нашелся такой лист, то заверишм ф-цию
        }
    }
    dfs(root->left, depth + 1);
    dfs(root->right, depth + 1);
}

bool check_leaf_level(struct node *root) {
    dfs(root, 0);                                        //Узнаем уровень
    return max_depth >= -1;                              
}

int main(void) {
    struct node *t = NULL;                                        //указатель на корень дерева, инициализируем как NULL
    int value;                                                    //переменная, в которую мы записываем значение считанной вершины
    int action;                                                   //переменная, которая считывает с клавиатуры команды меню
    print_menu();
    int leafLevel = 0;
    while (action) {                                              //чтение символа из потока ввода
        value = 0;  
        printf("\nДействие: ");
        scanf("%d", &action);
        switch (action) {
            case 1:
                printf("Введите значение элемента: ");
                scanf("%d", &value);
                t = add_node(t, value);
                break;
            case 2:
                print_tree(t, 1);
                break;
            case 3:
                printf("\nВведите значение элемента: ");
                scanf("%d", &value);
                t = delete_node(t, value);
                break;
            case 4:
                if (check_leaf_level(t))                      //Вывод об уровне деревьев
                    printf("Все листья находятся НА ОДНОМ уровне\n");
                else
                    printf("Все листья находятся НЕ на одном уровне\n");
                break;
            case 0:
                exit(1);
            default:
                printf("Действия с таким номерам нет\n");
                break;
        }
        print_menu();
    }
    free_tree(t);                                         //освобождение памяти дерева
}

