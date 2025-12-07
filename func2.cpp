#include <iostream>
#include <cmath>
using namespace std;

//1. Определить периметр треугольника, заданного координатами вершин. Длину стороны треугольника вычислять в функции. Посчитать среднее арифметическое периметров трех треугольников, координаты которых ввести с клавиатуры.

double dist(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

double trianglePerimeter(double x1, double y1, double x2, double y2, double x3, double y3) {
    double a = dist(x1, y1, x2, y2);
    double b = dist(x2, y2, x3, y3);
    double c = dist(x3, y3, x1, y1);
    return a + b + c;
}

//2. Написать функцию для сортировки массива.

// Функция для обмена элементов
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void bubble_sort(int a[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void insertion_sort(int a[], int size) {
    for (int i = 1; i < size; i++) {
        int key = a[i];
        int j = i - 1;
        
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void selection_sort(int a[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (a[j] < a[min_idx]) {
                min_idx = j;
            }
        }
        swap(a[i], a[min_idx]);
    }
}

// Функция для выбора метода сортировки
int sort(int a[], int size, int method) {
    /*
	method - метод сортировки:
	1 - сортировка пузырьком
	    сравнивает соседние элементы и меняет их местами при необходимости
	2 - сортировка вставками
	    вставляет каждый элемент в правильную позицию в уже отсортированной части массива
	3 - сортировка выбором
	    находит минимальный элемент и помещает его в начало
    */
    if (method == 1) {
        bubble_sort(a, size);
    } else if (method == 2) {
        insertion_sort(a, size);
    } else if (method == 3) {
        selection_sort(a, size);
    }
    return 0;
}


//3. Написать функцию табуляции функции f(x)=(x-1)^0.5 в точках x = 1,2,3,..., 12.\

double f(double x) {
    return sqrt(x - 1);
}

void tabulateFunction() {
    cout << "x\tf(x) = sqrt(x-1)" << endl;
    cout << "-------------------------" << endl;
    
    for (int i = 1; i <= 12; i++) {
        double result = f(i);
        cout << i << "\t" << result << endl;
    }
}

    

//4. Написать функцию вычисляющую количество совпадений числа x с элементами числового массива

int count_num(int x, int m[], int size) {
    int count = 0;
    for(int i = 0; i < size; i++){
        if (m[i] == x){
            count++;
        }
    }
    return count;
}
    
int main(){
    //задание 1
    /*
    double perimeters[3];
    double sum = 0;
    
    cout << "Введите координаты вершин трех треугольников:" << endl;
    
    for (int i = 0; i < 3; i++) {
        cout << "\nТреугольник " << i + 1 << ":" << endl;
        
        double x1, y1, x2, y2, x3, y3;
        
        cout << "Вершина 1 (x y): ";
        cin >> x1 >> y1;
        
        cout << "Вершина 2 (x y): ";
        cin >> x2 >> y2;
        
        cout << "Вершина 3 (x y): ";
        cin >> x3 >> y3;
        
        // Вычисляем периметр и сохраняем его
        perimeters[i] = trianglePerimeter(x1, y1, x2, y2, x3, y3);
        sum += perimeters[i];
        
        cout << "Периметр треугольника " << i + 1 << ": " << perimeters[i] << endl;
    }
    
    double average = sum / 3;
    
    cout << "\nРезультаты:" << endl;
    cout << "Среднее арифметическое периметров: " << average << endl;
    */
    
    //задание 2
    
    int m[] = {6, 34, 5, 12, 2, 11, 9, 8, 76, 0};
    int size = sizeof(m) / sizeof(m[0]);
    
    cout << "Исходный массив: "<<endl;
    for(int i = 0; i < size; i++){
	    cout << m[i] <<" ";
    }
    cout << '\n';
    
    cout << "Сортировка: "<<endl;
    sort(m, size, 2);
    for(int i = 0; i < size; i++){
	    cout << m[i] <<" ";
    }
    cout << '\n';

    //задание 3
    //tabulateFunction();
    
    //задание 4
    /*
    int x = 4;
    int m[] = {5, 7, 4, 5, 4, 9, 4};
    int size = sizeof(m) / sizeof(m[0]);
    cout<<count_num(x, m, size)<<endl;
    */
    
    return 0;
}
