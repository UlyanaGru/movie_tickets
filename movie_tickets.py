# deafaultdict выбран из-за своей функциональности (ссылка в README.md)
from collections import defaultdict
def solve():

    ## Чтение данных из файла

    # Чтение данных из файла logs.csv
    with open('logs.csv', 'r') as f:
        # Читает построчно файл, создает список с элеменатами - прочитанными строками
        lines = [line.strip() for line in f if line.strip()]
    # При обращении к несуществующему ключу, автоматически будет создаваться пустое множество set()
    email_to_phones = defaultdict(set)
    phone_to_emails = defaultdict(set)

    ## Создание множеств для телефонов и почт пользователей

    # Пробег по каждой строчке
    for line in lines:
        # .strip() удаляет пробел и переход на новую строку \n в начале и конце строки, 
        # Далее строка по запятой разбивается на список
        parts = line.split(',')
        # Структура фиксированная, поэтому первая часть - email, вторая - телефон
        email = parts[0].strip()
        # Но надо проверить, что номер не пустой
        phone = parts[1].strip() if len(parts) > 1 else ''
        # Проверка на непустые значения email и phone: None, '', пробел
        if email and phone:
            # К соответсвующему ключу добавляется телефон
            email_to_phones[email].add(phone)
            # Email
            phone_to_emails[phone].add(email)
    # Новое множество для email и телефонов
    visited = set()
    # Для хранения итоговых групп пользвателей
    groups = []
    # Множество для проверки принадлежности к группе
    element_to_group = {}
    # Пробег по email в словаре соответсвия email -> телефон
    for email in email_to_phones:
        # Если email еще не фиксировался в посещениях
        if email not in visited:
            # В очередь присваивается email
            queue = [email]
            # Создание множества для ткущей группы
            current_group = set()
            # Определения номера группы по длине списка на данную итерацию
            group_num = len(groups)
            # Пока очередь непустая
            while queue:
                # Извлекает текущее значение в очереди .pop() - последнее
                current = queue.pop()
                # Если текущее значение в ключах словаря email -> телефон
                if current in email_to_phones:
                    # Если телефон еще не группировался
                    if current not in visited:
                        # Добавляет телефон в текущую группу
                        current_group.add(current)
                        # Ключу телефона присвается номер группы
                        element_to_group[current] = group_num
                        # В множество посетивших сайт добалвяется текущий номер
                        visited.add(current)
                        # Номера телефонов в соответствии с каждым ключом добавляются в очередь
                        for phone in email_to_phones[current]:
                            queue.append(phone)
                else:
                    # Если email еще не группировался
                    if current not in visited:
                        # Добавляет почту в текущую группу
                        current_group.add(current)
                        # Ключу email присвается нмоер группы
                        element_to_group[current] = group_num
                        # В мноежство посетивших добавляется текущий email
                        visited.add(current)
                        # Адреса почт довбляется в сответствии с ключом в очередь
                        for email in phone_to_emails[current]:
                            queue.append(email)
            # В группы добавляется найденная группа
            groups.append(current_group)
    # Количество транзакций групп: для каждой группы 0 изначально
    group_counts = [0] * len(groups)
    # Пробег по линии
    for line in lines:
        # Разделение
        parts = line.split(',')
        # Вычленение email
        elements = [parts[0].strip()]
        # Если длина списка > 1 -> есть еще телефон
        if len(parts) > 1:
            # Добавляет телефон в элементы
            elements.append(parts[1].strip())
        # Для каждого элемента строки
        for element in elements:
            # Если элемент строки в группах
            if element in element_to_group:
                # То считается, что транзакция произошла -> счетчик ↑
                group_counts[element_to_group[element]] += 1
                break

    return print((max(group_counts) if group_counts else 0))

if __name__ == "__main__":
    solve()