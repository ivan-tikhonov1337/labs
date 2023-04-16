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

bool is_Level_Leaf(struct node *tree, int level, int *leafLevel) {    //Проверка на уровень листов
    if (tree == NULL)                                                 //Если дерево пустое, то всё верно, листья на одном уровне
        return true;

    if (tree->left == NULL && tree->right == NULL) {            //Если ветки узла пустые, то сделаем следующее:
        if (*leafLevel == 0) {                                  //Если уровень листа(какого-то одного) равен 0,            
            *leafLevel = level;                                 //значит мы опустились вниз в первый раз и изменим это значение 
            return true;                                        //на уровень данного листа (не важно какой именно, если в дальнейшем они все 
        }                                                       //будут на одном уровне)
        else {
            return (level == *leafLevel);                       //Если не равен 0, то сверим с уровнем другого листа. Если не совпадают, то этот
        }                                                       //и какой-то другой лист на разных уровнях
    }
    else {
        return is_Level_Leaf(tree->left, level+1, leafLevel) && //Если же ветки не пустые, то проверим их
        is_Level_Leaf(tree->right, level+1, leafLevel);
    }
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
                if (is_Level_Leaf(t, 1, &leafLevel))  //Вывод об уровне деревьев
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
}
