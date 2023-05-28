#include "table.h"

// создание списка
List* Create_List() {
    List* l = (List*)malloc(sizeof(List)); //выделяем память под список
    l->head = NULL;                        //инициализируем указатель на первый элемент списка
    l->size = 0;                           //инициализируем количество элементов списка
    l->sorted = 0;                         //инициализируем состояние списка (неотсортирован)
    return l;                              //возвращаем указатель на созданный список
}

void Read_Table(List* l, FILE* fp) {      //поля ключ и значение в файле должны отделяться знаком табуляции
    char line[100];
    while (fgets(line, 100, fp) != NULL) {
        char* key_str = strtok(line, "\t");
        char* value_str = strtok(NULL, "\n");
        char* key = (char*)malloc(7 * sizeof(char));
        strncpy(key, key_str, 6);
        key[6] = '\0';
        char* value = (char*)malloc((strlen(value_str) + 1) * sizeof(char));
        strcpy(value, value_str);
        Node* new_node = (Node*)malloc(sizeof(Node));
        if (!key || !value || !new_node) {
            printf("Memory allocation error!\n");
            exit(1);
        }        
        
        strcpy(new_node->key, key);
        new_node->data = value;
        new_node->next = NULL;
        
        if (l->head == NULL) {
            new_node->prev = NULL;
            l->head = new_node;
        }
        else {
            Node* current = l->head;
            while (current->next != NULL) {
                current = current->next;
            }
            new_node->prev = current;
            current->next = new_node;
        }

        l->size++;
        free(key);
    }
}

// добавление записи в конец списка
void Add_To_List(List* list, const char* key, const char* data) {
    Node* new_node = (Node*)malloc(sizeof(Node)); //выделяем память под новый элемент списка
    strcpy(new_node->key, key);                   //копируем ключ новой записи в соответствующее поле структуры
    new_node->data = strdup(data);                //копируем данные новой записи в соответствующее поле структуры
    new_node->next = NULL;                        //инициализируем указатель на следующий элемент списка

    if (list->head == NULL) {                     //если список пустой
        new_node->prev = NULL;                    //инициализируем указатель на предыдущий элемент списка
        list->head = new_node;                    //устанавливаем указатель на первый элемент списка
    }
    else {                                        //если список не пустой
        Node* current = list->head;               //устанавливаем указатель на первый элемент списка
        while (current->next != NULL) {           //перебираем элементы списка, пока не найдем последний элемент
            current = current->next;
        }
        new_node->prev = current;                 //устанавливаем указатель на предыдущий элемент списка
        current->next = new_node;                 //устанавливаем указатель на следующий элемент списка
    }

    list->size++;                                 //увеличиваем количество элементов списка на 1
}

// удаление последней записи из списка
void Table_Pop(List* list) {
    if (list->head == NULL) {                     //если список пустой
        return;                                   //выходим из функции
    }

    Node* current = list->head;                   //устанавливаем указатель на первый элемент списка
    while (current->next != NULL) {               //перебираем элементы списка, пока не найдем последний элемент
        current = current->next;
    }

    if (current->prev == NULL) {                  //если удаляемый элемент - единственный в списке
        list->head = NULL;                        //устанавливаем указатель на первый элемент списка в NULL
    } else {                                      //если удаляемый элемент не единственный в списке
        current->prev->next = NULL;               //устанавливаем указатель на следующий элемент предыдущего элемента списка в NULL
    }

    free(current->data);                          //освобождаем память, выделенную под данные удаляемой записи
    free(current);                                //освобождаем память, выделенную под удаляемый элемент списка
    list->size--;                                 //уменьшаем количество элементов списка на 1
}

// получение указателя на первый элемент списка
Node* Begin_List(List* list) {
    if (!list || !list->head) {                   //если список пустой или не существует
        return NULL;                             
    }
    return list->head;                            //возвращаем указатель на первый элемент списка
}

// печать списка
void Table_Print(List* list) {
    printf("\n");                                //выводим пустую строку
    if (list->size == 0) {                       //если список пустой
        printf("List is empty\n");               //выводим сообщение об этом
        return;                                  //выходим из функции
    }
    Node* n = Begin_List(list);                  //устанавливаем указатель на первый элемент списка
    for (int i = 0; i < list->size; i++) {       //перебираем элементы списка
        printf("%s\t%s\n", n->key, n->data);     //выводим ключ и данные очередной записи
        n = n->next;                             //переходим к следующему элементу списка
    }
    printf("\n");                                //выводим пустую строку
}

// удаление списка
void Free_List(List* list) {
    Node* current = list->head;           //устанавливаем указатель на первый элемент списка
    while (current != NULL) {             //перебираем элементы списка, пока не достигнем конца списка
        Node* next = current->next;       //устанавливаем указатель на следующий элемент списка
        free(current->data);              //освобождаем память, выделенную под данные текущей записи
        free(current);                    //освобождаем память, выделенную под текущий элемент списка
        current = next;                   //переходим к следующему элементу списка
    }
    free(list);                           //освобождаем память, выделенную под список
}

// получение размера списка
int List_Size (List* list) {
    return list->size;                    //возвращаем количество элементов списка
}

// получение указателя на элемент списка на определенной позиции
Node* Plus(Node* n, int x) {
    for (int i = 0; i < x; i++) {         //перебираем элементы списка до тех пор, пока не достигнем нужной позиции
        n = n->next;                      //переходим к следующему элементу списка
    }
    return n;                             //возвращаем указатель на элемент списка на нужной позиции
}

// обмен двух элементов списка
void Swap (List* list, int x, int y) {
    Node* n_x = Begin_List(list);         //устанавливаем указатель на первый элемент списка
    n_x = Plus(n_x, x);                   //устанавливаем указатель на элемент списка на позиции x
    Node* n_y = Begin_List(list);         //устанавливаем указатель на первый элемент списка
    n_y = Plus(n_y, y);                   //устанавливаем указатель на элемент списка на позиции y

    char key[7];                          //временная переменная для хранения ключа элемента списка
    char* data;                           //временная переменная для хранения данных элемента списка

    strncpy(key, n_x->key, 6);            //копируем ключ элемента списка на позиции x в временную переменную
    key[6] = '\0';                        //добавляем символ конца строки в конец скопированного ключа
    data = n_x->data;                     //копируем данные элемента списка на позиции x в временную переменную

    strncpy(n_x->key, n_y->key, 6);       //копируем ключ элемента списка на позиции y в поле ключа элемента списка на позиции x
    n_x->key[6] = '\0';                   //добавляем символ конца строки в конец поля ключа элемента списка на позиции x
    n_x->data = n_y->data;                //копируем данные элемента списка на позиции y в поле данных элемента списка на позиции x

    strncpy(n_y->key, key, 6);            //копируем скопированный ключ в поле ключа элемента списка на позиции y
    n_y->key[6] = '\0';                   //добавляем символ конца строки в конец поля ключа элемента списка на позиции y
    n_y->data = data;                     //копируем скопированные данные в поле данных элемента списка на позиции y
}

// Функция для сравнения двух ключей. Возвращает 0, если ключи равны, отрицательное число, если первый ключ меньше второго, и положительное число, если первый ключ больше второго.
int Compare_Keys(char* key1, char* key2) {
    return strncmp(key1, key2, 6);
}

// Функция для поиска узла по заданной позиции в списке. Возвращает узел по данной позиции.
Node* Find(List* list, int position) {
    Node* a = Begin_List(list);
    for (int i = 0; i<position; i++){
        a = a->next;
    }
    return a;
}

// Функция для сортировки элементов в списке методом пузырька.
void Bubble_Sort(List* list) {
    int i, j;
    for (i = 0; i < (list->size - 1); ++i) {
        for (j = 0; j < (list->size - 1 - i); ++j) {
            if (Compare_Keys(Find(list, j)->key, Find(list, j + 1)->key) > 0) {
                Swap(list, j, j + 1);
            }
        }
    }
}

// Функция для бинарного поиска элемента в списке. Возвращает значение элемента, если он найден, и NULL, если элемент не найден.
char* Binary_Search(List* list, char key[7]) {
    if (!list || !list->head) {
        printf("List is empty!");
        return NULL;
    }

    Node* left = list->head;
    Node* right = left;

    while (right->next && strcmp(right->key, key) < 0) { // выполняем поиск элемента, пока не найдём нужный или пока не дойдём до конца списка
        left = right;
        right = right->next;
    }

    if (!strcmp(right->key, key)) {        // если элемент найден, возвращаем его значение
        return right->data;
    }

    return NULL;                           // если элемент не найден, возвращаем NULL
}

// Функция для разворота списка.
void Reverse_List(List* list) {
    Node* current = list->head;
    Node* temp = NULL;

    while (current != NULL) {              // проход по всем элементам списка
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if (temp != NULL) {
        list->head = temp->prev;
    }
}

// Функция для записи списка в файл.
void Write_List(FILE* fp, List* list) {
    Node* current = list->head;
    while (current) {                     // проход по всем элементам списка
        fprintf(fp, "%s\t%s\n", current->key, current->data);
        current = current->next;
    }
}

// Функция для проверки, отсортирован ли список. Возвращает true, если список отсортирован, и false, если список не отсортирован.
bool Is_List_Sorted(List* list, bool asc_order) {
  if (list == NULL || list->size == 0) { // проверка на пустоту списка
    return true;
  }

  Node* current = list->head;
  int compare_result = strcmp(current->key, current->next->key);

  if (asc_order) {                       // проверка на порядок сортировки
    for (; current->next != NULL; current = current->next) {
      compare_result = strcmp(current->key, current->next->key);
      if (compare_result > 0) {
        return false;
      }
    }
  } else {                               // для порядка убывания
    for (; current->next != NULL; current = current->next) {
      compare_result = strcmp(current->key, current->next->key);
      if (compare_result < 0) {          // знак сравнения меняем на обратный
        return false;
      }
    }
  }
  return true;
}

// Функция для печати меню
void print_menu() {                                       
    printf("print - Напечатать таблицу\n");
    printf("add [ключ] [значение] - добавить запись в таблицу\n");
    printf("remove - удалить последнюю запись\n");
    printf("find [ключ] - найти значение по ключу\n");
    printf("sort - отсортировать таблицу\n");
    printf("issort - отсортирован ли список?\n");
    printf("overwriting - перерзаписать файл\n");
    printf("exit - завершение программы\n");
}
