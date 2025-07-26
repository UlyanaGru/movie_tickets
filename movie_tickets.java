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


        