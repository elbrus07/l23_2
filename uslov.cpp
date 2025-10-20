#include <iostream>
#include <cmath>

int main(){
  //1. Пользователь вводит три числа. Программа выводит максимальное из них.
  
  /*
  double a, b, c, max;
  std::cout<<"Введите три числа:";
  std::cin>>a>>b>>c;
  if (a>=b && a>=c) {
      max = a;
  } else if (b>=c){
      max = b;
  } else {
      max = c;
  }
  std::cout<<"Максимальное число: "<<max<<std::endl;
  */
  
  //2. Пользователь вводит три числа. Если среди чисел нет нуля, то вычислить произведение, иначе вычислить сумму этих чисел.
  
  /*
  double a, b, c, res;
  std::cout<<"Введите три числа:";
  std::cin>>a>>b>>c;
  if (a!=0 && b!=0 && c!=0) {
      res = a*b*c;
      std::cout<<"Произведение: "<<res<<std::endl;
  } else {
      res = a+b+c;
      std::cout<<"Сумма: "<<res<<std::endl;
  }
  */
  
  //3. Пользователь вводит три числа. Вывести их в порядке возрастания.
  
  /*
  double a, b, c, first, second, third;
  std::cout << "Введите три числа: ";
  std::cin >> a >> b >> c;
  if (a <= b && a <= c) {
    first = a;
    if (b <= c) {
      second = b;
      third = c;
    } else {
      second = c;
      third = b;
    }
  } else if (b <= a && b <= c) {
    first = b;
    if (a <= c) {
      second = a;
      third = c;
    } else {
      second = c;
      third = a;
    }
  } else {
    first = c;
    if (a <= b) {
      second = a;
      third = b;
    } else {
      second = b;
      third = a;
    }
  }
  std::cout << "Числа в порядке возрастания: " << first << " " << second << " " << third << std::endl;  
  */
  
  //4. Пользователь вводит 3 числа. Программа должна проверить могут ли эти числа являться длинами сторон треугольника. Если да, то вычислить площадь треугольника, если нет, то вывести сумму этих чисел
  
  /*
  double a, b, c, res;
  std::cout<<"Введите три числа: ";
  std::cin>>a>>b>>c;
  if (a+b>c && b+c>a && a+c>b) {
      double p = (a + b + c)/2 ;
      res = pow((p * (p - a) * (p - b) * (p - c)),0.5);
      std::cout<<"Площадь треугольника :"<< res << std::endl;;    
  
  } else{
      res = a + b + c;
      std::cout<<"Сумма чисел:" << res << std::endl;;
  }
  */
  
  //5. Пользователь вводит три числа – коэффициенты квадратного уравнения. Программа вычисляет корни уравнения
  

  double a, b, c, d;
  std::cout << "Введите коэффициенты квадратного уравнения (a, b, c), где a ≠ 0: ";
  std::cin >> a >> b >> c;
  d = b * b - 4 * a * c;
  if (d > 0) {
    double root1 = (-b + sqrt(d)) / (2 * a);
    double root2 = (-b - sqrt(d)) / (2 * a);
    std::cout << "Два корня: " << root1 << " и " << root2 << std::endl;
  } else if (d == 0) {
    double root = -b / (2 * a);
    std::cout << "Один корень: " << root << std::endl;
  } else {
      std::cout << "Корней нет." << std::endl;
  }

  
  //6. Пользователь вводит координаты точки на плоскости (x,y). Определить в какой четверти или на какой оси декартовой плоскости находится точка
  
  /*
  double x, y;
  std::cout << "Введите координаты точки на плоскости (x, y): ";
  std::cin >> x >> y;
  if (x == 0 && y == 0) {
    std::cout << "Точка находится в начале координат." << std::endl;
  } else if (x == 0) {
    std::cout << "Точка находится на оси Y." << std::endl;
  } else if (y == 0) {
    std::cout << "Точка находится на оси X." << std::endl;
  } else if (x > 0 && y > 0) {
    std::cout << "Точка находится в первой четверти." << std::endl;
  } else if (x < 0 && y > 0) {
    std::cout << "Точка находится во второй четверти." << std::endl;
  } else if (x < 0 && y < 0) {
    std::cout << "Точка находится в третьей четверти." << std::endl;
  } else if (x > 0 && y < 0) {
    std::cout << "Точка находится в четвертой четверти." << std::endl;
  }
  */
  
  //7. Написать программу, проверяющую является ли введённое пользователем число целым или дробным
  
  /*
  double a;
  std::cout << "Введите число: ";
  std::cin >> a;
  if ((int)a == a) {
      std::cout << "Введённое число является целым." << std::endl;
  } else {
      std::cout << "Введённое число является дробным." << std::endl;
  }
  */
  
  //8. Вычислить выражение sqrt(x-sqrt(y+1)). Значения x и y вводит пользователь. Перед вычислением выполнить проверку на существование квадратных корней.
  
  /*
  double x, y, res;
  std::cout << "Введите x и y: ";
  std::cin >> x >> y;
  if (y + 1 >= 0 && x - sqrt(y + 1) >= 0) {
    res = sqrt(x - sqrt(y + 1));
    std::cout << "Результат: " << res << std::endl;
  } else {
    std::cout << "Невозможно вычислить." << std::endl;
  }
  */
  
  //9. Дано пятизначное число. Занулить цифры, стоящие на четных разрядах. Например, из 123456 получается число 103050. Нумерация разрядов начинается справа.
  
  /*
  int number, res;
  std::cout << "Введите пятизначное число: ";
  std::cin >> number;
  int units = number % 10;
  int tens = 0;           
  int hundreds = (number / 100) % 10;
  int thousands = 0;
  int ten_thousands = number / 10000;
  res = ten_thousands * 10000 + thousands * 1000 + hundreds * 100 + tens * 10 + units;
  std::cout << "Результат: " << res << std::endl;
  */
   
  return 0;
}
