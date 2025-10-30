#include "SinglyList.h"
#include <iostream>

using namespace std;

void FPRINT(const SinglyLinkedList& list) {
    FNode* nd = list.head; 
    while (nd != nullptr) {
        cout << "\"" << nd -> key << "\" ";
        nd = nd->next;
    }
    cout << endl;
}

void FPRINT_REC(FNode* nd) { 
    if (nd == nullptr) {
        cout << endl;
        return;
    }
    cout << "\"" << nd -> key << "\" ";
    FPRINT_REC(nd -> next);
}

void FPUSH_HEAD(SinglyLinkedList& list, const string& key) {
    FNode* newNode = new FNode{key, list.head}; 
    list.head = newNode;
    list.size++;
}

void FPUSH(SinglyLinkedList& list, const string& key) {
    FNode* newNode = new FNode{key, nullptr}; 
    if (!list.head) {
        list.head = newNode;
        list.size++;
        return;
    }
    FNode* temp = list.head; 
    while (temp -> next != nullptr)
        temp = temp -> next;
    temp -> next = newNode;
    list.size++;
}

void FPUSH_AFTER(FNode* nd, const string& key) {
    if (!nd) return;
    FNode* newNode = new FNode{key, nd -> next}; 
    nd -> next = newNode;
}

void FPUSH_BEFORE(SinglyLinkedList& list, const string& target, const string& key) {
    if (!list.head) return;
    if (list.head -> key == target) {
        FPUSH_HEAD(list, key);
        return;
    }
    FNode* prev = list.head; 
    FNode* curr = list.head -> next; 
    while (curr && curr -> key != target) {
        prev = curr;
        curr = curr -> next;
    }
    if (!curr) return;
    FNode* newNode = new FNode{key, curr}; 
    prev -> next = newNode;
    list.size++;
}

void FDEL_HEAD(SinglyLinkedList& list) {
    if (!list.head) return;
    FNode* temp = list.head; 
    list.head = list.head -> next;
    delete temp;
    list.size--;
}

void FDEL_TAIL(SinglyLinkedList& list) {
    if (!list.head) return;
    if (!list.head -> next) {
        delete list.head;
        list.head = nullptr;
        list.size--;
        return;
    }
    FNode* temp = list.head; 
    while (temp -> next -> next)
        temp = temp -> next;
    delete temp->next;
    temp -> next = nullptr;
    list.size--;
}

void FDEL_AFTER(FNode* nd) {
    if (!nd || !nd -> next) return;
    FNode* del = nd -> next; 
    nd -> next = del -> next;
    delete del;
}

void FDEL_BEFORE(SinglyLinkedList& list, const string& target) {
    if (!list.head || list.head -> key == target) return;
    FNode* prevPrev = nullptr; 
    FNode* prev = list.head; 
    FNode* curr = list.head->next; 
    while (curr && curr -> key != target) {
        prevPrev = prev;
        prev = curr;
        curr = curr -> next;
    }
    if (!curr) return; 
    if (!prevPrev) { 
        FDEL_HEAD(list);
    } else {
        prevPrev -> next = curr;
        delete prev;
        list.size--;
    }
}

void FDEL(SinglyLinkedList& list, const string& value) {
    if (!list.head) return;
    if (list.head -> key == value) {
        FDEL_HEAD(list);
        return;
    }
    FNode* prev = list.head; 
    FNode* curr = list.head->next; 
    while (curr && curr -> key != value) {
        prev = curr;
        curr = curr -> next;
    }
    if (!curr) return;
    prev -> next = curr->next;
    delete curr;
    list.size--;
}

FNode* FGET(const SinglyLinkedList& list, const string& value) {
    FNode* temp = list.head;
    while (temp) {
        if (temp -> key == value)
            return temp;
        temp = temp -> next;
    }
    return nullptr;
}