#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// читает существующий файл
void readFile() {
    ifstream f("stud.dat");
    string line;

    if (!f.is_open()) {
        cout << "файл не открылся почему-то\n";
        return;
    }

    // пока просто читаю первую строку
    getline(f, line);  //(прочитать остальные строки)
    cout << line << endl;
}

// считает строки (недоделано)
int countLines() {
    ifstream f("stud.dat");
    string s;
    int c = 0;

    while (getline(f, s)) {
        c = c + 1;
    }

    return c;
}

int main() {

    readFile(); // читает файл stud.dat
    cout << "кол-во строк: " << countLines() << endl;

    // НУЖНО!!
    //  сделать сортировку
    //  фильтр по курсу
    //  сделать запись в файл

    return 0;
}
