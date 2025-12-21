#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

/*
Функция добавляет нового студента в файл базы данных.
Запрашивает у пользователя данные студента и сохраняет их в файл "db_stud.dat".
Данные записываются в формате: Фамилия#Имя#Отчество#ДатаРождения#Группа#Зачетка#Курс

Пример записи в файле: Иванов#Иван#Иванович#2000-05-15#101#IVT2001#3

Файл открывается в режиме добавления (ios::app), чтобы не удалять существующие данные.
*/
void addStudent() {
    ofstream file("db_stud.dat", ios::app);
    
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }
    
    string fam, name, otch, dt_r, gr, n_z;
    int kurs;
    
    cout << "--- Добавление нового студента ---" << endl;
    cout << "Фамилия: "<< "Имя: "<< "Отчество: "<< "Дата рождения (ГГГГ-ММ-ДД): "<< "Группа: "<< "Номер зачетки: "<< "Курс: ";
    cin >> fam >> name >> otch >> dt_r >> gr >> n_z >> kurs;

    
    file << fam << "#" << name << "#" << otch << "#" 
         << dt_r << "#" << gr << "#" << n_z << "#" << kurs << endl;
    
    file.close();
    cout << "Студент добавлен" << endl;
}

/*
Функция читает и выводит всех студентов из файла "db_stud.dat".
Каждая строка файла разбирается на отдельные поля с помощью разделителя '#'.
Выводит информацию о каждом студенте в читаемом формате с нумерацией.

В конце выводит общее количество студентов в файле.

Если файл не найден, выводится сообщение об ошибке.
*/
void readAllStudents() {
    ifstream file("db_stud.dat");
    
    if (!file.is_open()) {
        cout << "Файл не найден! Сначала добавьте студентов." << endl;
        return;
    }
    
    string line;
    int count = 0;
    
    cout << "\n--- Список всех студентов ---" << endl;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        // Разделяем строку вручную
        string parts[7];
        int partIndex = 0;
        string currentPart = "";
        
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == '#') {
                parts[partIndex] = currentPart;
                currentPart = "";
                partIndex++;
            } else {
                currentPart += line[i];
            }
        }
        parts[6] = currentPart;  // последняя часть (курс)
        
        // Выводим информацию о студенте
        cout << "Студент " << (count + 1) << ":" << endl;
        cout << "  ФИО: " << parts[0] << " " << parts[1] << " " << parts[2] << endl;
        cout << "  Дата рождения: " << parts[3] << endl;
        cout << "  Группа: " << parts[4] << endl;
        cout << "  Зачетка: " << parts[5] << endl;
        cout << "  Курс: " << parts[6] << endl;
        
        count++;
    }
    
    file.close();
    
    if (count == 0) {
        cout << "В файле нет записей о студентах." << endl;
    } else {
        cout << "Всего студентов: " << count << endl;
    }
}

/*
Функция ищет и выводит студентов по указанному курсу.

param searchKurs - номер курса для поиска (вводится пользователем)

Функция читает файл, находит в каждой строке последнее число (номер курса)
и сравнивает его с searchKurs. Если совпадение найдено, выводит данные студента.

Выводит студентов в упрощенном формате, заменяя символы '#' на пробелы.

Пример вывода для курса 3:
Иванов Иван Иванович 2000-05-15 101 IVT2001 3

В конце выводит количество найденных студентов.
*/
void findStudentsByKurs() {
    ifstream file("db_stud.dat");
    
    if (!file.is_open()) {
        cout << "Файл не найден!" << endl;
        return;
    }
    
    int searchKurs;
    cout << "Введите курс для поиска: ";
    cin >> searchKurs;
    
    string line;
    int found = 0;
    
    cout << "\n Студенты " << searchKurs << " курса " << endl;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        // Находим последний разделитель (#)
        int lastHash = 0;
        for (int i = line.length() - 1; i >= 0; i--) {
            if (line[i] == '#') {
                lastHash = i;
                break;
            }
        }
        
        // Извлекаем курс(число после последнего #)
        string kursStr = "";
        for (int i = lastHash + 1; i < line.length(); i++) {
            kursStr += line[i];
        }
        
        int kurs = stoi(kursStr);  // преобразуем строку в число
        
        if (kurs == searchKurs) {
            // Выводим всю строку
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '#') cout << " ";
                else cout << line[i];
            }
            cout << endl;
            found++;
        }
    }
    
    file.close();
    
    if (found == 0) {
        cout << "Студентов " << searchKurs << " курса не найдено." << endl;
    } else {
        cout << "Найдено: " << found << " студентов" << endl;
    }
}

/*
Функция подсчитывает общее количество студентов в базе данных.

Читает файл "db_stud.dat" и считает количество непустых строк.
Каждая непустая строка соответствует одному студенту.

Если файл не найден, выводит сообщение что студентов 0.

return - выводит результат на экран, но не возвращает значение.
*/
void countStudents() {
    ifstream file("db_stud.dat");
    
    if (!file.is_open()) {
        cout << "Файл не найден! Студентов: 0" << endl;
        return;
    }
    
    string line;
    int count = 0;
    
    while (getline(file, line)) {
        if (!line.empty()) {
            count++;
        }
    }
    
    file.close();
    cout << "Всего студентов в базе: " << count << endl;
}


int main() {
    int choice;
    
    // Создаем файл если его нет
    ofstream testFile("db_stud.dat", ios::app);
    testFile.close();
    
    do {
       
        cout << "1. Добавить нового студента" << endl;
        cout << "2. Показать всех студентов" << endl;
        cout << "3. Найти студентов по курсу" << endl;
        cout << "4. Посчитать количество студентов" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                readAllStudents();
                break;
            case 3:
                findStudentsByKurs();
                break;
            case 4:
                countStudents();
                break;
            case 0:
                cout << "Выход из программы..." << endl;
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
                break;
        }
        
    } while (choice != 0);
    
    return 0;
}