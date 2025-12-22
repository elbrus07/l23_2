#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 1. Реализуйте функцию для выполнения простейшего сжатия строк с использованием счетчика 
// повторяющихся символов. Например, строка ааbсссссааа превращается в а2b1с5а3. Если сжатая
// строка не становится короче исходной, то метод возвращает исходную строку. Предполагается, 
// что строка состоит только из букв верхнего и нижнего регистра (a-z) 

string compress(string inputStr) {
    if (inputStr.length() == 0) {
        return inputStr;
    }
    
    string compressedResult;
    char prevChar = inputStr[0];
    int counter = 1;
    int strSize = inputStr.length();
    
    for (int pos = 1; pos < strSize; pos++) {
        if (inputStr[pos] == prevChar) {
            counter++;
        } else {
            compressedResult += prevChar;
            compressedResult += to_string(counter);
            
            prevChar = inputStr[pos];
            counter = 1;
        }
    }
    
    compressedResult += prevChar;
    compressedResult += to_string(counter);
    
    if (compressedResult.length() >= inputStr.length()) {
        compressedResult = inputStr;
    }
    
    return compressedResult;
}

int main() {
    string userInput;
    cout << "Введите строку: ";
    cin >> userInput;
    
    string output = compress(userInput);
    cout << "Результат: " << output << endl;
    
    return 0;
}



#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 1. Реализуйте функцию для выполнения простейшего сжатия строк с использованием счетчика 
// повторяющихся символов. Например, строка ааbсссссааа превращается в а2b1с5а3. Если сжатая
// строка не становится короче исходной, то метод возвращает исходную строку. Предполагается, 
// что строка состоит только из букв верхнего и нижнего регистра (a-z) 

string compress(string inputStr) {
    if (inputStr.length() == 0) {
        return inputStr;
    }
    
    string compressedResult;
    char prevChar = inputStr[0];
    int counter = 1;
    int strSize = inputStr.length();
    
    for (int pos = 1; pos < strSize; pos++) {
        if (inputStr[pos] == prevChar) {
            counter++;
        } else {
            compressedResult += prevChar;
            compressedResult += to_string(counter);
            
            prevChar = inputStr[pos];
            counter = 1;
        }
    }
    
    compressedResult += prevChar;
    compressedResult += to_string(counter);
    
    if (compressedResult.length() >= inputStr.length()) {
        compressedResult = inputStr;
    }
    
    return compressedResult;
}

int main() {
    string userInput;
    cout << "Введите строку: ";
    cin >> userInput;
    
    string output = compress(userInput);
    cout << "Результат: " << output << endl;
    
    return 0;
}


// 3. Для двух строк напишите метод, определяющий, является ли одна строка перестановкой другой 

bool checkPermutation(string firstStr, string secondStr) {
    if (firstStr.length() != secondStr.length()) {
        return false;
    }
    
    int charFrequency[256] = {0};
    
    for (int i = 0; i < firstStr.length(); i++) {
        charFrequency[firstStr[i]]++;
    }
    
    for (int i = 0; i < secondStr.length(); i++) {
        charFrequency[secondStr[i]]--;
        if (charFrequency[secondStr[i]] < 0) {
            return false;
        }
    }
    
    return true;
}

int main() {
    string string1, string2;
    cout << "Введите две строки: ";
    cin >> string1 >> string2;
    
    if (checkPermutation(string1, string2)) {
        cout << "Это перестановка" << endl;
    } else {
        cout << "Это не перестановка" << endl;
    }
    
    return 0;
}