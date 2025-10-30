#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

#include <string>
#include <cstddef>

struct FNode {
    std::string key;
    FNode* next;
};

struct SinglyLinkedList { 
    FNode* head = nullptr;
    size_t size = 0;
    std::string filename;
};

void FPRINT(const SinglyLinkedList& list);
void FPRINT_REC(FNode* nd);

void FPUSH_HEAD(SinglyLinkedList& list, const std::string& key);
void FPUSH(SinglyLinkedList& list, const std::string& key);
void FPUSH_AFTER(FNode* nd, const std::string& key);
void FPUSH_BEFORE(SinglyLinkedList& list, const std::string& target, const std::string& key);

void FDEL_HEAD(SinglyLinkedList& list);
void FDEL_TAIL(SinglyLinkedList& list);
void FDEL_AFTER(FNode* nd);
void FDEL_BEFORE(SinglyLinkedList& list, const std::string& target);
void FDEL(SinglyLinkedList& list, const std::string& value);

FNode* FGET(const SinglyLinkedList& list, const std::string& value);

#endif