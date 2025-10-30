#include "Commands.h"
#include "Array.h"
#include "Queue.h"
#include "SinglyList.h"
#include "DoublyList.h"
#include "AVLTree.h"
#include "Stack.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// функции для файлов

// массив
void loadArrayFromFile(const string& filename, DynamicArray& arr) {
    ifstream file(filename + "_array");
    string value;
    while (file >> value) { MPUSH(arr, value); }
}
void saveArrayToFile(const string& filename, const DynamicArray& arr) {
    ofstream file(filename + "_array");
    for (int i = 0; i < arr.size; ++i) {
        file << arr.data[i] << (i == arr.size - 1 ? "" : " ");
    }
}

// очередь
void loadQueueFromFile(const string& filename, Queue& q) {
    ifstream file(filename + "_queue");
    string value;
    while (file >> value) { QPUSH(q, value); }
}
void saveQueueToFile(const string& filename, const Queue& q) {
    ofstream file(filename + "_queue");
    QNode* current = q.head;
    bool first = true;
    while (current) {
        if (!first) file << " ";
        file << current->data;
        first = false;
        current = current->next;
    }
}

// стек
void loadStackFromFile(const string& filename, Stack& s) {
    ifstream file(filename + "_stack");
    string value;
    vector<string> values;
    while (file >> value) { values.push_back(value); }
    for(const auto& val : values) { SPUSH(s, val); }
}
void saveStackToFile(const string& filename, const Stack& s) {
    ofstream file(filename + "_stack");
    SNode* current = s.top;
    vector<string> temp_items;
    while(current) { temp_items.push_back(current->data); current = current->next; }
    reverse(temp_items.begin(), temp_items.end());
    for(size_t i = 0; i < temp_items.size(); ++i) {
        file << temp_items[i] << (i == temp_items.size() - 1 ? "" : " ");
    }
}

// односвязный список
void FCLEAR(SinglyLinkedList& list) {
    while(list.head != nullptr) { FDEL_HEAD(list); }
}
void loadSinglyListFromFile(const string& filename, SinglyLinkedList& list) {
    ifstream file(filename + "_slist");
    string value;
    while (file >> value) { FPUSH(list, value); }
}
void saveSinglyListToFile(const string& filename, const SinglyLinkedList& list) {
    ofstream file(filename + "_slist");
    FNode* current = list.head;
    bool first = true;
    while(current) {
        if (!first) file << " ";
        file << current->key;
        first = false;
        current = current->next;
    }
}

// двусвязный список
void loadDoublyListFromFile(const string& filename, DoublyList& list) {
    ifstream file(filename + "_dlist");
    string value;
    while (file >> value) { LADD_TAIL(list, value); }
}
void saveDoublyListToFile(const string& filename, const DoublyList& list) {
    ofstream file(filename + "_dlist");
    LNode* current = list.head;
    bool first = true;
    while(current) {
        if (!first) file << " ";
        file << current->data;
        first = false;
        current = current->next;
    }
}

// дерево
void saveTreeRecursive(ofstream& file, AVLNode* node) {
    if (!node) return;
    queue<AVLNode*> q; q.push(node);
    bool first = true;
    while(!q.empty()){
        AVLNode* current = q.front(); q.pop();
        if(!first) file << " ";
        file << current->key;
        first = false;
        if(current->left) q.push(current->left);
        if(current->right) q.push(current->right);
    }
}
void loadTreeFromFile(const string& filename, AVLTree& tree) {
    ifstream file(filename + "_tree");
    string value;
    while (file >> value) { tree.root = TINSERT(tree.root, value); }
}
void saveTreeToFile(const string& filename, const AVLTree& tree) {
    ofstream file(filename + "_tree");
    saveTreeRecursive(file, tree.root);
}

void Commands::execute(const string& query, const string& filename) {
    istringstream iss(query);
    string command, arg1, arg2;
    iss >> command;

    // массив
    if (command == "MPUSH") {
        if (iss >> arg1) {
            DynamicArray arr; MCREATE(arr); loadArrayFromFile(filename, arr);
            MPUSH(arr, arg1);
            saveArrayToFile(filename, arr); MCLEAR(arr);
            cout << "-> добавлен " << arg1 << endl;
        } else { cout << "Ошибка: команда MPUSH требует <значение>." << endl; }
    }
    else if (command == "MINSERT") {
        if (iss >> arg1 >> arg2) {
            try {
                int index = stoi(arg1);
                DynamicArray arr; MCREATE(arr); loadArrayFromFile(filename, arr);
                MINSERT(arr, index, arg2);
                saveArrayToFile(filename, arr); MCLEAR(arr);
                cout << "-> вставлен " << arg2 << " по индексу " << index << endl;
            } catch (const exception&) { cout << "Ошибка: неверный формат индекса." << endl; }
        } else { cout << "Ошибка: команда MINSERT требует <индекс> <значение>." << endl; }
    }
    else if (command == "MGET") {
        if (iss >> arg1) {
            try {
                int index = stoi(arg1);
                DynamicArray arr; MCREATE(arr); loadArrayFromFile(filename, arr);
                cout << "-> " << MGET(arr, index) << endl;
                MCLEAR(arr);
            } catch (const exception&) { cout << "Ошибка: неверный формат индекса." << endl; }
        } else { cout << "Ошибка: команда MGET требует <индекс>." << endl; }
    }
     else if (command == "MDEL") {
        if (iss >> arg1) {
            try {
                int index = stoi(arg1);
                DynamicArray arr; MCREATE(arr); loadArrayFromFile(filename, arr);
                MDEL(arr, index);
                saveArrayToFile(filename, arr); MCLEAR(arr);
                cout << "-> удален элемент по индексу " << index << endl;
            } catch (const exception&) { cout << "Ошибка: неверный формат индекса." << endl; }
        } else { cout << "Ошибка: команда MDEL требует <индекс>." << endl; }
    }
    else if (command == "MSET") {
        if (iss >> arg1 >> arg2) {
            try {
                int index = stoi(arg1);
                DynamicArray arr; MCREATE(arr); loadArrayFromFile(filename, arr);
                MSET(arr, index, arg2);
                saveArrayToFile(filename, arr); MCLEAR(arr);
                cout << "-> установлен " << arg2 << " по индексу " << index << endl;
            } catch (const exception&) { cout << "Ошибка: неверный формат индекса." << endl; }
        } else { cout << "Ошибка: команда MSET требует <индекс> <значение>." << endl; }
    }
    else if (command == "MGET_SIZE") {
        DynamicArray arr; MCREATE(arr); loadArrayFromFile(filename, arr);
        cout << "-> Размер массива: " << MGET_SIZE(arr) << endl;
        MCLEAR(arr);
    }
    else if (command == "MCLEAR") {
        DynamicArray arr; MCREATE(arr);
        saveArrayToFile(filename, arr); MCLEAR(arr);
        cout << "-> массив очищен." << endl;
    }
    else if (command == "MPRINT") {
        DynamicArray arr; MCREATE(arr); loadArrayFromFile(filename, arr);
        cout << "-> "; MPRINT(arr);
        MCLEAR(arr);
    }
    
    // стек
    else if (command == "SPUSH") {
        if (iss >> arg1) {
            Stack stack; SCREATE(stack); loadStackFromFile(filename, stack);
            SPUSH(stack, arg1);
            saveStackToFile(filename, stack); SCLEAR(stack);
            cout << "-> добавлен " << arg1 << endl;
        } else { cout << "Ошибка: команда SPUSH требует <значение>." << endl; }
    }
    else if (command == "SPOP") {
        Stack stack; SCREATE(stack); loadStackFromFile(filename, stack);
        if (!isEmpty(stack)) {
            string val = SPOP(stack);
            saveStackToFile(filename, stack); cout << "-> извлечен " << val << endl;
        } else { cout << "Ошибка: стек пуст" << endl; }
        SCLEAR(stack);
    }
    else if (command == "SPEEK") {
        Stack stack; SCREATE(stack); loadStackFromFile(filename, stack);
        if (!isEmpty(stack)) { cout << "-> " << SPEEK(stack) << endl; }
        else { cout << "Ошибка: стек пуст" << endl; }
        SCLEAR(stack);
    }
    else if (command == "SCLEAR") {
        Stack stack; SCREATE(stack);
        saveStackToFile(filename, stack); SCLEAR(stack);
        cout << "-> стек очищен." << endl;
    }
    else if (command == "SPRINT") {
        Stack stack; SCREATE(stack); loadStackFromFile(filename, stack);
        cout << "-> "; SPRINT(stack);
        SCLEAR(stack);
    }
    
    // очередь
    else if (command == "QPUSH") {
        if (iss >> arg1) {
            Queue q; QCREATE(q); loadQueueFromFile(filename, q);
            QPUSH(q, arg1);
            saveQueueToFile(filename, q); QCLEAR(q);
            cout << "-> добавлен " << arg1 << endl;
        } else { cout << "Ошибка: команда QPUSH требует <значение>." << endl; }
    }
    else if (command == "QPOP") {
        Queue q; QCREATE(q); loadQueueFromFile(filename, q);
        if (!isEmpty(q)) {
            string val = QPOP(q);
            saveQueueToFile(filename, q); cout << "-> извлечен " << val << endl;
        } else { cout << "Ошибка: очередь пуста" << endl; }
        QCLEAR(q);
    }
    else if (command == "QPEEK") {
        Queue q; QCREATE(q); loadQueueFromFile(filename, q);
        if (!isEmpty(q)) { cout << "-> " << QPEEK(q) << endl; }
        else { cout << "Ошибка: очередь пуста" << endl; }
        QCLEAR(q);
    }
    else if (command == "QCLEAR") {
        Queue q; QCREATE(q);
        saveQueueToFile(filename, q); QCLEAR(q);
        cout << "-> очередь очищена." << endl;
    }
    else if (command == "QPRINT") {
        Queue q; QCREATE(q); loadQueueFromFile(filename, q);
        cout << "-> "; QPRINT(q);
        QCLEAR(q);
    }

    // односвязный список
    else if (command == "FPUSH_HEAD") {
        if (iss >> arg1) {
            SinglyLinkedList list; loadSinglyListFromFile(filename, list);
            FPUSH_HEAD(list, arg1);
            saveSinglyListToFile(filename, list); FCLEAR(list);
            cout << "-> добавлен " << arg1 << " в начало" << endl;
        } else { cout << "Ошибка: команда FPUSH_HEAD требует <значение>." << endl; }
    }
    else if (command == "FPUSH" || command == "FPUSH_TAIL") {
        if (iss >> arg1) {
            SinglyLinkedList list; loadSinglyListFromFile(filename, list);
            FPUSH(list, arg1);
            saveSinglyListToFile(filename, list); FCLEAR(list);
            cout << "-> добавлен " << arg1 << " в конец" << endl;
        } else { cout << "Ошибка: команда " << command << " требует <значение>." << endl; }
    }
    else if (command == "FPUSH_BEFORE") {
        if (iss >> arg1 >> arg2) {
            SinglyLinkedList list; loadSinglyListFromFile(filename, list);
            FPUSH_BEFORE(list, arg2, arg1);
            saveSinglyListToFile(filename, list); FCLEAR(list);
            cout << "-> вставлен " << arg1 << " перед " << arg2 << endl;
        } else { cout << "Ошибка: команда FPUSH_BEFORE требует <новое_значение> <целевое_значение>." << endl; }
    }
    else if (command == "FPUSH_AFTER") {
        if (iss >> arg1 >> arg2) {
            SinglyLinkedList list; loadSinglyListFromFile(filename, list);
            FNode* target = FGET(list, arg2);
            if (target) {
                FPUSH_AFTER(target, arg1);
                saveSinglyListToFile(filename, list);
                cout << "-> вставлен " << arg1 << " после " << arg2 << endl;
            } else { cout << "-> целевой элемент " << arg2 << " не найден" << endl; }
            FCLEAR(list);
        } else { cout << "Ошибка: команда FPUSH_AFTER требует <новое_значение> <целевое_значение>." << endl; }
    }
    else if (command == "FDEL") {
        if (iss >> arg1) {
            SinglyLinkedList list; loadSinglyListFromFile(filename, list);
            FDEL(list, arg1);
            saveSinglyListToFile(filename, list); FCLEAR(list);
            cout << "-> произведена попытка удаления " << arg1 << endl;
        } else { cout << "Ошибка: команда FDEL требует <значение>." << endl; }
    }
    else if (command == "FGET") {
        if (iss >> arg1) {
            SinglyLinkedList list; loadSinglyListFromFile(filename, list);
            cout << "-> " << (FGET(list, arg1) ? "найден" : "не найден") << endl;
            FCLEAR(list);
        } else { cout << "Ошибка: команда FGET требует <значение>." << endl; }
    }
    else if (command == "FCLEAR") {
        SinglyLinkedList list;
        saveSinglyListToFile(filename, list);
        cout << "-> односвязный список очищен." << endl;
    }
    else if (command == "FPRINT") {
        SinglyLinkedList list; loadSinglyListFromFile(filename, list);
        cout << "-> "; FPRINT(list);
        FCLEAR(list);
    }

    // двусвязный список
    else if (command == "LADD_HEAD") {
        if (iss >> arg1) {
            DoublyList list; LCREATE(list); loadDoublyListFromFile(filename, list);
            LADD_HEAD(list, arg1);
            saveDoublyListToFile(filename, list); LCLEAR(list);
            cout << "-> добавлен " << arg1 << " в начало" << endl;
        } else { cout << "Ошибка: команда LADD_HEAD требует <значение>." << endl; }
    }
    else if (command == "LADD_TAIL" || command == "LPUSH") {
        if (iss >> arg1) {
            DoublyList list; LCREATE(list); loadDoublyListFromFile(filename, list);
            LADD_TAIL(list, arg1);
            saveDoublyListToFile(filename, list); LCLEAR(list);
            cout << "-> добавлен " << arg1 << " в конец" << endl;
        } else { cout << "Ошибка: команда " << command << " требует <значение>." << endl; }
    }
    else if (command == "LADD_BEFORE") {
         if (iss >> arg1 >> arg2) {
            DoublyList list; LCREATE(list); loadDoublyListFromFile(filename, list);
            LADD_BEFORE(list, arg1, arg2); // Ваша функция ищет сама
            saveDoublyListToFile(filename, list);
            cout << "-> вставлен " << arg1 << " перед " << arg2 << endl;
            LCLEAR(list);
        } else { cout << "Ошибка: команда LADD_BEFORE требует <новое_значение> <целевое_значение>." << endl; }
    }
    else if (command == "LADD_AFTER") {
        if (iss >> arg1 >> arg2) {
            DoublyList list; LCREATE(list); loadDoublyListFromFile(filename, list);
            LADD_AFTER(list, arg1, arg2);
            saveDoublyListToFile(filename, list);
            cout << "-> вставлен " << arg1 << " после " << arg2 << endl;
            LCLEAR(list);
        } else { cout << "Ошибка: команда LADD_AFTER требует <новое_значение> <целевое_значение>." << endl; }
    }
    else if (command == "LDEL") {
        if (iss >> arg1) {
            DoublyList list; LCREATE(list); loadDoublyListFromFile(filename, list);
            if (LDEL_BY_VALUE(list, arg1)) {
                saveDoublyListToFile(filename, list);
                cout << "-> удален " << arg1 << endl;
            } else { cout << "-> элемент " << arg1 << " не найден" << endl; }
            LCLEAR(list);
        } else { cout << "Ошибка: команда LDEL требует <значение>." << endl; }
    }
    else if (command == "LGET") {
        if (iss >> arg1) {
            DoublyList list; LCREATE(list); loadDoublyListFromFile(filename, list);
            cout << "-> " << (LGET(list, arg1) ? "найден" : "не найден") << endl;
            LCLEAR(list);
        } else { cout << "Ошибка: команда LGET требует <значение>." << endl; }
    }
    else if (command == "LCLEAR") {
        DoublyList list; LCREATE(list);
        saveDoublyListToFile(filename, list); LCLEAR(list);
        cout << "-> двусвязный список очищен." << endl;
    }
    else if (command == "LPRINT") {
        DoublyList list; LCREATE(list); loadDoublyListFromFile(filename, list);
        cout << "-> "; LPRINT(list);
        LCLEAR(list);
    }
    else if (command == "LPRINT_BACKWARD") {
        DoublyList list; LCREATE(list); loadDoublyListFromFile(filename, list);
        cout << "-> "; LPRINT_BACKWARD(list);
        LCLEAR(list);
    }

    // дерево
    else if (command == "TINSERT") {
        if (iss >> arg1) {
            AVLTree tree; loadTreeFromFile(filename, tree);
            tree.root = TINSERT(tree.root, arg1);
            saveTreeToFile(filename, tree);
            cout << "-> вставлен " << arg1 << endl;
        } else { cout << "Ошибка: команда TINSERT требует <значение>." << endl; }
    }
    else if (command == "TDEL") {
        if (iss >> arg1) {
            AVLTree tree; loadTreeFromFile(filename, tree);
            tree.root = TDEL(tree.root, arg1);
            saveTreeToFile(filename, tree);
            cout << "-> удален " << arg1 << endl;
        } else { cout << "Ошибка: команда TDEL требует <значение>." << endl; }
    }
    else if (command == "TGET" || command == "ISMEMBER") {
        if (iss >> arg1) {
            AVLTree tree; loadTreeFromFile(filename, tree);
            cout << "-> " << (TGET(tree.root, arg1) ? "TRUE" : "FALSE") << endl;
        } else { cout << "Ошибка: команда " << command << " требует <значение>." << endl; }
    }
    else if (command == "TPRINT") {
        AVLTree tree; loadTreeFromFile(filename, tree);
        TPRINT(tree.root);
    }

    else {
        cerr << "Неизвестная команда: " << command << endl;
    }
}