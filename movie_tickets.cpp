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

    // Словари для хранения соответствий email->телефоны и телефон->emails
    // Используем unordered_map для быстрого доступа
    unordered_map<string, unordered_set<string>> email_to_phones;
    unordered_map<string, unordered_set<string>> phone_to_emails;
    
    // Парсим строки и заполняем словари
    for (const auto& ln : lines) {
        size_t pos = ln.find(',');
        string email = ln.substr(0, pos);
        // Удаляем пробелы в начале и конце
        email.erase(0, email.find_first_not_of(" \t"));
        email.erase(email.find_last_not_of(" \t") + 1);
        
        string phone = (pos != string::npos) ? ln.substr(pos + 1) : "";
        phone.erase(0, phone.find_first_not_of(" \t"));
        phone.erase(phone.find_last_not_of(" \t") + 1);
        
        if (!email.empty() && !phone.empty()) {
            email_to_phones[email].insert(phone);
            phone_to_emails[phone].insert(email);
        }
    }