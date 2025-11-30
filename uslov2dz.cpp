#include <iostream>
using namespace std;

int main() {
    // 1. Дана строка, состоящая из одного символа. Определить является ли этот символ цифрой.
    char c;
    cin >> c;
    if (c >= '0' && c <= '9') cout << "digit\n";
    else cout << "not digit\n";

    // 2. Даны три числа. Программа должна проверить могут ли эти числа являться углами треугольника.
    int a, b, d;
    cin >> a >> b >> d;
    if (a + b > d && a + d > b && b + d > a) cout << "triangle\n";
    else cout << "not triangle\n";

    // 3. Дано трехзначное число. Проверить делится ли это число на все свои цифры.
    int n;
    cin >> n;
    int x = n / 100;
    int y = (n / 10) % 10;
    int z = n % 10;
    if (x != 0 && y != 0 && z != 0 && n % x == 0 && n % y == 0 && n % z == 0) cout << "yes\n";
    else cout << "no\n";

    // 4. Дано трехзначное число. Найти произведение максимальной и минимальной цифр этого числа.
    cin >> n;
    x = n / 100;
    y = (n / 10) % 10;
    z = n % 10;
    int maxc = x;
    if (y > maxc) maxc = y;
    if (z > maxc) maxc = z;
    int minc = x;
    if (y < minc) minc = y;
    if (z < minc) minc = z;
    cout << maxc * minc << "\n";

    // 5. Дано трехзначное число. Составить из его цифр максимально возможное по величине число.
    cin >> n;
    x = n / 100;
    y = (n / 10) % 10;
    z = n % 10;
    int a1, b1, c1;
    if (x >= y && x >= z) { a1 = x; b1 = (y >= z ? y : z); c1 = (y >= z ? z : y); }
    else if (y >= x && y >= z) { a1 = y; b1 = (x >= z ? x : z); c1 = (x >= z ? z : x); }
    else { a1 = z; b1 = (x >= y ? x : y); c1 = (x >= y ? y : x); }
    cout << a1 * 100 + b1 * 10 + c1 << "\n";

    // 6. Дано трехзначное число. Если вторая цифра делится на 3 — разделить её на 3, иначе заменить её нулём.
    cin >> n;
    x = n / 100;
    y = (n / 10) % 10;
    z = n % 10;
    if (y % 3 == 0) y = y / 3;
    else y = 0;
    cout << x << y << z << "\n";

    return 0;
}