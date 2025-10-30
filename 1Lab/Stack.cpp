#include "Stack.h"
#include <iostream>

using namespace std;

void SCREATE(Stack& s) {
    s.top = nullptr;
    s.size = 0;
    cout << "Стек создан." << endl;
}

bool isEmpty(const Stack& s) {
    return s.top == nullptr;
}

void SPUSH(Stack& s, const string& value) {
    SNode* newNode = new SNode(value, s.top);
    s.top = newNode;
    s.size++;
}

string SPOP(Stack& s) {
    if (isEmpty(s)) {
        cerr << "Ошибка: стек пуст! Невозможно выполнить pop." << endl;
        return "";
    }
    SNode* temp = s.top;
    string popped_value = temp -> data;
    
    s.top = s.top -> next;

    delete temp;
    s.size--;
    return popped_value;
}

string SPEEK(const Stack& s) {
    if (isEmpty(s)) {
        cerr << "Ошибка: стек пуст! Невозможно прочитать элемент." << endl;
        return "";
    }
    return s.top -> data;
}

void SPRINT(const Stack& s) {
    if (isEmpty(s)) {
        cout << "Стек пуст." << endl;
        return;
    }

    cout << "Вершина -> ";
    SNode* current = s.top;
    while (current != nullptr) {
        cout << "\"" << current -> data << "\" ";
        current = current -> next;
    }
    cout << "-> Дно" << endl;
}

void SCLEAR(Stack& s) {
    while (!isEmpty(s)) {
        SPOP(s);
    }
    cout << "Стек очищен." << endl;
}