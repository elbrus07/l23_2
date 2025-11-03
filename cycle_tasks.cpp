#include <iostream>
using namespace std;

int main() {
    int choice;
    
    do {
        cout << "\n=== ВЫБЕРИТЕ ЗАДАНИЕ ===" << endl;
        cout << "1. Макс/мин цифра числа и их произведение" << endl;
        cout << "2. Сумма последовательности до 0" << endl;
        cout << "3. Удаление цифры из числа" << endl;
        cout << "4. Делители чисел в промежутке" << endl;
        cout << "5. Таблица умножения" << endl;
        cout << "0. Выход" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;
        
        switch(choice) {
            case 1: {
                // Задание 1: Максимальная и минимальная цифра числа
                int number;
                cout << "\n--- Задание 1 ---" << endl;
                cout << "Введите целое число: ";
                cin >> number;
                
                int temp = abs(number);
                
                if (temp == 0) {
                    cout << "Максимальная цифра: 0" << endl;
                    cout << "Минимальная цифра: 0" << endl;
                    cout << "Произведение: 0" << endl;
                    break;
                }
                
                int maxDigit = 0;
                int minDigit = 9;
                
                // Цикл for
                cout << "\nЦИКЛ FOR:" << endl;
                maxDigit = 0; minDigit = 9;
                for (int n = temp; n > 0; n /= 10) {
                    int digit = n % 10;
                    if (digit > maxDigit) maxDigit = digit;
                    if (digit < minDigit) minDigit = digit;
                }
                cout << "Максимальная цифра: " << maxDigit << endl;
                cout << "Минимальная цифра: " << minDigit << endl;
                cout << "Произведение: " << maxDigit * minDigit << endl;
                
                // Цикл while
                cout << "\nЦИКЛ WHILE:" << endl;
                maxDigit = 0; minDigit = 9;
                int n = temp;
                while (n > 0) {
                    int digit = n % 10;
                    if (digit > maxDigit) {
	                    maxDigit = digit;
	                }
                    if (digit < minDigit){
                    	minDigit = digit;
                    }
                    n /= 10;
                }
                cout << "Максимальная цифра: " << maxDigit << endl;
                cout << "Минимальная цифра: " << minDigit << endl;
                cout << "Произведение: " << maxDigit * minDigit << endl;
                
                // Цикл do while
                cout << "\nЦИКЛ DO WHILE:" << endl;
                maxDigit = 0; minDigit = 9;
                n = temp;
                do {
                    int digit = n % 10;
                    if (digit > maxDigit) maxDigit = digit;
                    if (digit < minDigit) minDigit = digit;
                    n /= 10;
                } while (n > 0);
                cout << "Максимальная цифра: " << maxDigit << endl;
                cout << "Минимальная цифра: " << minDigit << endl;
                cout << "Произведение: " << maxDigit * minDigit << endl;
                break;
            }
            
            case 2: {
                // Задание 2: Сумма последовательности до 0
                cout << "\n--- Задание 2 ---" << endl;
                cout << "Вводите натуральные числа (0 для окончания):" << endl;
                
                int sum = 0, num;
                cout << "\nЦИКЛ DO WHILE (введите числа снова):" << endl;
                sum = 0;
                do {
                    cin >> num;
                    if (num != 0) sum += num;
                } while (num != 0);
                cout << "Сумма: " << sum << endl;
                break;
            }
            
            case 3: {
                // Задание 3: Удаление цифры из числа
                cout << "\n--- Задание 3 ---" << endl;
                int number, digitToRemove;
                cout << "Введите число: ";
                cin >> number;
                cout << "Введите цифру для удаления: ";
                cin >> digitToRemove;
                
                int result = 0, multiplier = 1;
                int temp = abs(number);
                
                // Цикл for
                cout << "\nЦИКЛ FOR:" << endl;
                result = 0; multiplier = 1;
                for (int n = temp; n > 0; n /= 10) {
                    int digit = n % 10;
                    if (digit != digitToRemove) {
                        result += digit * multiplier;
                        multiplier *= 10;
                    }
                }
                if (number < 0) result = -result;
                cout << "Результат: " << result << endl;
                
                // Цикл while
                cout << "\nЦИКЛ WHILE:" << endl;
                result = 0; multiplier = 1;
                int n = temp;
                while (n > 0) {
                    int digit = n % 10;
                    if (digit != digitToRemove) {
                        result += digit * multiplier;
                        multiplier *= 10;
                    }
                    n /= 10;
                }
                if (number < 0) result = -result;
                cout << "Результат: " << result << endl;
                
                // Цикл do while
                cout << "\nЦИКЛ DO WHILE:" << endl;
                result = 0; multiplier = 1;
                n = temp;
                do {
                    int digit = n % 10;
                    if (digit != digitToRemove) {
                        result += digit * multiplier;
                        multiplier *= 10;
                    }
                    n /= 10;
                } while (n > 0);
                if (number < 0) result = -result;
                cout << "Результат: " << result << endl;
                break;
            }
            
            case 4: {
                // Задание 4: Делители чисел в промежутке
                cout << "\n--- Задание 4 ---" << endl;
                int N, M;
                cout << "Введите N: ";
                cin >> N;
                cout << "Введите M: ";
                cin >> M;
                
                if (N > M) {
                    cout << "N должно быть меньше или равно M!" << endl;
                    break;
                }
                
                // Цикл for
                cout << "\nЦИКЛ FOR:" << endl;
                for (int i = N; i <= M; i++) {
                    cout << i << ": ";
                    bool hasDivisors = false;
                    for (int j = 2; j <= i/2; j++) {
                        if (i % j == 0) {
                            cout << j << " ";
                            hasDivisors = true;
                        }
                    }
                    if (!hasDivisors) cout << "нет делителей";
                    cout << endl;
                }
                
                // Цикл while
                cout << "\nЦИКЛ WHILE:" << endl;
                int i = N;
                while (i <= M) {
                    cout << i << ": ";
                    bool hasDivisors = false;
                    int j = 2;
                    while (j <= i/2) {
                        if (i % j == 0) {
                            cout << j << " ";
                            hasDivisors = true;
                        }
                        j++;
                    }
                // Цикл for
                cout << "\nЦИКЛ FOR:" << endl;
                sum = 0;
                for (;;) {
                    cin >> num;
                    if (num == 0) break;
                    sum += num;
                }
                cout << "Сумма: " << sum << endl;
                
                // Цикл while
                cout << "\nЦИКЛ WHILE (введите числа снова):" << endl;
                sum = 0;
                while (num != 0) {
                    sum += num;
                    cin >> num;
                }
                cout << "Сумма: " << sum << endl;
                
                // Цикл do while
if (!hasDivisors) cout << "нет делителей";
                    cout << endl;
                    i++;
                }
                
                // Цикл do while
                cout << "\nЦИКЛ DO WHILE:" << endl;
                i = N;
                do {
                    cout << i << ": ";
                    bool hasDivisors = false;
                    int j = 2;
                    do {
                        if (i % j == 0 && j <= i/2) {
                            cout << j << " ";
                            hasDivisors = true;
                        }
                        j++;
                    } while (j <= i/2);
                    if (!hasDivisors) cout << "нет делителей";
                    cout << endl;
                    i++;
                } while (i <= M);
                break;
            }
            
            case 5: {
                // Задание 5: Таблица умножения
                cout << "\n--- Задание 5 ---" << endl;
                
                // Цикл for
                cout << "\nЦИКЛ FOR:" << endl;
                for (int i = 1; i <= 10; i++) {
                    for (int j = 1; j <= 10; j++) {
                        cout << i * j << "\t";
                    }
                    cout << endl;
                }
                
                // Цикл while
                cout << "\nЦИКЛ WHILE:" << endl;
                int i = 1;
                while (i <= 10) {
                    int j = 1;
                    while (j <= 10) {
                        cout << i * j << "\t";
                        j++;
                    }
                    cout << endl;
                    i++;
                }
                
                // Цикл do while
                cout << "\nЦИКЛ DO WHILE:" << endl;
                i = 1;
                do {
                    int j = 1;
                    do {
                        cout << i * j << "\t";
                        j++;
                    } while (j <= 10);
                    cout << endl;
                    i++;
                } while (i <= 10);
                break;
            }
            
            case 0:
                cout << "Выход из программы..." << endl;
                break;
                
            default:
                cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);
    
    return 0;
}

