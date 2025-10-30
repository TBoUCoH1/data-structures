#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include <cstddef>

struct QNode {
    std::string data;
    QNode* next;
};

struct Queue {
    QNode* head = nullptr;
    QNode* tail = nullptr;
    size_t size = 0;
    std::string filename;
};

void QCREATE(Queue& q);
bool isEmpty(const Queue& q);
void QPUSH(Queue& q, const std::string& value);
std::string QPOP(Queue& q);
std::string QPEEK(const Queue& q);
void QPRINT(const Queue& q);
void QCLEAR(Queue& q);

#endif