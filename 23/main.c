#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void get_level(struct node* node, int level, int* leaf_level) { // Функция для получения уровня листьев
    if (node == NULL) {
        return;
    }
    if (node->left == NULL && node->right == NULL) {
        if (*leaf_level == 0) {                                 // Сохраняем уровень первого листа
            *leaf_level = level;
        } else if (*leaf_level != level) {                      // Если нашли лист на другом уровне, то дерево не удовлетворяет условию
            return;
        }
    }
    get_level(node->left, level + 1, leaf_level);               // Рекурсивный вызов для левого и правого поддерева
    get_level(node->right, level + 1, leaf_level);
}

bool check_level(struct node* node, int level, int leaf_level) {// Функция для проверки того, что все листья находятся на одном уровне
    if (node == NULL) {
        return true;
    }
    if (node->left == NULL && node->right == NULL) {
        if (level != leaf_level) {                              // Если нашли лист на другом уровне, то дерево не удовлетворяет условию
            return false;
        }
    }        
    return check_level(node->left, level + 1, leaf_level) &&    // Рекурсивный вызов для левого и правого поддерева
    check_level(node->right, level + 1, leaf_level);
}

bool leaf_level_check(struct node* root) {                      // Функция для проверки, находятся ли все листья на одном уровне. 
    int leaf_level = 0;                                         // Получаем уровень первого листа
    get_level(root, 1, &leaf_level);                            // Проверяем, что все листья находятся на одном уровне
    return check_level(root, 1, leaf_level);                    
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

