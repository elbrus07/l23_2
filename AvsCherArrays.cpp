#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

//1.Организовать ввод элементов массива с клавиатуры. Размер массива 
//также должен задаваться пользователем. Введённый массив вывести на экран. 

// int main(int argumentCount, char* argumentValues[]) {
//     int arraySize;
    
//     if (argumentCount > 1) {
//         arraySize = stoi(argumentValues[1]);
//         cout << "Размер массива из аргументов: " << arraySize << endl;
//     } else {
//         cout << "Введите размер массива: ";
//         cin >> arraySize;
//     }
    
//     vector<int> numbers(arraySize);
//     cout << "Введите " << arraySize << " элементов: ";
//     for (int index = 0; index < arraySize; index++) {
//         cin >> numbers[index];
//     }
    
//     cout << "Массив: ";
//     for (int value : numbers) {
//         cout << value << " ";
//     }
//     cout << endl;
    
//     return 0;
// }

//2.Создать массив случайного размера, состоящий из случайных целых чисел в заданном диапазоне. 

// int main() {
    
//     const int MIN_SIZE = 4;
//     const int MAX_SIZE = 20;
//     const int MIN_VALUE = 1;
//     const int MAX_VALUE = 100;
    
//     std::random_device randomDevice;
//     std::mt19937 generator(randomDevice());
//     std::uniform_int_distribution<> sizeDistribution(MIN_SIZE, MAX_SIZE);
//     std::uniform_int_distribution<> valueDistribution(MIN_VALUE, MAX_VALUE);
    
//     int arrayLength = sizeDistribution(generator);
//     std::vector<int> randomArray(arrayLength);
    
//     for (int position = 0; position < arrayLength; position++) {
//         randomArray[position] = valueDistribution(generator);
//     }
    
//     std::cout << "Размер массива: " << arrayLength << std::endl;
//     std::cout << "Массив: ";
//     for (int element : randomArray) {
//         std::cout << element << " ";
//     }
//     std::cout << std::endl;
    
//     return 0;
// }

//3.Заполнить массив случайным образом нулями и единицами так, чтобы количество 
//единиц было в точности равно количеству нулей. 

// int main(int argumentCount, char* argumentValues[]) {
//     int arrayLength;
    
//     if (argumentCount > 1) {
//         arrayLength = stoi(argumentValues[1]);
//     } else {
//         cout << "Введите размер (четный): ";
//         cin >> arrayLength;
//     }
    
//     if (arrayLength % 2 != 0) {
//         cout << "Размер должен быть четным!" << endl;
//         return 1;
//     }
    
//     vector<int> binaryArray(arrayLength);
//     int middle = arrayLength / 2;
    
//     // Заполняем половину единицами, половину нулями
//     for (int index = 0; index < middle; index++) {
//         binaryArray[index] = 1;
//     }
//     for (int index = middle; index < arrayLength; index++) {
//         binaryArray[index] = 0;
//     }
    
//     // Перемешиваем
//     random_device randomDevice;
//     mt19937 generator(randomDevice());
//     shuffle(binaryArray.begin(), binaryArray.end(), generator);
    
//     cout << "Массив 0 и 1: ";
//     for (int element : binaryArray) {
//         cout << element << " ";
//     }
//     cout << endl;
    
//     return 0;
// }

//4.Дан массив A из 2n элементов. Вычислить A1−A2 + A3−A4 + … +A2n−1 + A2n. 

// int main(int argumentCount, char* argumentValues[]) {
//     vector<int> mainArray;
    
//     if (argumentCount > 1) {
//         for (int i = 1; i < argumentCount; i++) {
//             mainArray.push_back(stoi(argumentValues[i]));
//         }
//     } else {
//         cout << "Введите элементы массива (четное количество: ";
//         int inputValue;
//         while (cin >> inputValue) {
//             mainArray.push_back(inputValue);
//         }
//     }
    
//     if (mainArray.size() % 2 != 0) {
//         cout << "Количество элементов должно быть четным!" << endl;
//         return 1;
//     }
    
//     int totalSum = 0;
//     for (int position = 0; position < mainArray.size(); position += 2) {
//         totalSum += mainArray[position] - mainArray[position + 1];
//     }
    
//     cout << "Результат: " << totalSum << endl;
    
//     return 0;
// }

//5.Дан массив и число p. Найти два различных числа в массиве, сумма которых наиболее близка к p. 

//6.Дан массив чисел. Заменить каждый элемент с чётным индексом на соседний слева элемент. 

// int main(int argumentCount, char* argumentValues[]) {
//     vector<int> numberArray;
    
//     if (argumentCount > 1) {
//         for (int i = 1; i < argumentCount; i++) {
//             numberArray.push_back(stoi(argumentValues[i]));
//         }
//     } else {
//         cout << "Введите элементы массива: ";
//         int inputNumber;
//         while (cin >> inputNumber) {
//             numberArray.push_back(inputNumber);
//         }
//     }
    
//     cout << "Исходный массив: ";
//     for (int value : numberArray) cout << value << " ";
//     cout << endl;
    
//     for (int index = 2; index < numberArray.size(); index += 2) {
//         numberArray[index] = numberArray[index - 1];
//     }
    
//     cout << "После замены: ";
//     for (int value : numberArray) cout << value << " ";
//     cout << endl;
    
//     return 0;
// }

//7.Дан массив. Поменять местами наибольший и наименьший элементы массива. 

// int main(int argumentCount, char* argumentValues[]) {
//     vector<int> dataArray;
    
//     if (argumentCount > 1) {
//         for (int i = 1; i < argumentCount; i++) {
//             dataArray.push_back(stoi(argumentValues[i]));
//         }
//     } else {
//         cout << "Введите элементы массива: ";
//         int inputElement;
//         while (cin >> inputElement) {
//             dataArray.push_back(inputElement);
//         }
//     }
    
//     cout << "Исходный массив: ";
//     for (int element : dataArray) cout << element << " ";
//     cout << endl;
    
//     auto minIterator = min_element(dataArray.begin(), dataArray.end());
//     auto maxIterator = max_element(dataArray.begin(), dataArray.end());
    
//     swap(*minIterator, *maxIterator);
    
//     cout << "После обмена: ";
//     for (int element : dataArray) cout << element << " ";
//     cout << endl;
    
//     return 0;
// }

//8.Даны два массива. Сформировать третий массив, состоящий из тех элементов, которые присутствуют в обоих массивах 

// int main() {
    
//     vector<int> firstArray = {1, 2, 3, 4, 5, 2};
//     vector<int> secondArray = {3, 4, 5, 6, 7, 4};
//     vector<int> commonElements;

//     for (int firstIndex = 0; firstIndex < firstArray.size(); firstIndex++) {
//         bool elementFound = false;
//         for (int secondIndex = 0; secondIndex < secondArray.size(); secondIndex++) {
//             if (firstArray[firstIndex] == secondArray[secondIndex]) {
//                 elementFound = true;
//                 break;
//             }
//         }
        
//         if (elementFound) {
//             bool alreadyAdded = false;
//             for (int thirdIndex = 0; thirdIndex < commonElements.size(); thirdIndex++) {
//                 if (commonElements[thirdIndex] == firstArray[firstIndex]) {
//                     alreadyAdded = true;
//                     break;
//                 }
//             }
//             if (!alreadyAdded) {
//                 commonElements.push_back(firstArray[firstIndex]);
//             }
//         }
//     }

//     cout << "Первый массив: ";
//     for (int value : firstArray) cout << value << " ";
//     cout << endl;
    
//     cout << "Второй массив: ";
//     for (int value : secondArray) cout << value << " ";
//     cout << endl;
    
//     cout << "Общие элементы: ";
//     for (int value : commonElements) cout << value << " ";
//     cout << endl;
    
//     return 0;
// }