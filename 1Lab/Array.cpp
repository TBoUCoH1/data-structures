#include "Array.h"
#include <iostream>
#include <algorithm>

using namespace std;

void MCREATE(DynamicArray& arr, int initial_capacity) {
    if (initial_capacity <= 0) {
        initial_capacity = 4;
    }
    arr.data = new string[initial_capacity];
    arr.size = 0;
    arr.capacity = initial_capacity;
    cout << "Массив создан с вместимостью " << arr.capacity << endl;
}

void MRESIZE(DynamicArray& arr) {
    int new_capacity = arr.capacity * 2;
    string* new_data = new string[new_capacity];

    for (int i = 0; i < arr.size; ++i) {
        new_data[i] = arr.data[i];
    }
    delete[] arr.data;

    arr.data = new_data;
    arr.capacity = new_capacity;
    cout << "-> Массив расширен до " << arr.capacity << " элементов." << endl;
}

// в конец массива
void MPUSH(DynamicArray& arr, const string& value) {
    if (arr.size >= arr.capacity) {
        MRESIZE(arr);
    }
    arr.data[arr.size] = value;
    arr.size++;
}

// по индексу
void MINSERT(DynamicArray& arr, int index, const string& value) {
    if (index < 0 || index > arr.size) {
        cerr << "Ошибка: неверный индекс для вставки." << endl;
        return;
    }
    if (arr.size >= arr.capacity) {
        MRESIZE(arr);
    }
    // сдвигаем вправо
    for (int i = arr.size; i > index; --i) {
        arr.data[i] = arr.data[i - 1];
    }

    arr.data[index] = value;
    arr.size++;
}

// Получение по индексу
string MGET(const DynamicArray& arr, int index) {
    if (index < 0 || index >= arr.size) {
        cerr << "Ошибка: неверный индекс для получения элемента. Возвращена пустая строка." << endl;
        return "";
    }
    return arr.data[index];
}

// Удаление по индексу
void MDEL(DynamicArray& arr, int index) {
    if (index < 0 || index >= arr.size) {
        cerr << "Ошибка: неверный индекс для удаления." << endl;
        return;
    }

    // Сдвигаем влево
    for (int i = index; i < arr.size - 1; ++i) {
        arr.data[i] = arr.data[i + 1];
    }
    arr.size--;
}

// Замена по индексу
void MSET(DynamicArray& arr, int index, const string& value) { 
    if (index < 0 || index >= arr.size) {
        cerr << "Ошибка: неверный индекс для замены элемента." << endl;
        return;
    }
    arr.data[index] = value;
}

int MGET_SIZE(const DynamicArray& arr) {
    return arr.size;
}

void MPRINT(const DynamicArray& arr) {
    if (arr.size == 0) {
        cout << "Массив пуст." << endl;
        return;
    }
    cout << "Массив (size=" << arr.size << ", capacity=" << arr.capacity << "): ";
    for (int i = 0; i < arr.size; ++i) {
        cout << "\"" << arr.data[i] << "\" ";
    }
    cout << endl;
}

void MCLEAR(DynamicArray& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
    cout << "Память массива освобождена." << endl;
}