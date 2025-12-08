#include <iostream>
#include <cmath>
#include <array>
using namespace std;

//1. Определить периметр треугольника, заданного координатами вершин. Длину стороны треугольника вычислять в функции.
//Посчитать среднее арифметическое периметров трех треугольников, координаты которых ввести с клавиатуры.

double metrika(double x1,double y1,double x2,double y2){
    return pow(pow(x1 - x2, 2) + pow(y1 - y2, 2),0.5);
}
double triangle(double x1,double y1,double x2,double y2,double x3,double y3){
    if((y1 - y2)/(x1 - x2) != (y3 - y2)/(x3 - x2))
        return metrika(x1, y1, x2, y2) + metrika(x1, y1, x3, y3) + metrika(x3, y3, x2, y2);
    else
        return 0;
}

//4. Написать функцию вычисляющую количество совпадений числа x с элементами числового массива
int sovpad(int x, int mas[]){
    int n = 0;
    int i = 0;
    int d = 500;
    while (mas[i]){ 
        if(x == mas[i])
            n++;
        i++; }   
    return n;}

//3. Написать функцию табуляции функции f(x) = (x - 1)**0.5 в точках x = 1,2,3,..., 12.
double tabl(double start,double end,double step){
    cout<< "[X]" << "[Y]" <<endl;
    for (double x = start; x <= end; x += step){
        double y = pow(x - 1, 0.5);
        cout<< "[" << x << "]" << "[" << y << "]" <<endl;}
    return 0;
}

//2. Написать функцию для сортировки массива методом пузырька.
int sort(string sort, int arr[], int n){
    int new_arr[n];
    for(int i; i<n; i++){
        new_arr[i] = arr[i];
    }


    if(sort == "bubble"){
        for (int i = 0; i < n-1; i++){
            for(int j = 0; j < n-1-i; j++){
                if(arr[j] > arr[j+1])
                    arr[j], arr[j+1] = new_arr[j+1], new_arr[j]; 
                }
            }
        }

    for(int i = 0; i<n; i++){
        cout<< new_arr[i];
    }
    return 0;
}


int main(){
    int r[6]{2,4,1,3,6,5};
    sort("bubble", r, 6);
    return 0;
}
