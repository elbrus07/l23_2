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
    int k = rand() % (15 - 5) + 5;
    int massiv[k];
    

    cout << "Создан массив из " << k << " элементов:" << endl;
    
    for(int i = 0; i < k; i++) {
        massiv[i] = rand() % (b - a + 1) + a;
        cout << massiv[i] << " ";
    }
    cout<<"\n";
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
/*    
    srand(time(0));
    
    int n, p, num1, num2;
    cout << "Введите размер массива: ";
    cin >> n;
    cout << "Введите число p: ";
    cin >> p;
    
    int massiv[n];

    for (int i = 0; i < n; i++) {
        massiv[i] = rand() % 100;
    }

    int minDiff = INT_MAX; 

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
        for (int j = i + 1; j < n-1; j++) {
            int sum = massiv[i] + massiv[j];
            int diff = abs(sum - p);  
            
            if (diff < minDiff) {
                minDiff = diff;
                num1 = massiv[i];
                num2 = massiv[j];
            }
        }
    cout << "Найденная пара: " << num1 << " и " << num2 << endl;
    cout << "Их сумма: " << num1 + num2 << endl;
*/

//6.Дан массив чисел. Заменить каждый элемент с чётным индексом на соседний слева элемент.
/*
    srand(time(0));
    
    int n;
    cout << "Введите размер массива: ";
    cin >> n;

    int massiv[n];

    cout << "Исходный массив: " ;
    for (int i = 0; i < n; i++) {
        massiv[i] = rand() % 100;
        cout << massiv[i] << " "<< endl;
    }

    for(int i = 0; i < n; i++){

        if (i % 2 == 0) {
            if ( i> 0) {
                massiv[i] = massiv[i - 1];
            }   
        }
    for(int i = 2; i < n; i+=2){
       massiv[i] = massiv[i - 1];
    }
		
	}
    cout << "Результат: ";
    for (int i = 0; i < n; i++) {
        cout << massiv[i] << " ";
    }
*/

//7.Дан массив. Поменять местами наибольший и наименьший элементы массива.
/*
    srand(time(0));
    
    int n;
    cout << "Введите размер массива: ";
    cin >> n;

    int massiv[n];

    cout << "Исходный массив: " ;
    for (int i = 0; i < n; i++) {
        massiv[i] = rand() % 100;
        cout << massiv[i] << " "<< endl;
    }

    int max_cifr =  massiv[0];
    int min_cifr = massiv[0];
    int maxi = 0;
    int mini = 0;

    for(int i = 0; i < n; i++){


       if (massiv[i] > max_cifr) {  
            max_cifr = massiv[i];
            maxi = i;
        }
        if (massiv[i] < min_cifr) { 
            min_cifr = massiv[i];
            mini = i;
        }

	}

    massiv[maxi] = min_cifr;
    massiv[mini] = max_cifr;

    cout << "Результат: ";
    for (int i = 0; i < n; i++) {
        cout << massiv[i] << " ";
    }
*/

//8.Даны два массива. Сформировать третий массив, состоящий из тех элементов, которые присутствуют в обоих массивах
    /*
    int massiv1[5] = {1,4,6,2,7};
    int massiv2[5] = {8,5,3,2,7};
    int massiv3[5] = {0};  
    
    int count = 0;  
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (massiv1[i] == massiv2[j]) {
                massiv3[count] = massiv1[i];  
                count++;
                break;
            }
        }
    }
    
    cout << "общие элементы: ";
    for (int i = 0; i < count; i++) {
        cout << massiv3[i] << " ";
    }
    
*/ 
	return 0;

}

