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
    
    // Поиск связанных компонентов (групп пользователей)
    unordered_set<string> visited;  // Посещенные email/телефоны
    vector<unordered_set<string>> groups;  // Все найденные группы
    unordered_map<string, int> element_to_group;  // Элемент -> номер группы

    // Обходим все email для поиска групп
    for (const auto& email_entry : email_to_phones) {
        const string& email = email_entry.first;
        
        // Если email еще не посещен
        if (visited.find(email) == visited.end()) {
            queue<string> q;  // Очередь для BFS-обхода
            q.push(email);    // Начинаем с текущего email
            unordered_set<string> current_group;  // Текущая группа
            int group_num = groups.size();  // Номер новой группы

            // BFS-обход связанных элементов
            while (!q.empty()) {
                string current = q.front();  // Берем первый элемент из очереди
                q.pop();  // Удаляем его из очереди

                // Если текущий элемент - email
                if (email_to_phones.find(current) != email_to_phones.end()) {
                    if (visited.find(current) == visited.end()) {
                        current_group.insert(current);  // Добавляем в группу
                        element_to_group[current] = group_num;  // Запоминаем группу
                        visited.insert(current);  // Помечаем как посещенный
                        
                        // Добавляем все связанные телефоны в очередь
                        for (const auto& phone : email_to_phones[current]) {
                            q.push(phone);
                        }
                    }

                } else {  // Если текущий элемент - телефон
                    if (visited.find(current) == visited.end()) {
                        current_group.insert(current);
                        element_to_group[current] = group_num;
                        visited.insert(current);
                        
                        // Добавляем все связанные emails в очередь
                        for (const auto& email : phone_to_emails[current]) {
                            q.push(email);
                        }
                    }
                }
            }
            
            groups.push_back(current_group);  // Сохраняем найденную группу
        }
    }

    
