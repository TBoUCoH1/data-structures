#include "Queue.h"
#include <iostream>

using namespace std;

void QCREATE(Queue& q) {
    q.head = nullptr;
    q.tail = nullptr;
    q.size = 0;
    cout << "Очередь создана." << endl;
}

bool isEmpty(const Queue& q) {
    return q.head == nullptr;
}

void QPUSH(Queue& q, const string& value) {
    QNode* newNode = new QNode{value, nullptr};
    if (isEmpty(q)) {
        q.head = newNode;
        q.tail = newNode;
    } else {
        q.tail -> next = newNode;
        q.tail = newNode;
    }
    q.size++;
}

string QPOP(Queue& q) {
    if (isEmpty(q)) {
        cerr << "Ошибка: очередь пуста! Невозможно выполнить pop." << endl;
        return "";
    }
    QNode* temp = q.head;
    string popped_value = temp -> data;
    q.head = q.head -> next;

    if (q.head == nullptr) {
        q.tail = nullptr;
    }
    delete temp;
    q.size--;
    return popped_value;
}

string QPEEK(const Queue& q) {
    if (isEmpty(q)) {
        cerr << "Ошибка: очередь пуста! Невозможно прочитать элемент." << endl;
        return "";
    }
    return q.head->data;
}

void QPRINT(const Queue& q) {
    if (isEmpty(q)) {
        cout << "Очередь пуста." << endl;
        return;
    }

    cout << "Начало -> ";
    QNode* current = q.head;
    while (current != nullptr) {
        cout << "\"" << current->data << "\" ";
        current = current->next;
    }
    cout << "-> Конец" << endl;
}

void QCLEAR(Queue& q) {
    while (!isEmpty(q)) {
        QPOP(q);
    }
    cout << "Очередь очищена." << endl;
}