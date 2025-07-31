## Билеты в кино

Покупая билет в кино, пользователь сервиса может указать свой email или телефон, либо email и телефон сразу. Напишите алгоритм, который по списку таких транзакций находит пользователя, купившего больше всех билетов. В качестве ответа укажите число строк в исходном файле, которые относятся к этому пользователю. Под пользователем понимается email, телефон или комбинация обоих идентификаторов, если их удастся связать по логам покупок.

Пример связывания пользователей по логам:

user_1@contest.yandex.ru, 880111111111\
user_1@contest.yandex.ru, 880222222222\
user_2@contest.yandex.ru, 880222222222\
user_3@contest.yandex.ru, 880333333333

В этом примере адреса user_1@contest.yandex.ru, user_2@contest.yandex.ru и телефоны 880111111111, 880222222222 относятся к одному пользователю. А user_3@contest.yandex.ru и 880333333333 — к другому.

### Формат ввода

Логи покупок доступны в файле [logs.csv](https://disk.yandex.ru/d/ULHABqNIyu9fmg)\
В первом столбце указан адрес электронной почты пользователя, во втором — телефон.

### Формат вывода

Целое число строк.

### Ограничения

Ограничение времени 1 с\
Ограничение памяти 64 МБ

- [x] [Решение на Python](https://github.com/UlyanaGru/movie_tickets/blob/main/movie_tickets.py)
- [x] [Решение на C++](https://github.com/UlyanaGru/movie_tickets/blob/main/movie_tickets.cpp)
- [x] [Решение на Java](https://github.com/UlyanaGru/movie_tickets/blob/main/movie_tickets.java)

_Не забудьте при проверке скачать файлик_ ↑

#### Немного полезных ссылок

[Defaultdict в документации](https://docs.python.org/3/library/collections.html#collections.defaultdict)

#### Переменные в решении

lines - список строк из файла logs.csv

email_to_phones / emailToPhones - отображение email → множество телефонов

phone_to_emails / phoneToEmails - отображение телефон → множество emails

visited - множество посещенных элементов (email/телефон)

groups - список всех найденных групп пользователей

element_to_group / elementToGroup - отображение элемента (email/телефон) на номер его группы

group_counts / groupCounts - счетчики транзакций для каждой группы

file.is_open() / try - проверка успешного открытия файла

email.erase() / trim() - очистка строк от лишних пробелов

email_to_phones[email].insert() / computeIfAbsent() - добавление связи email-телефон

visited.find() == visited.end() / contains() - проверка посещения элемента

queue.push() / add() - добавление элемента в очередь для BFS-обхода

groups.push_back() / add() - добавление найденной группы в список

group_counts[group_num]++ - инкремент счетчика транзакций группы

max_element() / Arrays.stream().max() - поиск максимального значения