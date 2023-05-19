#include "two-sided_list.h"

// Функция для вставки нового узла в конец списка
Node* InsertAtIndex(Node* head, Complex val, int index) {
    if (index != 0 && Length(head) == 0) {
        printf("Введено неправильное значение индекса(ожидалось 0)\n");
        return head;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));   // создание нового узла
    newNode->data = val;                           // присваивание переданного значения в узел
    newNode->next = NULL;
    newNode->prev = NULL;
    if(index == 0) {                              // если нужно вставить элемент в начало списка
        newNode->next = head;                      // устанавливаем указатель на следующий элемент нового узла на первый элемент старого списка
        if(head != NULL) {                         // если старый список был не пуст
            head->prev = newNode;                   // устанавливаем указатель на предыдущий элемент первого элемента старого списка на новый узел
        }
        head = newNode;                             // новый узел становится первым элементом списка
    }
    else {                                         // если нужно вставить элемент в середину или конец списка
        Node* temp = head;
        for(int i = 0; i < index - 1; i++) {        // переход к узлу, предшествующему индексу вставки
            if(temp->next == NULL) {                 // если достигнут конец списка
                printf("Индекс вне диапазона списка\n");
                return head;                       // возвращает указатель на первый узел списка
            }
            temp = temp->next;
        }
        newNode->next = temp->next;                 // устанавливаем указатель на следующий элемент нового узла на элемент, следующий за узлом, предшествующим индексу вставки
        newNode->prev = temp;                       // устанавливаем указатель на предыдущий элемент нового узла на узел, предшествующий индексу вставки
        if(temp->next != NULL) {                     // если не вставляем в конец списка
            temp->next->prev = newNode;               // устанавливаем указатель на предыдущий элемент следующего элемента за узлом, предшествующим индексу вставки, на новый узел
        }
        temp->next = newNode;                        // устанавливаем указатель на следующий элемент узла, предшествующего индексу вставки, на новый узел
    }
    return head;                                     // возвращает указатель на первый узел списка
}

// Функция для удаления узла из списка
Node* DeleteAtIndex(Node* head, int index) {
    Node* temp = head;                              // временный указатель на первый узел списка
    if(index == 0) {                               // если нужно удалить первый элемент списка
        head = head->next;                           // первый узел списка становится следующим узлом
        if(head != NULL) {                           // если список не пуст
            head->prev = NULL;                        // устанавливаем указатель на предыдущий элемент нового первого элемента списка на NULL
        }
        free(temp);                                   // удаляем первый узел списка
        return head;                                  // возвращает указатель на новый первый узел списка
    }
    else {
        for(int i = 0; i < index - 1; i++) {        // переход к узлу, предшествующему индексу удаления
            if(temp->next == NULL) {                 // если достигнут конец списка
                printf("Индекс вне диапазона списка\\\\n");
                return head;                       // возвращает указатель на первый узел списка
            }
            temp = temp->next;
        }
        Node* nodeToDelete = temp->next;            // временный указатель на узел, который нужно удалить
        temp->next = nodeToDelete->next;            // переназначаем указатель на следующий элемент в узле, предшествующему удаляемому узлу
        if(nodeToDelete->next != NULL) {             // если удаляемый узел не последний в списке
            nodeToDelete->next->prev = temp;           // переназначаем указатель на предыдущий элемент в следующем узле
        }
        free(nodeToDelete);                          // удаляем узел
        return head;                                  // возвращает указатель на первый узел списка
    }
}


// Функция для подсчета длины списка
int Length(Node* head) {
    int count = 0;                                                               // счетчик узлов
    while(head != NULL) {                                                        // цикл, пока не будет достигнут конец списка
        count++;                                                                 // увеличение счетчика
        head = head->next;                                                       // переход к следующему узлу
    }
    return count;                                                                // возвращает количество узлов в списке
}

// Функция для дополнения списка до указанной длины копиями переданного значения
Node* AddToLength(Node* head, Complex val, int k) {    
    int len = Length(head);                                                      // длина списка
    if(len >= k) {                                                               // если длина списка больше или равна заданной длине
        printf("Длина списка больше введённого значения\n");
        return head;                                                             // возвращает указатель на первый узел списка
    }
    int count = k - len;                                                         // количество узлов, которые нужно добавить
    while(count > 0) {                                                           // цикл, пока не будет добавлено нужное количество узлов
        head = InsertAtEnd(head, val);                                           // добавление нового узла в конец списка
        count--;                                                                 // уменьшение счетчика
    }
    return head;                                                                 // возвращает указатель на первый узел списка
}

void DeleteList(Node* head) {
    Node* temp = NULL;
    while(head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

Node* InsertAtIndex(Node* head, Complex val, int index) {
    Node* newNode = (Node*)malloc(sizeof(Node));   // создание нового узла
    newNode->data = val;                           // присваивание переданного значения в узел
    newNode->next = NULL;
    newNode->prev = NULL;
    if(index == 0) {                              // если нужно вставить элемент в начало списка
        newNode->next = head;                      // устанавливаем указатель на следующий элемент нового узла на первый элемент старого списка
        if(head != NULL) {                         // если старый список был не пуст
            head->prev = newNode;                   // устанавливаем указатель на предыдущий элемент первого элемента старого списка на новый узел
        }
        head = newNode;                             // новый узел становится первым элементом списка
    }
    else {                                         // если нужно вставить элемент в середину или конец списка
        Node* temp = head;
        for(int i = 0; i < index - 1; i++) {        // переход к узлу, предшествующему индексу вставки
            if(temp->next == NULL) {                 // если достигнут конец списка
                printf("Индекс вне диапазона списка\n");
                return head;                       // возвращает указатель на первый узел списка
            }
            temp = temp->next;
        }
        newNode->next = temp->next;                 // устанавливаем указатель на следующий элемент нового узла на элемент, следующий за узлом, предшествующим индексу вставки
        newNode->prev = temp;                       // устанавливаем указатель на предыдущий элемент нового узла на узел, предшествующий индексу вставки
        if(temp->next != NULL) {                     // если не вставляем в конец списка
            temp->next->prev = newNode;               // устанавливаем указатель на предыдущий элемент следующего элемента за узлом, предшествующим индексу вставки, на новый узел
        }
        temp->next = newNode;                        // устанавливаем указатель на следующий элемент узла, предшествующего индексу вставки, на новый узел
    }
    return head;                                     // возвращает указатель на первый узел списка
}
