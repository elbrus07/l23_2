#include <iostream>
#include <cmath>
int main(){
/*
    //1. Пользователь вводит три числа. Программа выводит максимальное из них.
    double a;    
    double b;
    double c;
    double d;
    std::cin>> a;
    std::cin>> b;
    std::cin>> c;


    if (b>a && b>c)
        d = b;
    else if (c>b && c>a)
        d = c;
    else if (a>c && a>b)
        d = a;
    
    std::cout<<d;
*/
/*
    //2. Пользователь вводит три числа. Если среди чисел нет нуля, то вычислить 
    //произведение, иначе вычислить сумму этих чисел.

    double a;    
    double b;
    double c;

    std::cin>> a;
    std::cin>> b;
    std::cin>> c;

    if (a!=0 && b!=0 && c!=0)
        std::cout<< a*b*c;

    else
        std::cout<< a+b+c;

*/
/*
    //3. Пользователь вводит три числа. Вывести их в порядке возрастания.
    double a;    
    double b;
    double c;
    std::cin>> a;
    std::cin>> b;
    std::cin>> c;
    if (a>=b && b>=c)
        std::cout<< a << b<< c;
    else if (a>=c && c>=b)
        std::cout<< a << ", " << c << ", " << b;
    else if (b>=a && a>=c)
        std::cout<< b << ", " << a << ", " << c;
    else if (b>=c && c>=a)
        std::cout<< b << ", " << c << ", " << a;
    else if (c>=a && a>=b)
        std::cout<< c << ", " << a << ", " << b;
    else if (c>=b && b>=a)
        std::cout<< c << ", " << b << ", " << a; 
*/   
/*
 //5. Пользователь вводит три числа – коэффициенты квадратного уравнения. Программа вычисляет корни уравнения

    double a;    
    double b;
    double c;
    std::cin>> a;
    std::cin>> b;
    std::cin>> c;
     
    if (b*b - 4*a*c >= 0)
        std::cout<< (-1*b - pow(b*b - 4*a*c, 0.5))/2*a;
        std::cout<< (-1*b + pow(b*b - 4*a*c, 0.5))/2*a;
*/
/*
    //6. Пользователь вводит координаты точки на плоскости (x,y). Определить в какой четверти или на какой оси декартовой плоскости находится точка
    double x;    
    double y;
    std::cin>> x;
    std::cin>> y;

    if (x>0 && y>0)
    std::cout << "I";
    if (x>0 && y<0)
    std::cout << "II";
    if (x<0 && y<0)
    std::cout << "III";
    if (x<0 && y>0)
    std::cout << "IIII";
*/

    //7. Написать программу, проверяющую является ли введённое пользователем число
    //целым или дробным


/*
//8. Вычислить выражение √𝑥 − √𝑦 + 1. Значения x и y вводит пользователь. Перед
//вычислением выполнить проверку на существование квадратных корней.
    double x;    
    double y;
    std::cin>> x;
    std::cin>> y;

    if (y >= -1 && x >= pow(y-1,0.5))
        std::cout<< pow(x - pow(y+1,0.5),0.5);
    else
        std::cout<< "none";
*/
/*
//9. Дано пятизначное число. Занулить цифры, стоящие на четных разрядах. Например, из
//123456 получается число 103050. Нумерация разрядов начинается справа.
    int x;
    std::cin>>x;
    
    int x1 = x % 10;
    int x2 = x % 100;
    int x3 = x % 1000;
    int x4 = x % 10000;
    
    int d_x = x2 - x1;
    int t_x = x4 - x3;

    std::cout<< x - t_x - d_x;
*/

    return 0;
}
