#include <iostream>
#include <cmath>
using namespace std;

// 1. Определить периметр треугольника, заданного координатами вершин.
// Длину стороны треугольника вычислять в функции. 
// Посчитать среднее арифметическое периметров трех треугольников, 
// координаты которых ввести с клавиатуры.

double storona(double x1, double y1, double x2, double y2) {
    double dlinastorony;
    dlinastorony = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
    return dlinastorony;
}

void zadacha1() {
    double summa = 0;
    
    for(int i = 0; i < 3; i++) {
        cout << "Треугольник " << i+1 << endl;
        double x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        
        double AB = storona(x1, y1, x2, y2);
        double BC = storona(x2, y2, x3, y3);
        double CA = storona(x3, y3, x1, y1);
        
        double perimetr = AB + BC + CA;
        cout << "Периметр: " << perimetr << endl;
        
        summa = summa + perimetr;
    }
    
    double srednee = summa / 3.0;
    cout << "Среднее: " << srednee << endl;
}

// 2. Написать функцию для сортировки массива.
// Выбор метода сортировки осуществляется путем передачи соответствующего параметра.

void puzir(int massiv[], int razmer) {
    for(int i = 0; i < razmer-1; i++) {
        for(int j = 0; j < razmer-i-1; j++) {
            if(massiv[j] > massiv[j+1]) {
                int temp = massiv[j];
                massiv[j] = massiv[j+1];
                massiv[j+1] = temp;
            }
        }
    }
}

void vstavki(int massiv[], int razmer) {
    for(int i = 1; i < razmer; i++) {
        int tekuwii = massiv[i];
        int j = i-1;
        
        while(j >= 0 && massiv[j] > tekuwii) {
            massiv[j+1] = massiv[j];
            j--;
        }
        massiv[j+1] = tekuwii;
    }
}

void sortirovka(int massiv[], int razmer, int metod) {
    if(metod == 1) {
        puzir(massiv, razmer);
    }
    else if(metod == 2) {
        vstavki(massiv, razmer);
    }
}

void zadacha2() {
    int chisla[] = {7, 3, 9, 1, 5, 2, 8, 4, 6};
    int n = 9;
    
    cout << "Массив до: ";
    for(int i = 0; i < n; i++) {
        cout << chisla[i] << " ";
    }
    cout << endl;
    
    int vibor;
    cout << "Выберите 1 (пузырек) или 2 (вставки): ";
    cin >> vibor;
    
    sortirovka(chisla, n, vibor);
    
    cout << "Массив после: ";
    for(int i = 0; i < n; i++) {
        cout << chisla[i] << " ";
    }
    cout << endl;
}

// 3. Написать функцию табуляции функции f(x) = sqrt(x - 1) 
// в точках x = 1,2,3,..., 12.

void zadacha3() {
    for(int x = 1; x <= 12; x++) {
        double fx;
        if(x-1 >= 0) {
            fx = sqrt(x-1);
            cout << "x=" << x << " f(x)=" << fx << endl;
        }
        else {
            cout << "x=" << x << " не определено" << endl;
        }
    }
}

// 4. Написать функцию, вычисляющую количество совпадений числа x 
// с элементами числового массива

int sovpadeniya(int x, int massiv[], int razmer) {
    int schetchik = 0;
    for(int i = 0; i < razmer; i++) {
        if(massiv[i] == x) {
            schetchik++;
        }
    }
    return schetchik;
}

void zadacha4() {
    int spisok[] = {3, 7, 2, 3, 8, 3, 5, 7, 3, 1, 4, 3, 6};
    int n = 13;
    
    cout << "Массив: ";
    for(int i = 0; i < n; i++) {
        cout << spisok[i] << " ";
    }
    cout << endl;
    
    int iskomoe;
    cout << "Введите число: ";
    cin >> iskomoe;
    
    int kolvo = sovpadeniya(iskomoe, spisok, n);
    cout << "Совпадений: " << kolvo << endl;
}

int main() {
    zadacha1();
    zadacha2();
    zadacha3();
    zadacha4();
    
    return 0;
}
