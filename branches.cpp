#include <iostream>  // для ввода-вывода в консоль
#include <fstream>   // для работы с файлами
#include <string>    // для работы со строками
#include <vector>    // для хранения списка студентов
#include <algorithm> // для сортировки

using namespace std;

// Структура для хранения данных о студенте
// Структура - это как шаблон, в котором хранятся связанные данные
struct Student {
    string fam;     // фамилия
    string name;    // имя
    string otch;    // отчество
    string dt_r;    // дата рождения
    string gr;      // группа
    string n_z;     // номер зачетки
    int kurs;       // курс
};

// Функция для разделения строки на части по символу '#'
vector<string> splitString(const string& str, char delimiter) {
    vector<string> parts;  // вектор для хранения частей строки
    string part = "";      // временная переменная для накопления части строки
    
    for (char ch : str) {  // проходим по каждому символу строки
        if (ch == delimiter) {  // если встретили разделитель
            parts.push_back(part);  // сохраняем накопленную часть
            part = "";               // очищаем для следующей части
        } else {
            part += ch;  // добавляем символ к текущей части
        }
    }
    parts.push_back(part);  // добавляем последнюю часть
    return parts;
}

// Функция для чтения всех студентов из файла
vector<Student> readAllStudents() {
    vector<Student> students;  // создаем вектор для хранения студентов
    ifstream file("db_stud.dat");  // открываем файл для чтения
    
    if (!file.is_open()) {  // если файл не открылся
        cout << "Файл не найден или не может быть открыт." << endl;
        cout << "Создайте новый файл при добавлении первого студента." << endl;
        return students;  // возвращаем пустой список
    }
    
    string line;
    getline(file, line);  // пропускаем заголовок (первую строку)
    
    // читаем файл построчно
    while (getline(file, line)) {
        vector<string> parts = splitString(line, '#');  // разделяем строку
        
        // Проверяем, что в строке достаточно данных
        if (parts.size() >= 7) {
            Student student;  // создаем нового студента
            
            // заполняем поля структуры
            student.fam = parts[0];
            student.name = parts[1];
            student.otch = parts[2];
            student.dt_r = parts[3];
            student.gr = parts[4];
            student.n_z = parts[5];
            student.kurs = stoi(parts[6]);  // stoi преобразует строку в число
            
            students.push_back(student);  // добавляем студента в вектор
        }
    }
    
    file.close();  // закрываем файл
    return students;
}

// Функция для сохранения всех студентов в файл
void saveAllStudents(const vector<Student>& students) {
    ofstream file("db_stud.dat");  // открываем файл для записи
    
    // записываем заголовок
    file << "fam#name#otch#dt_r#gr#n_z#kurs" << endl;
    
    // записываем каждого студента
    for (const auto& student : students) {
        file << student.fam << "#"
             << student.name << "#"
             << student.otch << "#"
             << student.dt_r << "#"
             << student.gr << "#"
             << student.n_z << "#"
             << student.kurs << endl;
    }
    
    file.close();  // закрываем файл
}

// Функция для добавления нового студента
void addStudent() {
    Student student;  // создаем нового студента
    
    cout << "\n=== Добавление нового студента ===" << endl;
    
    // запрашиваем данные у пользователя
    cout << "Фамилия: ";
    cin >> student.fam;
    
    cout << "Имя: ";
    cin >> student.name;
    
    cout << "Отчество: ";
    cin >> student.otch;
    
    cout << "Дата рождения (гггг-мм-дд): ";
    cin >> student.dt_r;
    
    cout << "Группа: ";
    cin >> student.gr;
    
    cout << "Номер зачетки: ";
    cin >> student.n_z;
    
    cout << "Курс: ";
    cin >> student.kurs;
    
    // читаем всех студентов из файла
    vector<Student> students = readAllStudents();
    
    // добавляем нового студента
    students.push_back(student);
    
    // сохраняем всех студентов обратно в файл
    saveAllStudents(students);
    
    cout << "Студент успешно добавлен!" << endl;
}

// Функция для сравнения студентов по имени (для сортировки)
bool compareByName(const Student& a, const Student& b) {
    return a.name < b.name;  // сравниваем имена (по алфавиту)
}

// Функция для поиска и вывода студентов
void findAndDisplayStudents() {
    vector<Student> allStudents = readAllStudents();  // читаем всех студентов
    
    if (allStudents.empty()) {
        cout << "В базе нет студентов." << endl;
        return;
    }
    
    int choice;
    cout << "\n=== Поиск студентов ===" << endl;
    cout << "1. Показать всех студентов" << endl;
    cout << "2. Показать студентов определенного курса" << endl;
    cout << "Выберите вариант: ";
    cin >> choice;
    
    vector<Student> filteredStudents;  // вектор для отфильтрованных студентов
    
    if (choice == 1) {
        // берем всех студентов
        filteredStudents = allStudents;
    } else if (choice == 2) {
        // фильтруем по курсу
        int kurs;
        cout << "Введите курс: ";
        cin >> kurs;
        
        // ищем студентов нужного курса
        for (const auto& student : allStudents) {
            if (student.kurs == kurs) {
                filteredStudents.push_back(student);
            }
        }
        
        if (filteredStudents.empty()) {
            cout << "На курсе " << kurs << " нет студентов." << endl;
            return;
        }
    } else {
        cout << "Неверный выбор!" << endl;
        return;
    }
    
    // спрашиваем, нужно ли сортировать
    char sortChoice;
    cout << "Сортировать по имени? (y/n): ";
    cin >> sortChoice;
    
    if (sortChoice == 'y' || sortChoice == 'Y') {
        // сортируем по имени
        sort(filteredStudents.begin(), filteredStudents.end(), compareByName);
    }
    
    // выводим результаты
    cout << "\n=== Результаты поиска ===" << endl;
    cout << "Найдено студентов: " << filteredStudents.size() << endl << endl;
    
    for (const auto& student : filteredStudents) {
        cout << "Фамилия: " << student.fam << endl;
        cout << "Имя: " << student.name << endl;
        cout << "Отчество: " << student.otch << endl;
        cout << "Дата рождения: " << student.dt_r << endl;
        cout << "Группа: " << student.gr << endl;
        cout << "Номер зачетки: " << student.n_z << endl;
        cout << "Курс: " << student.kurs << endl;
        cout << "------------------------" << endl;
    }
}

// Функция для подсчета количества студентов
void countStudents() {
    vector<Student> students = readAllStudents();  // читаем всех студентов
    
    cout << "\n=== Количество студентов ===" << endl;
    cout << "Всего студентов: " << students.size() << endl;
    
    // можно добавить подсчет по курсам
    if (!students.empty()) {
        cout << "\nРаспределение по курсам:" << endl;
        
        // считаем студентов на каждом курсе
        int maxKurs = 0;
        for (const auto& student : students) {
            if (student.kurs > maxKurs) {
                maxKurs = student.kurs;
            }
        }
        
        for (int kurs = 1; kurs <= maxKurs; kurs++) {
            int count = 0;
            for (const auto& student : students) {
                if (student.kurs == kurs) {
                    count++;
                }
            }
            cout << "Курс " << kurs << ": " << count << " студентов" << endl;
        }
    }
}

// Главная функция программы
int main() {
    int choice;
    
    // Выводим меню в цикле, пока пользователь не выберет выход
    while (true) {
        cout << "\n=== Система учета студентов ===" << endl;
        cout << "1. Добавить нового студента" << endl;
        cout << "2. Найти студентов" << endl;
        cout << "3. Показать количество студентов" << endl;
        cout << "4. Выйти из программы" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        
        // Выполняем выбранное действие
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                findAndDisplayStudents();
                break;
            case 3:
                countStudents();
                break;
            case 4:
                cout << "До свидания!" << endl;
                return 0;  // завершаем программу
            default:
                cout << "Неверный выбор! Попробуйте еще раз." << endl;
        }
    }
    
    return 0;
}
