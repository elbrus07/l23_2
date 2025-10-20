
// 1. Пользователь вводит сторону квадрата. Найти периметр и площадь квадрата.
#include <iostream>
using namespace std;
int main() {
    double storona;
    cin >> storona;
    cout << "Perimetr: " << 4 * storona << endl;
    cout << "Ploshad: " << storona * storona << endl;
    return 0;
}

// 2. Пользователь вводит время в минутах и расстояние в километрах. Найдите скорость в м/c.
#include <iostream>
using namespace std;
int main() {
    double min, km;
    cin >> min >> km;
    double skorost = (km * 1000) / (min * 60);
    cout << "Skorost (m/s): " << skorost << endl;
    return 0;
}

// 3. Даны катеты прямоугольного треугольника. Найдите площадь, периметр и гипотенузу треугольника.
#include <iostream>
#include <cmath>
using namespace std;
int main() {
    double katet1, katet2;
    cin >> katet1 >> katet2;
    double gip = sqrt(katet1 * katet1 + katet2 * katet2);
    cout << "Ploshad: " << (katet1 * katet2) / 2 << endl;
    cout << "Perimetr: " << katet1 + katet2 + gip << endl;
    cout << "Gipotenuza: " << gip << endl;
    return 0;
}

// 4. Дано значение температуры в градусах Цельсия. Вывести температуру в градусах Фаренгейта.
#include <iostream>
using namespace std;
int main() {
    double cels;
    cin >> cels;
    cout << "Farengeit: " << cels * 9 / 5 + 32 << endl;
    return 0;
}

// 5. Известно, что x кг конфет стоит a рублей. Определите, сколько стоит y кг этих конфет, а также сколько кг конфет можно купить на k рублей.
#include <iostream>
using namespace std;
int main() {
    double kg, rub, skolkoKg, skolkoRub;
    cin >> kg >> rub >> skolkoKg >> skolkoRub;
    double cenaZaKg = rub / kg;
    cout << "Stoimost y kg: " << cenaZaKg * skolkoKg << endl;
    cout << "Kg za k rub: " << skolkoRub / cenaZaKg << endl;
    return 0;
}

// 6. Пользователь вводит количество недель, месяцев, лет и получает количество дней за это время (в месяце 30 дней).
#include <iostream>
using namespace std;
int main() {
    int ned, mes, god;
    cin >> ned >> mes >> god;
    int dni = ned * 7 + mes * 30 + god * 365;
    cout << "Vsego dnei: " << dni << endl;
    return 0;
}

// 7. Булочка стоит R рублей и K копеек. Определите, сколько рублей и копеек нужно заплатить за N булочек.
#include <iostream>
using namespace std;
int main() {
    int rub, kop, skolko;
    cin >> rub >> kop >> skolko;
    int vseKop = (rub * 100 + kop) * skolko;
    cout << "Itogo: " << vseKop / 100 << " rub " << vseKop % 100 << " kop" << endl;
    return 0;
}

// 8. В школе решили набрать три класса и оборудовать кабинеты новыми партами. За каждой партой может сидеть два учащихся.
#include <iostream>
using namespace std;
int main() {
    int kl1, kl2, kl3;
    cin >> kl1 >> kl2 >> kl3;
    int party = (kl1 + 1) / 2 + (kl2 + 1) / 2 + (kl3 + 1) / 2;
    cout << "Nado part: " << party << endl;
    return 0;
}

// 9. Дано натуральное число N. Выведите следующее за ним чётное число.
#include <iostream>
using namespace std;
int main() {
    int chislo;
    cin >> chislo;
    cout << chislo + 2 - chislo % 2 << endl;
    return 0;
}

// 10. Дано целое неотрицательное число N, определите число десятков в нем (предпоследнюю цифру числа).
// Если предпоследней цифры нет, то можно считать, что число десятков равно нулю.
#include <iostream>
using namespace std;
int main() {
    int chislo;
    cin >> chislo;
    int desyatki = (chislo / 10) % 10;
    cout << "Desyatki: " << desyatki << endl;
    return 0;
}

// 11. Найти уравнение прямой, проходящей через две заданные пользователем точки (x1, y1) и (x2, y2).
// Уравнение в виде y = kx + b. Найти коэффициенты k и b.
#include <iostream>
using namespace std;
int main() {
    double x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    double k = (y2 - y1) / (x2 - x1);
    double b = y1 - k * x1;
    cout << "k = " << k << ", b = " << b << endl;
    cout << "Uravnenie: y = " << k << "x + " << b << endl;
    return 0;
}
