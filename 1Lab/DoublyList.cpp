#include "DoublyList.h"
#include <iostream>

using namespace std;

void LCREATE(DoublyList& list) {
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

void LADD_HEAD(DoublyList& list, const string& value) {
    LNode* newNode = new LNode{value, list.head, nullptr};
    if (list.head) { 
        list.head->prev = newNode;
    } else { 
        list.tail = newNode;
    }
    list.head = newNode;
    list.size++;
}

void LADD_TAIL(DoublyList& list, const string& value) {
    LNode* newNode = new LNode{value, nullptr, list.tail};
    if (list.tail) {
        list.tail->next = newNode;
    } else {
        list.head = newNode;
    }
    list.tail = newNode;
    list.size++;
}

void LADD_AFTER(DoublyList& list, const string& value, const string& target) {
    LNode* targetNode = LGET(list, target);
    if (!targetNode) {
        cerr << "Ошибка: целевой узел \"" << target << "\" для вставки после не найден." << endl;
        return;
    }

    LNode* newNode = new LNode{value, targetNode->next, targetNode};
    
    if (targetNode -> next) {
        targetNode -> next -> prev = newNode;
    } else { // если targetNode был хвостом
        list.tail = newNode;
    }
    targetNode -> next = newNode;
    list.size++;
}

void LADD_BEFORE(DoublyList& list, const string& value, const string& target) {
    LNode* targetNode = LGET(list, target);
    if (!targetNode) {
        cerr << "Ошибка: целевой узел \"" << target << "\" для вставки до не найден." << endl;
        return;
    }

    if (targetNode == list.head) { // Вставка в начало
        LADD_HEAD(list, value);
        return;
    }
 
    LNode* newNode = new LNode{value, targetNode, targetNode->prev};

    targetNode -> prev -> next = newNode;
    targetNode -> prev = newNode;
    list.size++;
}

void LDEL_HEAD(DoublyList& list) {
    if (!list.head) return;

    LNode* temp = list.head;
    list.head = list.head -> next;

    if (list.head) {
        list.head -> prev = nullptr;
    } else { 
        list.tail = nullptr;
    }
    delete temp;
    list.size--;
}

void LDEL_TAIL(DoublyList& list) {
    if (!list.tail) return;

    LNode* temp = list.tail;
    list.tail = list.tail -> prev;

    if (list.tail) {
        list.tail -> next = nullptr;
    } else {
        list.head = nullptr;
    }
    delete temp;
    list.size--;
}

void LDEL_AFTER(DoublyList& list, const string& target) {
    LNode* targetNode = LGET(list, target);
    if (!targetNode || !targetNode->next) return;
    
    LNode* nodeToDelete = targetNode -> next;
    targetNode->next = nodeToDelete -> next;

    if (nodeToDelete -> next) { 
        nodeToDelete -> next -> prev = targetNode;
    } else { // Удаляемый узел был хвостом
        list.tail = targetNode;
    }
    delete nodeToDelete;
    list.size--;
}

void LDEL_BEFORE(DoublyList& list, const string& target) {
    LNode* targetNode = LGET(list, target);
    if (!targetNode || !targetNode->prev) return;
    
    LNode* nodeToDelete = targetNode->prev;
    targetNode -> prev = nodeToDelete->prev;

    if (nodeToDelete -> prev) {
        nodeToDelete -> prev -> next = targetNode;
    } else { // Удаляемый узел был головой
        list.head = targetNode;
    }
    delete nodeToDelete;
    list.size--;
}

LNode* LGET(DoublyList& list, const string& value) { 
    LNode* temp = list.head;
    while (temp) {
        if (temp -> data == value) { // Изменено key на data для LNode
            return temp;
        }
        temp = temp -> next;
    }
    return nullptr; 
}

bool LDEL_BY_VALUE(DoublyList& list, const string& value) { // LDEL
    LNode* targetNode = LGET(list, value);
    if (!targetNode) {
        cout << "Узел со значением \"" << value << "\" не найден." << endl;
        return false;
    }

    if (targetNode == list.head) {
        LDEL_HEAD(list);
    } else if (targetNode == list.tail) {
        LDEL_TAIL(list);
    } else {
        targetNode -> prev -> next = targetNode -> next;
        targetNode -> next -> prev = targetNode -> prev;
        delete targetNode;
        list.size--;
    }
    return true;
}

void LPRINT(const DoublyList& list) {
    cout << "Список (прямой обход): ";
    if (!list.head) {
        cout << "пуст." << endl;
        return;
    }
    LNode* temp = list.head;
    while (temp) {
        cout << "\"" << temp->data << "\" ";
        temp = temp->next;
    }
    cout << endl;
}

void LPRINT_BACKWARD(const DoublyList& list) {
    cout << "Список (обратный обход): ";
    if (!list.tail) {
        cout << "пуст." << endl;
        return;
    }
    LNode* temp = list.tail;
    while (temp) {
        cout << "\"" << temp->data << "\" ";
        temp = temp->prev;
    }
    cout << endl;
}

void LCLEAR(DoublyList& list) {
    while (list.head) {
        LDEL_HEAD(list);
    }
    cout << "Список очищен." << endl;
}