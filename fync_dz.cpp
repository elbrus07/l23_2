#include <iostream>
using namespace std;

/*
1. Определить периметр треугольника, заданного координатами вершин. Длину стороны треугольника вычислять в функции. Посчитать среднее арифметическое периметров трех треугольников, координаты которых ввести с клавиатуры.
*/

int perimetr() {
    int sum = 0; // сумма всех периметров

    for (int t = 1; t <= 3; t++) {
        int x1, y1, x2, y2, x3, y3;
        cout << "Введите координаты " << t
             << "-го треугольника (x1 y1 x2 y2 x3 y3): ";
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

        // --- сторона AB ---
        int dx = x1 - x2;
        if (dx < 0) dx = -dx;
        int dy = y1 - y2;
        if (dy < 0) dy = -dy;

        int s = dx*dx + dy*dy;
        int r = 0;
        while (r*r <= s) r++;
        int a = r - 1;

        // --- сторона BC ---
        dx = x2 - x3;
        if (dx < 0) dx = -dx;
        dy = y2 - y3;
        if (dy < 0) dy = -dy;

        s = dx*dx + dy*dy;
        r = 0;
        while (r*r <= s) r++;
        int b = r - 1;

        // --- сторона CA ---
        dx = x3 - x1;
        if (dx < 0) dx = -dx;
        dy = y3 - y1;
        if (dy < 0) dy = -dy;

        s = dx*dx + dy*dy;
        r = 0;
        while (r*r <= s) r++;
        int c = r - 1;

        int p = a + b + c; // периметр этого треугольника
        sum += p;
    }

    return sum / 3; // средний периметр
}

/*
2. Сортировка массива 3 методами:
   sort1 — пузырёк (меняем соседей)
   sort2 — выбор (ищем минимальный)
   sort3 — вставка (вставляем в отсортированную часть)
*/

void sort1(int a[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-1; j++)
            if (a[j] > a[j+1]) {
                int t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
}

void sort2(int a[], int n) {
    for (int i = 0; i < n; i++) {
        int min = i;
        for (int j = i+1; j < n; j++)
            if (a[j] < a[min]) min = j;
        int t = a[i];
        a[i] = a[min];
        a[min] = t;
    }
}

void sort3(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int x = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > x) {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = x;
    }
}

/*
3. Написать функцию табуляции функции в точках x = 1,2,3,..., 12.
*/

void table() {
    for (int x = 1; x <= 12; x++) {
        int y = x*x - x;
        cout << "x=" << x << " y=" << y << endl;
    }
}

/*
4. Написать функцию вычисляющую количество совпадений числа x с элементами числового массива.
*/

int countMatch(int a[], int n, int x) {
    int c = 0;
    for (int i = 0; i < n; i++)
        if (a[i] == x) c++;
    return c;
}
