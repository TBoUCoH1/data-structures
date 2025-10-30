#ifndef ARRAY_H
#define ARRAY_H

#include <string>
#include <cstddef>

struct DynamicArray {
    std::string* data;
    int size;
    int capacity;
    std::string filename;
};

void MCREATE(DynamicArray& arr, int initial_capacity = 4);
void MRESIZE(DynamicArray& arr);
void MPUSH(DynamicArray& arr, const std::string& value);
void MINSERT(DynamicArray& arr, int index, const std::string& value);
std::string MGET(const DynamicArray& arr, int index);
void MDEL(DynamicArray& arr, int index);
void MSET(DynamicArray& arr, int index, const std::string& value);
int MGET_SIZE(const DynamicArray& arr);
void MPRINT(const DynamicArray& arr);
void MCLEAR(DynamicArray& arr);

#endif