#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void solve() {
    // Чтение данных из файла logs.csv
    ifstream file("logs.csv");
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла" << endl;
        return;
    }

    // Хранение всех строк файла
    vector<string> lines;
    string line;
    
    // Чтение файла построчно
    while (getline(file, line)) {
        // Пропускаем пустые строки
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    file.close();

    // Создаем отображения:
    // email -> множество телефонов
    unordered_map<string, unordered_set<string>> email_to_phones;
    // phone -> множество email
    unordered_map<string, unordered_set<string>> phone_to_emails;