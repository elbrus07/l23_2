#include <iostream>
using namespace std;

int main(){
    // 1. Для введённого пользователем целого числа выдать максимальную цифру, минимальную цифру и их произведение
    /*
    int number;
    cout << "Введите число: ";
    cin >> number;
    
    // for
    int temp = number;
    int max_digit = 0, min_digit = 9;
    for (; temp > 0; temp = temp / 10) {
        int digit = temp % 10;
        if (digit > max_digit){
        	max_digit = digit;
        }
        if (digit < min_digit){
         	min_digit = digit;
        }
    }
    cout << "FOR: Макс=" << max_digit << " Мин=" << min_digit << " Произв=" << max_digit * min_digit << endl;
    
    // while
    temp = number;
    max_digit = 0; min_digit = 9;
    while (temp > 0) {
        int digit = temp % 10;
        if (digit > max_digit) max_digit = digit;
        if (digit < min_digit) min_digit = digit;
        temp = temp / 10;
    }
    cout << "WHILE: Макс=" << max_digit << " Мин=" << min_digit << " Произв=" << max_digit * min_digit << endl;
    
    // do while
    temp = number;
    max_digit = 0; min_digit = 9;
    do {
        int digit = temp % 10;
        if (digit > max_digit) max_digit = digit;
        if (digit < min_digit) min_digit = digit;
        temp = temp / 10;
    } while (temp > 0);
    cout << "DO WHILE: Макс=" << max_digit << " Мин=" << min_digit << " Произв=" << max_digit * min_digit << endl;
    */

    // 2. Найти сумму элементов последовательности
    /*
    int sum = 0;
    int n = 1;
    cout << "Вводите натуральные числа. По окончании введите 0" << endl;
    
    // for
    for (cin >> n; n != 0;) {
        sum = sum + n;
    }
    cout << "FOR: Сумма=" << sum << endl;
    
    // while
    sum = 0;
    n = 1;
    cout << "Вводите натуральные числа. По окончании введите 0" << endl;
    cin >> n;
    while (n != 0) {
        sum = sum + n;
        cin >> n;
    }
    cout << "WHILE: Сумма=" << sum << endl;
    
    // do while
    sum = 0;
    n = 1;
    cout << "Вводите натуральные числа. По окончании введите 0" << endl;
    do {
        cin >> n;
        sum = sum + n;
    } while (n != 0);
    cout << "DO WHILE: Сумма=" << sum << endl;
    
*/
    // 3. Удалить из числа заданную цифру
    /*
    int num, digit;
    cout << "Введите число: ";
    cin >> num;
    cout << "Введите цифру для удаления: ";
    cin >> digit;
    
    // for
    int temp = num;
    int result = 0, multiplier = 1;
    for (; temp > 0; temp = temp / 10) {
        int d = temp % 10;
        if (d != digit) {
            result = result + d * multiplier;
            multiplier = multiplier * 10;
            // result = result * 10 + d;
        }
    }
    cout << "FOR: Результат=" << result << endl;
    
    // while
    temp = num;
    result = 0; multiplier = 1;
    while (temp > 0) {
        int d = temp % 10;
        if (d != digit) {
            result = result + d * multiplier;
            multiplier = multiplier * 10;
        }
        temp = temp / 10;
    }
    cout << "WHILE: Результат=" << result << endl;
    
    // do while
    temp = num;
    result = 0; multiplier = 1;
    do {
        int d = temp % 10;
        if (d != digit) {
            result = result + d * multiplier;
            multiplier = multiplier * 10;
        }
        temp = temp / 10;
    } while (temp > 0);
    cout << "DO WHILE: Результат=" << result << endl;
    
*/
    // 4. Для каждого натурального числа вывести делители
    /*
    int N, M;
    cout << "Введите начало и конец промежутка: ";
    cin >> N >> M;
    
    // for
    cout << "FOR:" << endl;
    for (int i = N; i <= M; i++) {
        cout << i << ": ";
        for (int j = 2; j < i; j++) {
            if (i % j == 0) {
                cout << j << " ";
            }
        }
        cout << endl;
    }
    
    // while
    cout << "WHILE:" << endl;
    int i = N;
    while (i <= M) {
        cout << i << ": ";
        int j = 2;
        while (j < i) {
            if (i % j == 0) {
                cout << j << " ";
            }
            j++;
        }
        cout << endl;
        i++;
    }
    
    // do while
    cout << "DO WHILE:" << endl;
    i = N;
    do {
        cout << i << ": ";
        int j = 2;
        do {
            if (i % j == 0) {
                cout << j << " ";
            }
            j++;
        } while (j < i);
        cout << endl;
        i++;
    } while (i <= M);
    
*/
    // 5. Таблица умножения
    
    // for
    cout << "FOR:" << endl;
    for (int a = 1; a <= 10; a++) {
        for (int b = 1; b <= 10; b++) {
            cout << a * b << "\t";
        }
        cout << endl;
    }
    
    // while
    cout << "WHILE:" << endl;
    int a = 1;
    while (a <= 10) {
        int b = 1;
        while (b <= 10) {
            cout << a * b << "\t";
            b++;
        }
        cout << endl;
        a++;
    }
    
    // do while
    cout << "DO WHILE:" << endl;
    a = 1;
    do {
        int b = 1;
        do {
            cout << a * b << "\t";
            b++;
        } while (b <= 10);
        cout << endl;
        a++;
    } while (a <= 10);

    return 0;
}
