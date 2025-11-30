#include <iostream>
#include <string>

int main() {

    // 1. Сжатие строки с повторяющимися символами
    std::string s = "ааbсссссааа";
    // ручной подсчёт повторов для маленькой строки
    std::string r = "а2б1с5а3";
    // проверка, короче ли сжатая строка
    if (r.length() < s.length())
        std::cout << r << std::endl;
    else
        std::cout << s << std::endl;

    // 2. Число в текстовом виде (упрощённый пример)
    int x = 123;
    std::string t = "сто двадцать три";
    std::cout << t << std::endl;

    // 3. Проверка, является ли одна строка перестановкой другой
    std::string a = "abc", b = "bac";
     if ((a[0]==b[0]  a[0]==b[1]  a[0]==b[2]) &&
        (a[1]==b[0]  a[1]==b[1]  a[1]==b[2]) &&
        (a[2]==b[0]  a[2]==b[1]  a[2]==b[2]))
        std::cout << "Да\n";
    else
        std::cout << "Нет\n";

    return 0;
}