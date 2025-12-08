#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ===== 1. СЖАТИЕ СТРОК (RLE) =====
string compressString(const string& s) {
    if (s.empty()) {
        return s;
    }
    
    string compressed = "";
    int count = 1;
    char currentChar = s[0];
    
    for (int i = 1; i < s.length(); i++) {
        if (s[i] == currentChar) {
            count++;
        } else {
            compressed += currentChar;
            compressed += to_string(count);
            currentChar = s[i];
            count = 1;
        }
    }
    
    compressed += currentChar;
    compressed += to_string(count);
    
    return (compressed.length() < s.length()) ? compressed : s;
}

// ===== 2. ЧИСЛО В ТЕКСТОВЫЙ ВИД =====
vector<string> ones = {"", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"};
vector<string> teens = {"десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"};
vector<string> tens = {"", "", "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто"};
vector<string> hundreds = {"", "сто", "двести", "триста", "четыреста", "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот"};

string numberToText(int num) {
    if (num == 0) return "ноль";
    if (num < 0) return "минус " + numberToText(-num);
    
    string result = "";
    
    // Тысячи
    if (num >= 1000) {
        int thousands = num / 1000;
        if (thousands == 1) {
            result += "одна тысяча ";
        } else if (thousands == 2) {
            result += "две тысячи ";
        } else if (thousands >= 3 && thousands <= 4) {
            result += ones[thousands] + " тысячи ";
        } else if (thousands >= 5 && thousands <= 9) {
            result += ones[thousands] + " тысяч ";
        } else {
            // Для составных чисел тысяч
            result += numberToText(thousands) + " тысяч ";
        }
        num %= 1000;
    }
    
    // Сотни
    if (num >= 100) {
        result += hundreds[num / 100] + " ";
        num %= 100;
    }
    
    // Десятки и единицы
    if (num >= 20) {
        result += tens[num / 10] + " ";
        num %= 10;
        if (num > 0) {
            result += ones[num] + " ";
        }
    } else if (num >= 10) {
        result += teens[num - 10] + " ";
    } else if (num > 0) {
        result += ones[num] + " ";
    }
    
    // Убираем лишний пробел в конце
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    
    return result;
}

// ===== 3. ПРОВЕРКА ПЕРЕСТАНОВКИ СТРОК =====
bool isPermutation(const string& str1, const string& str2) {
    // Если длины разные, это не перестановка
    if (str1.length() != str2.length()) {
        return false;
    }
    
    // Создаём копии строк для сортировки
    string s1 = str1;
    string s2 = str2;
    
    // Сортируем обе строки
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    
    // Если отсортированные строки равны, это перестановка
    return s1 == s2;
}
