#ifndef STACK_H
#define STACK_H

#include <string>
#include <cstddef>

using namespace std;

struct SNode {
    string data;
    SNode* next;
    
    SNode(const string& val, SNode* nxt = nullptr) : data(val), next(nxt) {}
};

struct Stack { 
    SNode* top = nullptr; 
    size_t size = 0; 
    string filename; 
};

void SCREATE(Stack& s);
bool isEmpty(const Stack& s);
void SPUSH(Stack& stack, const string& value);
string SPOP(Stack& stack);
string SPEEK(const Stack& stack);
void SPRINT(const Stack& stack);
void SCLEAR(Stack& stack);

#endif