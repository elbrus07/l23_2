#include <iostream>
#include <cmath>
#include <string>
using namespace std;
//1. Реализуйте функцию для выполнения простейшего сжатия строк с использованием счетчика повторяющихся символов. Например, строка ааbсссссааа превращается в а2b1с5а3. Если сжатая строка не становится короче исходной, то метод возвращает исходную строку. Предполагается, что строка состоит только из букв верхнего и нижнего регистра (a-z)

string squeeze(string str) {
    if (str.empty()) {
        return "";
    }
    
    string result;
    char current = str[0];
    int count = 1;
    
    for (int i = 1; i < str.length(); ++i) {
        if (str[i] == current) {
            count++;
        } else {
            result += current;
            result += to_string(count);
            current = str[i];
            count = 1;
        }
    }
    
    
    result += current;
    result += to_string(count);
    
    if (result.length() >= str.length()) {
        return str;
    } else {
        return result;
    }
}
  
//2. Задано целое число. Выведите его значение в текстовом виде (например, одна тысяча двести тридцать четыре).

string number_to_text(int num) {
    if (num == 0) {
        return "ноль";
    }
    
    string thou, hun, ten, unit, teen;
    int thou_val = num / 1000;  
    int hun_val = (num / 100) % 10;  
    int ten_val = (num / 10) % 10;   
    int unit_val = num % 10;  

    if (thou_val == 1) {
        thou = "одна тысяча ";
    } else if (thou_val == 2) {
        thou = "две тысячи ";
    } else if (thou_val == 3) {
        thou = "три тысячи ";
    } else if (thou_val == 4) {
        thou = "четыре тысячи ";
    } else if (thou_val == 5) {
        thou = "пять тысяч ";
    } else if (thou_val == 6) {
        thou = "шесть тысяч ";
    } else if (thou_val == 7) {
        thou = "семь тысяч ";
    } else if (thou_val == 8) {
        thou = "восемь тысяч ";
    } else if (thou_val == 9) {
        thou = "девять тысяч ";
    } else {
        thou = "";
    }
    
    if (hun_val == 1) {
        hun = "сто ";
    } else if (hun_val == 2) {
        hun = "двести ";
    } else if (hun_val == 3) {
        hun = "триста ";
    } else if (hun_val == 4) {
        hun = "четыреста ";
    } else if (hun_val == 5) {
        hun = "пятьсот ";
    } else if (hun_val == 6) {
        hun = "шестьсот ";
    } else if (hun_val == 7) {
        hun = "семьсот ";
    } else if (hun_val == 8) {
        hun = "восемьсот ";
    } else if (hun_val == 9) {
        hun = "девятьсот ";
    } else {
        hun = "";
    }
    
    if (ten_val == 1) {  
        if (unit_val == 0) {
            teen = "десять ";
        } else if (unit_val == 1) {
            teen = "одиннадцать ";
        } else if (unit_val == 2) {
            teen = "двенадцать ";
        } else if (unit_val == 3) {
            teen = "тринадцать ";
        } else if (unit_val == 4) {
            teen = "четырнадцать ";
        } else if (unit_val == 5) {
            teen = "пятнадцать ";
        } else if (unit_val == 6) {
            teen = "шестнадцать ";
        } else if (unit_val == 7) {
            teen = "семнадцать ";
        } else if (unit_val == 8) {
            teen = "восемнадцать ";
        } else if (unit_val == 9) {
            teen = "девятнадцать ";
        }
        ten = "";
        unit = "";
    } else {
        if (ten_val == 2) {
            ten = "двадцать ";
        } else if (ten_val == 3) {
            ten = "тридцать ";
        } else if (ten_val == 4) {
            ten = "сорок ";
        } else if (ten_val == 5) {
            ten = "пятьдесят ";
        } else if (ten_val == 6) {
            ten = "шестьдесят ";
        } else if (ten_val == 7) {
            ten = "семьдесят ";
        } else if (ten_val == 8) {
            ten = "восемьдесят ";
        } else if (ten_val == 9) {
            ten = "девяносто ";
        } else {
            ten = "";
        }
        
        
        if (unit_val == 1) {
            unit = "один ";
        } else if (unit_val == 2) {
            unit = "два ";
        } else if (unit_val == 3) {
            unit = "три ";
        } else if (unit_val == 4) {
            unit = "четыре ";
        } else if (unit_val == 5) {
            unit = "пять ";
        } else if (unit_val == 6) {
            unit = "шесть ";
        } else if (unit_val == 7) {
            unit = "семь ";
        } else if (unit_val == 8) {
            unit = "восемь ";
        } else if (unit_val == 9) {
            unit = "девять ";
        } else {
            unit = "";
        }
        teen = "";
    }

    string full_text = thou + hun + ten + unit + teen;
        
    return full_text;
}

  
//3. Для двух строк напишите метод, определяющий, является ли одна строка перестановкой другой

bool is_anagram_check(string str1, string str2) {
    if (str1.length() != str2.length()) {
        return false;
    }
    
    for (int i = 0; i < str1.length(); ++i) {
        int pos = str2.find(str1[i]);
        if (pos > str1.length()) {
            return false;  
        }
        str2.erase(pos, 1); 
    }
    
    return true;
}

    
    
int main(){
    //номер 1
    /*
    string test1 = "ssssFegdddd";
    string res = squeeze(test1);
    cout << "Исходная: " << test1 << endl;
    cout << "Сжатая: " << res << endl;
    */
    
    //номер 2
    /*
    int test_num = 4534;
    cout << "Число " << test_num << " словами: " << number_to_text(test_num) << endl;
    */
    
    //номер 3
    /*
    string str1 = "listen";
    string str2 = "silent";
    cout << is_anagram_check(str1, str2) << endl;
    */
   
    return 0;
}
