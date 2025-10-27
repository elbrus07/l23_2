#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;
    cout << "Выберите задание (1-6): ";
    cin >> choice;

    switch (choice) {

    case 1: {
        // 1. Определить, является ли символ цифрой
        char c;
        cout << "Введите один символ: ";
        cin >> c;
        if (c >= '0' && c <= '9')
            cout << "Это цифра.\n";
        else
            cout << "Это не цифра.\n";
        break;
    }

    case 2: {
        // 2. Проверить, могут ли числа быть углами треугольника
        int a, b, c;
        cout << "Введите три угла: ";
        cin >> a >> b >> c;
        if (a > 0 && b > 0 && c > 0 && a + b + c == 180)
            cout << "Это углы треугольника.\n";
        else
            cout << "Это не углы треугольника.\n";
        break;
    }

    case 3: {
        // 3. Проверить, делится ли число на все свои цифры
        int n;
        cout << "Введите трёхзначное число: ";
        cin >> n;

        int a = n / 100;
        int b = (n / 10) % 10;
        int c = n % 10;

        if (b == 0 || c == 0) {
            cout << "Ошибка: деление на ноль невозможно.\n";
            break;
        }

        if (n % a == 0 && n % b == 0 && n % c == 0)
            cout << "Число делится на все свои цифры.\n";
        else
            cout << "Число не делится на все свои цифры.\n";
        break;
    }

    case 4: {
        // 4. Найти произведение максимальной и минимальной цифр
        int n;
        cout << "Введите трёхзначное число: ";
        cin >> n;

        int a = n / 100;
        int b = (n / 10) % 10;
        int c = n % 10;

        int max = a, min = a;
        if (b > max) max = b;
        if (c > max) max = c;
        if (b < min) min = b;
        if (c < min) min = c;

        cout << "Произведение максимальной и минимальной цифр: " << max * min << endl;
        break;
    }

    case 5: {
        // 5. Составить максимально возможное число из цифр
        int n;
        cout << "Введите трёхзначное число: ";
        cin >> n;

        int a = n / 100;
        int b = (n / 10) % 10;
        int c = n % 10;

        // Сортировка трёх цифр по убыванию
        if (a < b) swap(a, b);
        if (a < c) swap(a, c);
        if (b < c) swap(b, c);

        int result = a * 100 + b * 10 + c;
        cout << "Максимально возможное число: " << result << endl;
        break;
    }

    case 6: {
        // 6. Проверить делимость второй цифры на 3
        int n;
        cout << "Введите трёхзначное число: ";
        cin >> n;

        int a = n / 100;
        int b = (n / 10) % 10;
        int c = n % 10;

        if (b % 3 == 0)
            b = b / 3;
        else
            b = 0;

        int result = a * 100 + b * 10 + c;
        cout << "Результат: " << result << endl;
        break;
    }

    default:
        cout << "Неверный номер задания!\n";
    }

    return 0;
}
