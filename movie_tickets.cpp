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

    vector<string> lines;  // Хранит все строки из файла
    string line;           // Временная переменная для чтения строк
    while (getline(file, line)) {
        if (!line.empty()) {
            lines.push_back(line);  // Добавляем непустую строку в вектор
        }
    }
    file.close();  // Закрываем файл после чтения

    // Создаем отображения email -> телефоны и телефон -> emails
    unordered_map<string, unordered_set<string>> email_to_phones;
    unordered_map<string, unordered_set<string>> phone_to_emails;


    // Обрабатываем каждую строку из файла
    for (const auto& line : lines) {
        size_t comma_pos = line.find(',');  // Позиция разделителя
        string email = line.substr(0, comma_pos);  // Извлекаем email
        
        // Удаляем пробелы из email
        email.erase(remove_if(email.begin(), email.end(), ::isspace), email.end());
        
        string phone;  // Будет хранить номер телефона
        if (comma_pos != string::npos) {  // Если есть запятая (есть телефон)
            phone = line.substr(comma_pos + 1);  // Извлекаем телефон
            phone.erase(remove_if(phone.begin(), phone.end(), ::isspace), phone.end());
        }

        // Если и email и телефон не пустые, добавляем в отображения
        if (!email.empty() && !phone.empty()) {
            email_to_phones[email].insert(phone);  // Добавляем телефон к email
            phone_to_emails[phone].insert(email);  // Добавляем email к телефону
        }
    }

