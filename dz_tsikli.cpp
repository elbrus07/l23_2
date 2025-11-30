#include <iostream>
using namespace std;

int main() {

    // =========================
    // 1. Для введённого пользователем целого числа выдать максимальную цифру, минимальную цифру и их произведение
    int x;

    cout << "Введите число для задачи 1:" << endl;
    cin >> x;

    // For
    int n = x, max_d = 0, min_d = 9;
    for (; n > 0; n /= 10) {
        int d = n % 10;
        if (d > max_d) max_d = d;
        if (d < min_d) min_d = d;
    }
    cout << "For: Max=" << max_d << " Min=" << min_d << " Prod=" << max_d*min_d << endl;

    // While
    n = x; max_d = 0; min_d = 9;
    while (n > 0) {
        int d = n % 10;
        if (d > max_d) max_d = d;
        if (d < min_d) min_d = d;
        n /= 10;
    }
    cout << "While: Max=" << max_d << " Min=" << min_d << " Prod=" << max_d*min_d << endl;

    // Do-while
    n = x; max_d = 0; min_d = 9;
    do {
        int d = n % 10;
        if (d > max_d) max_d = d;
        if (d < min_d) min_d = d;
        n /= 10;
    } while (n > 0);
    cout << "Do-while: Max=" << max_d << " Min=" << min_d << " Prod=" << max_d*min_d << endl;

    // =========================
    // 2. Последовательность натуральных чисел, заканчивается числом 0. Найти сумму всех элементов
    cout << "Введите последовательность для задачи 2 (заканчивается 0):" << endl;
    int sum;

    // For
    sum = 0;
    for (;;) {
        cin >> x;
        if (x == 0) break;
        sum += x;
    }
    cout << "For sum=" << sum << endl;

    // While
    sum = 0;
    cin >> x;
    while (x != 0) {
        sum += x;
        cin >> x;
    }
    cout << "While sum=" << sum << endl;

    // Do-while
    sum = 0;
    do {
        cin >> x;
        if (x != 0) sum += x;
    } while (x != 0);
    cout << "Do-while sum=" << sum << endl;

    // =========================
    // 3. Удалить из числа заданную цифру
    int d;
    cout << "Введите число и цифру для удаления (задача 3):" << endl;
    cin >> x >> d;

    int r, pow10;

    // For
    r = 0; pow10 = 1; n = x;
    for (; n > 0; n /= 10) {
        int t = n % 10;
        if (t != d) { r = t*pow10 + r; pow10 *= 10; }
    }
    cout << "For result=" << r << endl;

    // While
    r = 0; pow10 = 1; n = x;
    while (n > 0) {
        int t = n % 10;
        if (t != d) { r = t*pow10 + r; pow10 *= 10; }
        n /= 10;
    }
    cout << "While result=" << r << endl;

    // Do-while
    r = 0; pow10 = 1; n = x;
    do {
        int t = n % 10;
        if (t != d) { r = t*pow10 + r; pow10 *= 10; }
        n /= 10;
    } while (n > 0);
    cout << "Do-while result=" << r << endl;

    // =========================
    // 4. Для каждого числа от N до M вывести все делители, кроме 1 и самого числа
    int N, M;
    cout << "Введите N и M для задачи 4:" << endl;
    cin >> N >> M;

    // For
    for (int i = N; i <= M; i++) {
        cout << "Number " << i << ": ";
        for (int j = 2; j < i; j++) if (i % j == 0) cout << j << " ";
        cout << endl;
    }

    // While
    int i = N;
    while (i <= M) {
        cout << "Number " << i << ": ";
        int j = 2;
        while (j < i) {
            if (i % j == 0) cout << j << " ";
            j++;
        }
        cout << endl;
        i++;
    }

    // Do-while
    i = N;
    do {
        cout << "Number " << i << ": ";
        int j = 2;
        do {
            if (j < i && i % j == 0) cout << j << " ";
            j++;
        } while (j <= i);
        cout << endl;
        i++;
    } while (i <= M);

    // =========================
    // 5. Двумерная таблица умножения
    int n_table = 10;

    // For
    for (int a = 1; a <= n_table; a++) {
        for (int b = 1; b <= n_table; b++) cout << a*b << "\t";
        cout << endl;
    }

    // While
    int a = 1;
    while (a <= n_table) {
        int b = 1;
        while (b <= n_table) {
            cout << a*b << "\t";
            b++;
        }
        cout << endl;
        a++;
    }

    // Do-while
    a = 1;
    do {
        int b = 1;
        do {
            cout << a*b << "\t";
            b++;
        } while (b <= n_table);
            cout << endl;
            a++;
        } while (a <= n_table);

    return 0;
}