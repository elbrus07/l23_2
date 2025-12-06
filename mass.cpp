#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;
int main(){
    //1. Организовать ввод элементов массива с клавиатуры. Размер массива также должен задаваться пользователем. Введённый массив вывести на экран.
    
    /*
    int n;
    cout << "Введите размер массива: "; 	
    cin >> n;

    int massiv[n];
    for (int i = 0; i < n; i++){	    
        cout<<"Введите "<<i+1<<"-й элемент массива: ";
        cin >> massiv[i];
    }

    for(int i = 0; i < n; i++){
	    cout << massiv[i] <<" ";
    }
    cout << '\n';
    */
    
    //2. Создать массив случайного размера, состоящий из случайных целых чисел в заданном диапазоне.
    
    /*
    srand(time(NULL)); // Инициализация генератора
    int a, b, c, d;
    cout<<"Введите диапазон массива (a, b): ";
    cin >> a >> b;
    int n = rand()%(b-a+1) + a; // Получение случайного числа
    int m[n];
    
    cout<<"Введите диапазон чисел массива (c, d): ";
    cin >> c >> d;
    for (int i = 0; i < n; i++){
        m[i] = rand()%(d-c+1) + c;
        cout << m[i] <<" ";
    }
    cout <<"\n";
    */
    
    //3. Заполнить массив случайным образом нулями и единицами так, чтобы количество единиц было в точности равно количеству нулей.
    
    //4. Дан массив A из 2n элементов. Вычислить A1−A2 + A3−A4 + … +A2n−1 + A2n.
    
    /*
    srand(time(NULL));
    int a, b, n;
    cout<<"Введите размер массива 2n: ";
    cin >> n;
    int size = 2*n;
    int A[size];
    
    cout<<"Введите диапазон чисел массива (a, b): ";
    cin >> a >> b;
    for (int i = 0; i < size; i++){
        A[i] = rand()%(b-a+1) + a;
        cout << A[i] <<" ";
    }
    cout <<"\n";
    
    int sum = 0;

    for (int i = 0; i < size; i+= 2){
        sum += A[i] - A[i+1];
    }
    cout << "A1−A2 + A3−A4 + … +A2n−1 + A2n = "<< sum << endl;
    */
    
    //5. Дан массив и число p. Найти два различных числа в массиве, сумма которых наиболее близка к p.
    
    /*
    srand(time(NULL));
    
    int p, n1, n2;
    p = 3;
    int m[5] = {2, 5, 4, 3, 8};
    int min_dif = m[0] + m[1]; 

    for (int i = 0; i < 5; i++){
        for (int j = i + 1; j < 5-1; j++){
            int sum = m[i] + m[j];
            int dif = abs(sum - p);  
            
            if (dif < min_dif) {
                min_dif = dif;
                n1 = m[i];
                n2 = m[j];
            }
        }
    }
    cout << "Пара слагаемых: " << n1 << " + " << n2 << " = " << n1 + n2 << endl;
    */
    
    //6. Дан массив чисел. Заменить каждый элемент с чётным индексом на соседний слева элемент.
    
    /*
    int m[5] = {2, 5, 4, 3, 8};
    for(int i = 2; i < 5; i+=2){
        m[i] = m[i-1];
    }
    for(int i = 0; i < 5; i++){
	    cout << m[i] <<" ";
    }
    cout << '\n';
    */
    
    //7. Дан массив. Поменять местами наибольший и наименьший элементы массива.
    
    /*
    int m[5] = {2, 5, 4, 3, 8};
    int maxInd = 0;
    int minInd = 0;

    for (int i = 1; i < 5; i++) {
        if (m[i] > m[maxInd]) {
            maxInd = i;
        }
        if (m[i] < m[minInd]) {
            minInd = i;
        }
    }

    int temp = m[maxInd];
    m[maxInd] = m[minInd];
    m[minInd] = temp;
    
    for(int i = 0; i < 5; i++){
	cout << m[i] <<" ";
    }
    cout << '\n';
    */
    
    //8. Даны два массива. Сформировать третий массив, состоящий из тех элементов, которые присутствуют в обоих массивах    
    

    
   
    return 0;
}
