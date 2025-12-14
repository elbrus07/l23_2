#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
using namespace std;

//1. Определить периметр треугольника, заданного координатами вершин. Длину стороны треугольника вычислять в функции. Посчитать среднее арифметическое периметров трех треугольников, координаты которых ввести с клавиатуры.

double dlin_st (double x1,double y1 , double x2 , double y2) {
    return sqrt((x2-x1) * (x2-x1) + (y2 - y1) * (y2 - y1) ) ;
}

double triangl_per ( double x1, double y1, double x2, double y2, double x3, double y3 ) {
    double a, b, c ;
    a = dlin_st(x1, y1, x2, y2);
    b = dlin_st(x2, y2, x3, y3);
    c = dlin_st(x3, y3, x1, y1);
    return a + b + c;
}



//2. Написать функцию для сортировки массива методом пузырька.

//сортировка пузырьком
//n - длина масива
void bubbleSort(int masiv[], int n) {    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (masiv[j] > masiv[j + 1]) {
                swap(masiv[j], masiv[j + 1]);  
            }
        }
    }
}

//сортировка выбором
void selectSort (int masiv[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        
        // находим минимальный элемент 
        for (int j = i + 1; j < n; j++) {
            if (masiv[j] < masiv[minIndex]) {
                minIndex = j;
            }
        }
        
        
        if (minIndex != i) {
            swap(masiv[i], masiv[minIndex]);
        }
    }
   
}

//сортировка вставками
void insertionSort ( int masiv[], int n) {
    for (int i = 1; i < n; i++) {
        int j = i;
        
        // Поднимаем элемент вверх, пока он меньше предыдущего
        while (j > 0 && masiv[j] < masiv[j - 1]) {
            swap(masiv[j], masiv[j - 1]);
            j--;
        }
    }
  
}

int sort(int masiv[], int size, int method) {
    /*
	Если в method написать 1 , то выполнится сортировка пузырьком
    Если в method написать 2 , то выполнится сортировка вставками
    Если в method написать 3 , то выполнится сортировка выбором
    */
    if (method == 1) {
        bubbleSort(masiv, size);
    } else if (method == 2) {
        insertionSort(masiv, size);
    } else if (method == 3) {
        selectSort(masiv, size);
    } else {
        cout << "Неверный метод сортировки!" << endl;
    }
}
//3. Написать функцию табуляции функции f(x)=√(x-1) в точках x = 1,2,3,..., 12.\


//4. Написать функцию вычисляющую количество совпадений числа xс элементами числового массива
int Poisc_sovpad(int masiv[], int n, int x) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (masiv[i] == x) {
            count++;
        }
    }
    return count;
}




int main(){
    //№1
    const int colvo_triangls = 3;
    int triangl_perim[colvo_triangls];
    int sum;

    cout << "Введите координаты треугольников:" << endl;
    
    for ( int i =0; i < colvo_triangls; i++) {
        double x1, y1, x2, y2, x3, y3 ;
        cout << "Введите координаты вершин : x1 y1 x2 y2 x3 y3";
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;


        triangl_perim[i] = triangl_per(x1, y1, x2, y2, x3, y3);
        sum += triangl_perim[i];

    }

    for ( int i =0 ; i < colvo_triangls; i++ ) {
         cout << "Периметр треугольника " << (i + 1) << ": " << triangl_perim[i] << endl;
    }

    double average = sum / colvo_triangls;
    cout << "Среднее арифметическое периметров: " << average << endl;


    //№2
    int m[] = {17, 15, 2, 12, 3, 11, 56, 8, 22, 0};
    int size = sizeof(m) / sizeof(m[0]);
    
    cout << "Исходный массив: "<<endl;
    for(int i = 0; i < size; i++){
	    cout << m[i] <<" ";
    }
    cout << '\n';
    
    cout << "Сортировка: "<<endl;
    sort(m, size, 1);
    for(int i = 0; i < size; i++){
	    cout << m[i] <<" ";
    }

    //№4
    srand(time(0));
    
    int n, x;   // n -размер массива; x -число для поиска
    n = 6 ;
    x= 2;
    
    int masiv[6];
    
    cout << "Массив: ";
    for (int i = 0; i < n; i++) {
        masiv[i] = rand() % 10;  // числа от 0 до 9
        cout << masiv[i] << " ";
    }
    cout << endl;
    
    int counter = Poisc_sovpad(masiv, n, x);
    cout << "Число " << x << " встречается -" << counter << "раз" << endl;
    
    return 0;
}