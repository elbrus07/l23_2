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
    string transform ( int number) {

    if (number == 0)  {
        return "ноль";
    }
    string thousands, hundreds, tens, units, tens_units;
    int a = number / 1000;  // тысячи
    int b = (number / 100) % 10;   //сотни
    int c = (number / 10 ) % 10;     //десятки
    int d = number  % 10;    // единицы

        //тысячи
        if (a == 1) {
            thousands = "одна тысяча" ;
        } else if (a == 2) {
            thousands = "две тысячи";
        } else if (a == 3) {
            thousands = "три тысячи";
        } else if (a == 4) {
            thousands = "четыре тысячи";
        }else if (a == 5) {
            thousands = "пять тысяч";
        }else if (a == 6) {
            thousands = "шесть тысяч";
        }else if (a == 7) {
            thousands = "семь тысяч";
        }else if (a == 8) {
            thousands = "восемь тысяч";
        }else if (a == 9) {
            thousands = "девять тысяч";
        }else if (a == 0) {
            thousands = "";
        }

        //сотни
        if (b == 1) {
            hundreds = "сто";
        } else if ( b == 2) {
            hundreds = "двести";
        }else if ( b == 3) {
            hundreds = "триста";
        }else if ( b == 4) {
            hundreds = "четыреста";
        }else if ( b == 5) {
            hundreds = "пятьсот";
        }else if ( b == 6) {
            hundreds = "шестьсот";
        }else if ( b == 7) {
            hundreds = "семьсот";
        }else if ( b == 8) {
            hundreds = "восемьсот";
        }else if ( b == 9) {
            hundreds = "девятьсот";
        }else if (a == 0) {
            hundreds = "";
        }

    if ( c == 1){   // Десятки и единицы (особые случаи 10-19)
        if (c == 1 && d ==0) {
            tens_units = "десять";
        } else if ( c== 1 && d == 1){
            tens_units = "одиннадцать";
        } else if ( c== 1 && d == 2){
            tens_units = "двенадцать";
        } else if ( c== 1 && d == 3){
            tens_units = "тринадцать";
        } else if ( c== 1 && d == 4){
            tens_units = "четырнадцать";
        } else if ( c== 1 && d == 5){
            tens_units = "пятнадцать";
        } else if ( c== 1 && d == 6){
            tens_units = "шестнадцать";
        } else if ( c== 1 && d == 7){
            tens_units = "семнадцать";
        } else if ( c== 1 && d == 8){
            tens_units = "восемнадцать";
        } else if ( c== 1 && d == 9){
            tens_units = "девятнадцать";
        } 
        tens = "";
        units = "";
    }else {
        // Обычные десятки (20-90)
        if ( c == 2) {
            tens = "двадцать";
        }else if ( c == 3) {
            tens = "тридцать";
        }else if ( c == 4) {
            tens = "сорок";
        }else if ( c == 5) {
            tens = "пятьдесят";
        }else if ( c == 6) {
            tens = "шестьдесят";
        }else if ( c == 7) {
            tens = "семьдесят";
        }else if ( c == 8) {
            tens = "восемьдесят";
        }else if ( c == 9) {
            tens = "девяносто";
        } else if (c == 0) {
            tens = "";
        }
        //единицы
        if ( d == 1 ) {
            units = "один";
        }else if ( d == 2) {
            units = "два";
        }else if ( d == 3) {
            units = "три";
        }else if ( d == 4) {
            units = "четыре";
        }else if ( d == 5) {
            units = "пять";
        }else if ( d == 6) {
            units = "шесть";
        }else if ( d == 7) {
            units = "семь";
        }else if ( d == 8) {
            units = "восемь";
        }else if ( d == 9) {
            units = "девять";
        } else if (d == 0) {
            units = "";
        }
        tens_units = "";
    }
    string result = thousands + hundreds + tens + units + tens_units;
    return  result;
}

//3. Для двух строк напишите метод, определяющий, является ли одна строка перестановкой другой








int main() {
//1.
    string test = "aaabbbbccv";
    cout << "Исходная: " << test << " -> Сжатая: " << compress(test) << endl;

//2
    cout << transform(1234) << endl;  // одна тысяча двести тридцать четыре
    cout << transform(567) << endl;   // пятьсот шестьдесят семь
    cout << transform(19) << endl;    // девятнадцать
    cout << transform(0) << endl;     // ноль
    return 0;

}
