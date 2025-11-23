#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

int main(){
//1.Организовать ввод элементов массива с клавиатуры. Размер массива также должен задаваться пользователем. Введённый массив вывести на экран.
/*
    int n;
    cout << "Введите размер массива";
    cin >> n;

    int massiv[n];

    for (int i =0 ; i<n ; i++){
        cout << "Введите"<<i<<"-ый элемент массива";
        cin >> massiv[i];
    }

    for(int i = 0; i < n; i++){
		cout << massiv[i] <<" ";
	}
*/

//2.Создать массив случайного размера, состоящий из случайных целых чисел в заданном диапазоне.
/*
    srand(time(0));  // генератор
    
    int a, b;
    cout << "Введите диапазон значений (a b): ";
    cin >> a >> b;
    
    // Случайный размер от 5 до 15
    int k = rand() % 11 + 5;
    int massiv[k];
    
    cout << "Создан массив из " << k << " элементов:" << endl;
    
    for(int i = 0; i < k; i++) {
        massiv[i] = rand() % (b - a + 1) + a;
        cout << massiv[i] << " ";
    }
*/    
//3.    Заполнить массив случайным образом нулями и единицами так, чтобы количество единиц было в точности равно количеству нулей 
/*    
    srand(time(0));
    int n, count1 = 0, count0 = 0;

    cout << "Введите размер массива, Размер должен быть четным";
    cin >> n;

    while (n % 2 != 0)
    {
        cout << "Вы ввели нечетный размер. Введите ЧЕТНЫЙ размер: ";
        cin >> n;
    }

    int massiv[n];

    for (int i = 0; i < n ; i++) { 
        if (count1 == n/2  ) {
            massiv[i] = 0;
            count0 += 1;
        } else if (count0 == n/2 ) {
            massiv[i] = 1;
            count1 += 1;
        }else {
            massiv[i] = rand() % 2;
            if (massiv[i] == 1){
                count1 += 1;
            } else {
                count0 += 1;
            }
        }
        
    }    

    cout << "Массив: ";
    for (int i = 0; i < n; i++) {
        cout << massiv[i] << " ";
    }
*/

//4. Дан массив A из 2n элементов. Вычислить A1−A2 + A3−A4 + … +A2n−1 + A2n
/*
    srand(time(0));
    int n;

    cout << "Введите n";
    cin >> n;
    
    int size= 2*n;
    int A[size];

    for (int i = 0; i < size; i++) {
        A[i] = rand() % 100;
    }

    int sum = 0;

    for (int i = 0; i < size; i+= 2)
    {
        sum += A[i] - A[i+1];
    }
    cout << "Сумма = "<< sum ;
*/

//5.Дан массив и число p. Найти два различных числа в массиве, сумма которых наиболее близка к p.
	
    return 0;

}
