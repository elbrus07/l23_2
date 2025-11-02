#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
int main(){

//1.Для введённого пользователем целого числа выдать максимальную цифру, минимальную цифру и их произведение
/*
    int num;
    std::cout << "Введите целое число ";
    std::cin >> num;

    num = abs(num);

    // цикл for
    int copia = num;
    int max_cifr = 0;
    int min_cifr = 9;

    for (; copia > 0; copia /= 10)
    {
        int digit = copia % 10;
        if (digit > max_cifr) max_cifr = digit;
        if (digit < min_cifr) min_cifr = digit;
    }
    int product = max_cifr * min_cifr ;
    std::cout<<"максимальная цифра"<< max_cifr << endl ;
    std::cout<<"минимальная цифра"<< min_cifr << endl ;
    std::cout<<"их произведение"<< product << endl;

    // цикл while
    copia = num;
    max_cifr = 0;
    min_cifr = 9;

    while (copia > 0)
    {
        int digit = copia % 10;
        if (digit > max_cifr) max_cifr = digit;
        if (digit < min_cifr) min_cifr = digit;
        copia /= 10;
    }
     product = max_cifr * min_cifr ;
    std::cout<<"максимальная цифра"<< max_cifr << endl ;
    std::cout<<"минимальная цифра"<< min_cifr << endl ;
    std::cout<<"их произведение"<< product << endl;

    // цикл do while

    copia = num;
    max_cifr = 0;
    min_cifr = 9;

    do {
            int digit = copia % 10;
            if (digit > max_cifr) max_cifr = digit;
            if (digit < min_cifr) min_cifr = digit;
            copia /= 10;
    } while (copia > 0);
    product = max_cifr * min_cifr ;
    std::cout<<"максимальная цифра"<< max_cifr << endl ;
    std::cout<<"минимальная цифра"<< min_cifr << endl ;
    std::cout<<"их произведение"<< product << endl;
*/
//2.Последовательность содержит некоторое количество натуральных чисел и заканчивается числом 0 (0 не является элементом последовательности). Найти сумму вех элементов последовательности 
/*
    cout << "Введите последовательность чисел (0 для завершения):" << endl;

    // цикл for
    int sum = 0;
    int num;

    for (;;)
    {
        std::cin >> num;
        if (num == 0)
        {
            break;
        } else {
            sum += num;
        }  
    }
    std:: cout << "Сумма: " << sum << endl;

    // цикл while
    sum = 0;
    std::cin >> num;
    while (num != 0)
    {
        sum += num;
        std:: cin >> num;
    }
    std:: cout << "Сумма: " << sum << endl;

    // цикл do while
    sum = 0;
    do
    {
        std:: cin >> num;
        if (num != 0) sum += num;    
    } while (num != 0);

    std:: cout << "Сумма: " << sum << endl;
*/

//3. Дано целое число. Удалить из него заданную цифру. Например, если задано 1464235 и цифра 4, то должно получиться 16235.
/*    
    int num, digit_to_remove;
    std::cout << "Введите число: ";
    std::cin >> num;
    std::cout << "Введите цифру для удаления: ";
    std::cin >> digit_to_remove;

    int copia = abs(num);
    int result = 0;
    int multiplier = 1;     //множитель разряда
    
    // цикл for

    for (; copia > 0; copia /= 10)
    {
        int current_digit = copia % 10;
        if (current_digit != digit_to_remove)
        {
            result += current_digit * multiplier;
            multiplier *= 10;
        }
        
    }
    if (num < 0) result = -result;
    cout << "Результат: " << result << endl;

    //цикл while
    copia = abs(num);
    result = 0;
    multiplier = 1;

    while (copia > 0)
    {
        int current_digit = copia % 10;
        if (current_digit != digit_to_remove)
        {
            result += current_digit * multiplier;
            multiplier *= 10;
        }
        copia /= 10;
    }
    if (num < 0) result = -result;
    cout << "Результат: " << result << endl;

    // цикл do while
    copia = abs(num);
    result = 0;
    multiplier = 1;

    do {
        int current_digit = copia % 10;
        if (current_digit != digit_to_remove) 
        {
            result += current_digit * multiplier;
            multiplier *= 10;
        }
        copia /= 10;
    } while (copia > 0);
    if (num < 0) result = -result;
    cout << "Результат: " << result << endl;
*/

//4.Для каждого натурального числа в промежутке от N до M вывести все делители, кроме единицы и самого числа. Значения N и M вводятся с клавиатуры. 
/*
    int N, M;
    std::cout << "Введите N: ";
    std::cin >> N;
    std::cout << "Введите M: ";
    std::cin >> M;

    // цикл for

    for (int i = N; i <= M; i++)
    {
        cout << "Делители " << i << ": ";
        bool has_divisors = false;
        
        for (int j = 2; j <= i/2; j++) { // i/2   Потому что делитель не может быть больше половины числа кроме самого числа
            if (i % j == 0) {
                cout << j << " ";
                has_divisors = true;
            }
        }
        if (!has_divisors) cout << "нет";
        cout << endl;
    }

    //цикл while
    int current = N;
    while (current <= M) {
        cout << "Делители " << current << ": ";
        bool has_divisors = false;
        int divisor = 2;
        
        while (divisor <= current/2) {
            if (current % divisor == 0) {
                cout << divisor << " ";
                has_divisors = true;
            }
            divisor++;
        }
        if (!has_divisors) cout << "нет";
        cout << endl;
        current++;
    }
*/


//5.Вывести на экран двумерную таблицу умножения. 
    return 0;
}