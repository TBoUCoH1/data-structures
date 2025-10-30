#include "Commands.h"
#include <iostream>
#include <string>
#include <locale>

using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");

    Commands cmd;
    string query;
    string filename;

    cout << "Введите базовое имя файла для работы (например, 'mydatabase'): ";
    cin >> filename;

    cout << "Введите команды (для выхода введите 'exit' или 'quit'):" << endl;
    cin.ignore();

    while (true) {
        cout << "> ";
        getline(cin, query);
        
        if (query == "exit" || query == "quit") {
            break;
        }
        
        if (!query.empty()) {
            cmd.execute(query, filename);
        }
    }

    cout << "Программа завершена." << endl;
    return 0;
}