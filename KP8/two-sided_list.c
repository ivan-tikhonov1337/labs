// Функция для создания нового узла списка
struct node* CreateNode(float val) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node)); // выделение памяти для нового узла
    newNode->data = val;                        // присвоение значению нового узла переданного значения
    newNode->next = NULL;                       // указатель на следующий узел нового узла = NULL
    newNode->prev = NULL;                       // указатель на предыдущий узел нового узла = NULL
    return newNode;                             // возвращает указатель на созданный узел
}

// Функция для вывода списка на экран
void PrintList(struct node* head) {
    while(head != NULL) {
        printf("%f    ", head->data);            // вывод значения текущего узла на экран
        head = head->next;                     // переход к следующему узлу
    }
    printf("\n");                              // переход на новую строку
}

// Функция для вставки нового узла в начало списка
struct node* InsertAtBeginning(struct node* head, float val) {
    struct node* newNode = CreateNode(val);    // создание нового узла
    if(head == NULL) {                         // если список пуст
        head = newNode;                        // то созданный узел становится первым
    }
    else {                                     // если список не пуст
        head->prev = newNode;                  // указатель на предыдущий узел текущего первого узла = новый узел
        newNode->next = head;                  // указатель на следующий узел нового узла = текущий первый узел
        head = newNode;                        // новый узел становится первым
    }
    return head;                               // возвращает указатель на первый узел списка
}

// Функция для вставки нового узла в конец списка
struct node* InsertAtEnd(struct node* head, float val) {
    struct node* newNode = CreateNode(val);    // создание нового узла
    if(head == NULL) {                         // если список пуст
        head = newNode;                        // то созданный узел становится первым
    }
    else { // если список не пуст
        struct node* temp = head;              // временный указатель на первый узел списка
        while(temp->next != NULL) {            // цикл, пока не будет найден последний узел списка
            temp = temp->next;                 // переход к следующему узлу
        }
        temp->next = newNode;                  // указатель на следующий узел последнего узла списка = новый узел
        newNode->prev = temp;                  // указатель на предыдущий узел нового узла = последний узел списка
    }
    return head;                               // возвращает указатель на первый узел списка
}

// Функция для удаления узла из списка
struct node* DeleteNode(struct node* head, float val) {
    struct node* temp = head;                  // временный указатель на первый узел списка
    if(head->data == val) {                    // если значение первого узла списка соответствует переданному значению
        head = head->next;                     // первый узел списка становится следующим узлом
        free(temp);                            // удаляется первый узел списка
        return head;                           // возвращает указатель на новый первый узел списка
    }
    while(temp->next != NULL && temp->next->data != val) { // цикл, пока не будет найден узел со значением, равным переданному
        temp = temp->next;                     // переход к следующему узлу
    }
    if(temp->next == NULL)
        printf("Значение не найдено\n");
        return head;                           // элемент не найден
    struct node* delNode = temp->next;         // временный указатель на удаляемый узел
    temp->next = delNode->next;                // указатель на следующий узел предыдущего узла = следующий узел удаляемого узла
    if(delNode->next != NULL)
        delNode->next->prev = temp;            // указатель на предыдущий узел следующего узла удаляемого узла = предыдущему узлу удаляемого узла
    free(delNode);                             // удаляется узел
    return head;                               // возвращает указатель на первый узел списка
}

// Функция для подсчета длины списка
int Length(struct node* head) {
    int count = 0;                             // счетчик узлов
    while(head != NULL) {                      // цикл, пока не будет достигнут конец списка
        count++;                               // увеличение счетчика
        head = head->next;                     // переход к следующему узлу
    }
    return count;                              // возвращает количество узлов в списке
}

struct node* AddToLength(struct node* head, float val, int k) {
    int len = Length(head);                    // длина списка
    if(len >= k) {                             // если длина списка больше или равна заданной длине
        printf("Длина списка меньше введённого значения\n");
        return head;                           // возвращает указатель на первый узел списка
    }
    int count = k - len;                       // количество узлов, которые нужно добавить
    while(count > 0) {                         // цикл, пока не будет добавлено нужное количество узлов
        head = InsertAtEnd(head, val);         // добавление нового узла в конец списка
        count--;                               // уменьшение счетчика
    }
    return head;                               // возвращает указатель на первый узел списка
}
