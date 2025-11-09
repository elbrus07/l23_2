#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
using namespace std;
//1. Реализуйте функцию для выполнения простейшего сжатия строк с использованием счетчика повторяющихся символов. Например, строка ааbсссссааа превращается в а2b1с5а3. Если сжатая строка не становится короче исходной, то метод возвращает исходную строку. Предполагается, что строка состоит только из букв верхнего и нижнего регистра (a-z)

string compress (string str) {
    if (str.length() <= 2){
        return str ;
    }

    int count =1  ;
    string compressed ;


    for (int i = 0; i < str.length(); i++) {
        if (str[i] == str[i + 1] && i + 1 < str.length()  ) {
            count++;
        } else {
           
            compressed += str[i];
            compressed += to_string(count);
            count = 1; 
        }

        if (compressed.length() < str.length()){
            return compressed ;

        } else {
            return str;
        }
    }
}

//2. Задано целое число. Выведите его значение в текстовом виде (например, одна тысяча двести тридцать четыре).


//3. Для двух строк напишите метод, определяющий, является ли одна строка перестановкой другой








int main() {
//1.
    string test = "aaabbbbccv";
    cout << "Исходная: " << test << " -> Сжатая: " << compress(test) << endl;

//2

    return 0;
}