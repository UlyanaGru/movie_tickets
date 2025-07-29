import java.io.*;
import java.util.*;

public class UserGroups {
    public static void main(String[] args) {
        solve();  // Запуск решения
    }

    public static void solve() {
        // Чтение данных из файла logs.csv
        List<String> lines = new ArrayList<>();  // Список строк из файла
        try (BufferedReader br = new BufferedReader(new FileReader("logs.csv"))) {
            String line;
            while ((line = br.readLine()) != null) {  // Читаем построчно
                if (!line.trim().isEmpty()) {  // Пропускаем пустые строки
                    lines.add(line.trim());  // Добавляем строку в список
                }
            }
        } catch (IOException e) {
            System.err.println("Ошибка чтения файла: " + e.getMessage());
            return;
        }


        // Создаем отображения email -> телефоны и телефон -> emails
        Map<String, Set<String>> emailToPhones = new HashMap<>();
        Map<String, Set<String>> phoneToEmails = new HashMap<>();

        // Обрабатываем каждую строку логов
        for (String line : lines) {
            String[] parts = line.split(",");  // Разделяем по запятой
            String email = parts[0].trim();    // Email - первая часть
            String phone = parts.length > 1 ? parts[1].trim() : "";  // Телефон (если есть)

            // Если и email и телефон не пустые
            if (!email.isEmpty() && !phone.isEmpty()) {
                // Добавляем телефон к email (вычислить если отсутствует)
                emailToPhones.computeIfAbsent(email, k -> new HashSet<>()).add(phone);
                // Добавляем email к телефону
                phoneToEmails.computeIfAbsent(phone, k -> new HashSet<>()).add(email);
            }
        }

        // Поиск связанных компонентов (групп пользователей)
        Set<String> visited = new HashSet<>();  // Посещенные элементы
        List<Set<String>> groups = new ArrayList<>();  // Все группы
        Map<String, Integer> elementToGroup = new HashMap<>();  // Элемент -> номер группы

        // Обходим все email для поиска групп
        for (String email : emailToPhones.keySet()) {
            if (!visited.contains(email)) {  // Если email еще не посещен
                Queue<String> queue = new LinkedList<>();  // Очередь для BFS
                queue.add(email);  // Начинаем с текущего email
                Set<String> currentGroup = new HashSet<>();  // Текущая группа
                int groupNum = groups.size();  // Номер новой группы

                // BFS-обход связанных элементов
                while (!queue.isEmpty()) {
                    String current = queue.poll();  // Берем элемент из очереди

                    