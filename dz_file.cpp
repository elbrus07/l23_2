#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
Функция добавляет нового студента в существующий файл stud.dat.
Используемые переменные:
fam, name, otch, dr, gr, z – данные студента
kurs – курс студента
out – файловый поток для записи
*/
void addStudent() {
    ofstream out("stud.dat", ios::app);

    string fam, name, otch, dr, gr, z;
    int kurs;

    cout << "Фамилия: ";
    cin >> fam;
    cout << "Имя: ";
    cin >> name;
    cout << "Отчество: ";
    cin >> otch;
    cout << "Дата рождения: ";
    cin >> dr;
    cout << "Группа: ";
    cin >> gr;
    cout << "Номер зачетки: ";
    cin >> z;
    cout << "Курс: ";
    cin >> kurs;

    out << fam << "#" << name << "#" << otch << "#"
        << dr << "#" << gr << "#" << z << "#"
        << kurs << endl;

    out.close();
}

/*
Функция подсчитывает количество студентов в файле stud.dat.
Используемые переменные:
in – файловый поток для чтения
line – строка из файла
count – счетчик строк
*/
int countStudents() {
    ifstream in("stud.dat");
    string line;
    int count = 0;

    while (getline(in, line)) {
        count++;
    }

    in.close();
    return count;
}

/*
Функция выводит студентов заданного курса,
отсортированных по имени.
Используемые переменные:
in – файловый поток для чтения
line – строка из файла
arr[] – массив строк студентов
kurs – курс из строки файла
findKurs – курс, введенный пользователем
*/
void showByKurs() {
    ifstream in("stud.dat");
    string line;
    string findKurs;

    string arr[100]; // простой массив строк
    int n = 0;

    cout << "Введите курс: ";
    cin >> findKurs;

    // чтение и отбор студентов по курсу
    while (getline(in, line)) {
        int last = line.rfind("#");
        string kurs = line.substr(last + 1);

        if (kurs == findKurs) {
            arr[n] = line;
            n++;
        }
    }

    in.close();

    // ПРОСТАЯ СОРТИРОВКА ПО ИМЕНИ (пузырёк)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {

            int p1 = arr[j].find("#");
            int p2 = arr[j].find("#", p1 + 1);
            string name1 = arr[j].substr(p1 + 1, p2 - p1 - 1);

            int p3 = arr[j + 1].find("#");
            int p4 = arr[j + 1].find("#", p3 + 1);
            string name2 = arr[j + 1].substr(p3 + 1, p4 - p3 - 1);

            if (name1 > name2) {
                string temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // вывод отсортированных студентов
    cout << "\nСтуденты курса " << findKurs << " (отсортированы по имени):\n";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << endl;
    }
}

int main() {
    int choice;

    cout << "1 - Добавить студента\n";
    cout << "2 - Показать студентов по курсу (с сортировкой)\n";
    cout << "3 - Подсчитать количество студентов\n";
    cout << "Ваш выбор: ";
    cin >> choice;

    if (choice == 1)
        addStudent();
    else if (choice == 2)
        showByKurs();
    else if (choice == 3)
        cout << "Количество студентов: "
             << countStudents() << endl;
    else
        cout << "Неверный выбор";

    return 0;
}