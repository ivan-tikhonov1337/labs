#include "mytree.h"

typedef struct binaryTree {                      //Создаем структуру узла для дерева
    int data;                                    //Значение узла
    struct Tree *left;                           //Левая ветка
    struct Tree *right;                          //Правая ветка
    struct Tree *parent;                         //Родитель
}Tree;                                           //запишем так, чтобы не писать каждый раз struct ...

Tree *node_create(int value) {                   //Ф-ция типа binaryTree, чобы создать новый узел
    Tree *tree = (Tree *) malloc(sizeof(Tree));  //Создали новый узел
    tree->data = value;                          //Присвоили значение узлу
    tree->left = NULL;                           //Левая ветка пустая
    tree->right = NULL;                          //Правая ветка пустая
    tree->parent = NULL;                         //Родитель пусто
    return tree;
}

Tree *add_Node(Tree *node, int value) {             // Функция для добавления элемента в дерево
    if (node == NULL) {                             //Если дерево пусто, то добавим корневой узел
        printf("Выполнено.\n");
        return node_create(value);               
    }
    Tree *NewTree = (Tree *) malloc(sizeof(Tree));  //выделяем память для нового узла
    NewTree->data = value;
    Tree *tree1 = node;
    Tree *tree2 = NULL;
    while (tree1 != NULL) {                         // Ищем место для вставки нового элемента
        tree2 = tree1;
        if (value < tree1->data) {                  //Запись в бинарное дерево. Если элемент меньше, чем
            tree1 = tree1->left;                    //Значение данного узла, то запишем это значение в левую
        } else if (value > tree1->data) {           //ветку узла, если она пуста. Если не пуста, то просто опустимся 
            tree1 = tree1->right;                   //в эту ветку и повторим операцию.
        } else {                                    //Случай, когда элемент повторился
            printf("Элемент с таким значением уже есть, введите новый.\n");
            return node;
        }
    }
    NewTree->parent = tree2;                        //устанавливаем указатель на родительский узел у нового узла
    NewTree->left = NULL;
    NewTree->right = NULL;
    if (value < tree2->data) {                      //вставляем новый узел в левое поддерево, если значение
        tree2->left = NewTree;                      //меньше значения текущего узла
    } else {                                        //Иначе вставляем в правое поддерево
        tree2->right = NewTree;
    }
        printf("Выполнено\n");
        return node;
}

void tree_print(Tree *root, int n) {                // Функция для печати дерева 
    if (root != NULL) {
        tree_print(root->right, n + 1);             // рекурсивный вызов для правого поддерева
        for (int i = 0; i < n; i++) printf("\t");
        printf("%d\n", root->data);
        tree_print(root->left, n + 1);              // рекурсивный вызов для левого поддерева
    }
}

Tree *search_in_tree(Tree *root, int value) {       //Функция для поиска элемента в дереве
    if (root == NULL) {
        return NULL;
    }
    if (root->data == value) {
        return root;
    }
    if (value > root->data) {
        return search_in_tree(root->right, value);
    } else {
        return search_in_tree(root->left, value);
    }
}

Tree *minimum(Tree *tree) {                         //Функция для нахождения узла с минимальным
    if (tree->left == NULL) {                       //значением в дереве. Нужна для удаления эл-та
        return tree;
    }
    return minimum(tree->left);
}

Tree *delete_element(Tree *tree, int value) {       //Функция для удаления элемента из дерева
    Tree *tree1 = NULL;                             //Указатель на удаляемый узел
    Tree *tree2 = NULL;                             //Указатель для поиска удаляемого элемента
    Tree *tree3 = tree;                             //Указатель на корень дерева
    Tree *tree4 = NULL;                             //Временный указатель
    if (tree == NULL) {                             //Проверяем, не является ли дерево пустым
        printf("Дерево пусто.\n");
        return tree;
    }
    tree1 = search_in_tree(tree3, value);          //Присвоим удаляемый узел     
    if (tree1 == NULL) {
        printf("Элемента с таким значением не существует.\n");
        return tree;
    }
    if (tree1->left == NULL && tree1->right == NULL) {        //Удаляемый элемент не имеет потомков
        if (tree1->parent == NULL) {
            free(tree1);
            tree1 = NULL;
            printf("Успешное удаление.\n");
            return NULL;
        }
        tree2 = tree1->parent;                                //Устанавливаем указатель на родительский узел удаляемого элемента
        if (tree2->left == tree1) {                           //Если удаляемый элемент является левым(правым) потомком
            tree2->left = NULL;                               //родительского элемента, то удаляем связь между ними
        } else {
            tree2->right = NULL;
        }
        free(tree1);                                          //Освобождаем память удаляемого элемента
    } else if (tree1->left != NULL && tree1->right == NULL) { //Удаляемый элемент имеет только одного левого потомка
        if (tree1->parent == NULL) {
            tree4 = tree1->left;
            tree4->parent = NULL;
            free(tree1);
            printf("Успешное удаление.\n");
            return tree4;
        }
        tree2 = tree1->parent;                               //Устанавливаем указатель на родительский узел удаляемого элемента
        if (tree2->left == tree1) {                          //Если удаляемый элемент является левым потомком родительского элемента,
            tree2->left = tree1->left;                       //то заменяем его на левого потомка
        } else {
            tree2->right = tree1->left;                        
        }
        free(tree1);                                         //Освобождаем память удаляемого элемента
    } else if (tree1->left == NULL && tree1->right != NULL) {//Удаляемый элемент имеет только одного правого потомка
        if (tree1->parent == NULL) {
            tree4 = tree1->right;
            tree4->parent = NULL;
            free(tree1);
            printf("Успешное удаление.\n");
            return tree4;
        }
        tree2 = tree1->parent;                               //Устанавливаем указатель на родительский узел удаляемого элемента
        if (tree2->left == tree1) {                          //Если удаляемый элемент является левым потомком родительского 
            tree2->left = tree1->right;                      //элемента, то заменяем его на правого потомка
        } else {
            tree2->right = tree1->right;
        }
        free(tree1);                                         //Освобождаем память удаляемого элемента
    } else if (tree1->left !=NULL && tree1->right != NULL) { //Удаляемый элемент имеет два потомка
        tree2 = minimum(tree1->right);                       //Находим узел с мин значением в правой ветке удаляемого элемента
        tree1->data = tree2->data;                           //Заменяем данные удаляемого элемента на данные найденного элемента
        tree4 = tree2->parent;                               //Устанавливаем указатель на родительский узел найденного элемента
        if (tree4->left == tree2) {                          //Если найденный элемент является левым потомком родительского 
            free(tree2);                                     //элемента, то удаляем связь между ними
            tree4->left = NULL;                              //Удаляем связь между родительским элементом и найденным элементом
        }
        if (tree4->right == tree2) {                         //Если найденный элемент является правым потомком родительского
            free(tree2);                                     //элемента, то удаляем связь между ними
            tree4->right = NULL;                             //Удаляем связь между родительским элементом и найденным элементом
        }
    }
    printf("Успешное удаление.\n");
    return tree;                                             //Возвращаем указатель на корень дерева
}

void print_menu() {                                             // Функция для печати меню
    printf("\nВыберите дейтвие и введите его номер:\n0) Выход\n");
    printf("1) Ввести в дерево элемент.\n");
    printf("2) Распечатать дерево.\n");
    printf("3) Удалить элемент из дерева.\n");
    printf("4) Проверить все ли листья на одном уровне.\n");
    printf("5) Вывести меню.\n");
}

bool is_Level_Leaf(Tree *tree, int level, int *leafLevel) {     //Проверка на уровень листов
    if (tree == NULL)                                           //Если дерево пустое, то всё верно, листья на одном уровне
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
