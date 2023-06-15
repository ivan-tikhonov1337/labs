#include "tree.h"

int main(void) {
       unit *t = NULL;
       int opt = -1;
       while (opt!=5) {
            printf("Выберите код действия:\n1. Введите выражение и создайте дерево.\n2. Преобразуйте выражение.\n3. Выведите дерево.\n4. Выведите выражение.\n5. Выход\n");
            scanf("%d", &opt);   
            switch (opt) {
                       case 1: {
                               printf("Введите выражение: ");
                               char expression[1000];
                               scanf("%s", expression);
                               int n = 0;
                               while (expression[n] != '\0') {
                                        n++;
                               }
                               t = make_tree(expression, 0, n-1);
                               break;
                       }
                       case 2: {
                               t = spec_func(t);
                               break;
                       }
                       case 3: {
                               printf("\n");
                               print_tree(t, 0);
                               break;
                       }
                       case 4: {
                               printf("\n");
                               print_expression(t);
                               printf("\n");
                               break;
                       }
               }
       }
       return 0;
}
