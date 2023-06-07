#include "tree.h"

//Функция, определяющая являятся ли символ операцией
bool is_op(char a) {     
    if(a == '*' || a == '^' || a == '/' || a == '+' || a == '-') return true; //если символ является оператором, возвращает true; иначе, false
    else return false;
}

//Функция, определяющая приоритет символа
int define_priority (char a) { 
       switch (a){             //оператор switch, который определяет приоритет в зависимости от символа
               case '-':
                       case '+':
                               return 1;
               case '*':
                       return 2;
               case '/':
                       return 3;
               case '^':
                       return 4;
               default:
                       return 100;
       }
}

//Создает дерево выражения, принимая на вход строку, индекс первого и последнего символов выражения.
unit *make_tree(char expr[], int first, int last) {  
       int prior, min_prior = 100, k, depth = 0;     //инициализация переменных
       unit *tree = malloc(sizeof(unit));            //выделение памяти для структуры unit
       for (int i = first; i <= last; ++i) {         //цикл, который пробегает по всем символам выражения
               if (expr[i] == '(') {                 //если символ - открывающая скобка, увеличивает глубину
                       depth++;
                       continue;
               }
               if (expr[i] == ')') {                 //если символ - закрывающая скобка, уменьшает глубину
                       depth--;
                       continue;
               }
               if (depth>0){                         //если глубина > 0, продолжает цикл
                       continue;
               }
               prior = define_priority(expr[i]);     //определяет приоритет текущего символа
               if (prior <= min_prior) {             //если приоритет <= минимальному приоритету
                       min_prior = prior;            //минимальный приоритет равен приоритету текущего символа
                       k = i;                        //индекс текущего символа
               }
       }
       if (depth !=0) {                             //если глубина не равна 0, выводит сообщение об ошибке и завершает программу
               printf("Wrong expression!\\n");
               exit (1);
       }
       int l;
       if (min_prior == 100) {                                     //если минимальный приоритет равен 100 (т.е. нет операторов)
               if (expr[first] == '(' && expr[last] == ')') {       //если выражение является выражением в скобках
                       free(tree);                                  //освобождает выделенную память
                       return make_tree(expr, first +1, last - 1); //возвращает дерево без скобок
               }
               else {                                         //если выражение не является выражением в скобках
                       l = last - first + 1;                  //длина выражения
                       for (int i = 0; i < l; i++ ) {         //цикл, который пробегает по всем символам выражения
                               tree->data[i] = expr[first+i]; //копирует символы в поле data структуры unit
                       }
                       tree->data[l] = '\n';        //добавляет символ переноса строки
                       tree->left = NULL;           //левый узел - NULL
                       tree->right = NULL;          //правый узел - NULL
                       return tree;                 //возвращает дерево
               }
       }
       tree->data[0] = expr[k];                     //первый символ в поле data структуры unit
       tree->data[1] = '\n';                        //добавляет символ переноса строки
       tree->left = make_tree(expr, first, k-1);    //левый узел - поддерево выражения до оператора
       tree->right = make_tree(expr, k+1, last);    //правый узел - поддерево выражения после оператора
       return tree;                                 //возвращает дерево
}

//Выводит дерево, принимая на вход указатель на структуру unit и уровень.
void print_tree(unit *u, int l) {                     
       if (u->right != NULL) print_tree(u->right, l+1);//если правый узел не является NULL, вызывает функцию print_tree для правого узла
       for(int i = 0; i < l; ++i) {                    //цикл, который выводит пробелы в зависимости от уровня
               printf("   ");
       }
       printf("%5s", u->data);                        //выводит символы из поля data структуры unit
       if (u->left != NULL) print_tree(u->left, l+1); //если левый узел не является NULL, вызывает функцию print_tree для левого узла
}

//Выводит выражение в инфиксном виде, принимая на вход указатель на структуру
void print_expression(unit *u) {                      //определение функции print_expression, принимающей указатель на структуру unit
       if (u==NULL) {                                 //если указатель является NULL, возвращает NULL
               return;
       }
       if (define_priority(u->data[0])!=100 && define_priority(u->left->data[0])!=100 && define_priority(u->data[0])
> define_priority(u->left->data[0])  || u->data[0] == '^' && u->left->data[0] == '^'   ){ //если приоритет оператора > приоритета оператора в левом поддереве
               printf("(");                           //выводит открывающую скобку
               print_expression(u->left);             //вызывает функцию print_expression для левого поддерева
               printf(")");                           //выводит закрывающую скобку
       } else print_expression(u->left);              //иначе, вызывает функцию print_expression для левого поддерева
       for (int i = 0; i < 50; ++i) {                 //цикл, который выводит первые 50 символов из поля data структуры unit
               if (u->data[i] == '\n') {              //если символ равен переносу строки, выходит из цикла
                       break;
               }
               printf("%c", u->data[i]);              //выводит символ
       }
       if (define_priority(u->data[0])!=100 && define_priority(u->right->data[0])!=100 && define_priority(u->data[0]
) > define_priority(u->right->data[0])  || u->data[0] == '^' && u->right->data[0] == '^'   ){ //если приоритет оператора > приоритета оператора в правом поддереве
               printf("(");                           //выводит открывающую скобку
               print_expression(u->right);            //вызывает функцию print_expression для правого поддерева
               printf(")");                           //выводит закрывающую скобку
       } else print_expression(u->right);             //иначе, вызывает функцию print_expression для правого поддерева
}

//Выполняет определенные операции с деревом, такие как перемещение знака минуса, принимая на вход указатель на структуру unit.
unit * spec_func(unit *u) {                          
    if (u == NULL) {                                  //если указатель является NULL, возвращает NULL
            return NULL;
    }

    if(is_op(u->data[0])) {                           //если символ является оператором
        spec_func(u->left);                           //вызывает функцию spec_func для левого поддерева
        spec_func(u->right);                          //вызывает функцию spec_func для правого поддерева
    }
    if(u->data[0] == '*' && !is_op(u->left->data[0]) && u->right->data[0] == '-'){ //если символ является умножением, левый узел не является оператором, а правый узел - знаком минус
        u->data[0] = '-';                             //символ - знак минус
        unit *left = u->left;                         //левый подузел
        unit *right = u->right;                       //правый подузел
        u->left = make_tree("*", 0, 1);               //создает дерево для умножения
        u->left->left = left;                         //левый узел - левый подузел
        u->left->right = right->left;                 //правый узел - левый подузел правого подузла
        u->right = make_tree("*", 0, 1);              //создает дерево для умножения
        u->right->left = left;                        //левый узел - левый подузел
        u->right->right = right->right;               //правый узел - правый подузел правого подузла
    }
    else if(u->data[0] == '*' && !is_op(u->right->data[0]) && u->left->data[0] == '-'){ //если символ является умножением, правый узел не является оператором, а левый узел - знаком минус
        u->data[0] = '-';                             //символ - знак минус
        unit *left = u->left;                         //левый подузел
        unit *right = u->right;                       //правый подузел
        u->left = make_tree("*", 0, 1);               //создает дерево для умножения
        u->left->left = right;                        //левый узел - правый подузел
        u->left->right = left->left;                  //правый узел - левый подузел левого подузла
        u->right = make_tree("*", 0, 1);              //создает дерево для умножения
        u->right->left = right;                       //левый узел - правый подузел
        u->right->right = left->right;                //правый узел - правый подузел левого подузла
    }
    if(is_op(u->data[0])) {                           //если символ является оператором
        spec_func(u->left);                           //вызывает функцию spec_func для левого поддерева
        spec_func(u->right);                          //вызывает функцию spec_func для правого поддерева
    }
    return u;                                         //возвращает указатель на структуру unit
}
