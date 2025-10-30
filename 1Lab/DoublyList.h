#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

#include <string>
#include <cstddef>

using namespace std; 

struct LNode {
    string data;
    LNode* next;
    LNode* prev;
    
    LNode(const string& val, LNode* nxt = nullptr, LNode* prv = nullptr) : data(val), next(nxt), prev(prv) {}
};

struct DoublyList { 
    LNode* head = nullptr; 
    LNode* tail = nullptr; 
    size_t size = 0;
    string filename;
};

void LADD_HEAD(DoublyList& list, const string& value);
void LADD_TAIL(DoublyList& list, const string& value);
void LADD_BEFORE(DoublyList& list, const string& value, const string& target); 
void LADD_AFTER(DoublyList& list, const string& value, const string& target);

void LDEL_HEAD(DoublyList& list);
void LDEL_TAIL(DoublyList& list);
void LDEL_BEFORE(DoublyList& list, const string& target); 
void LDEL_AFTER(DoublyList& list, const string& target);
bool LDEL_BY_VALUE(DoublyList& list, const string& value);

bool LFIND(const DoublyList& list, const string& value);
LNode* LGET(DoublyList& list, const string& value);

void LPRINT(const DoublyList& list); 
void LPRINT_BACKWARD(const DoublyList& list);

void LCREATE(DoublyList& list);
void LCLEAR(DoublyList& list);

#endif