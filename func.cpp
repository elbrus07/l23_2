#include <iostream>
#include <cmath>

using namespace std;

// 1. Периметр треугольника
double dlina(double x1, double y1, double x2, double y2) {
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

void zadanie1() {
    double sum = 0;
    
    for (int i = 0; i < 3; i++) {
        double x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        
        double a = dlina(x1, y1, x2, y2);
        double b = dlina(x2, y2, x3, y3);
        double c = dlina(x3, y3, x1, y1);
        double p = a + b + c;
        
        sum += p;
    }
    
    cout << sum / 3 << endl;
}

// 2. Сортировка пузырьком
void sortirovka(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void zadanie2() {
    int n;
    cin >> n;
    
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    sortirovka(arr, n);
    
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// 3. Табуляция функции
void zadanie3() {
    for (int x = 1; x <= 12; x++) {
        cout << sqrt(x-1) << endl;
    }
}

// 4. Количество совпадений
int skolko(int arr[], int n, int x) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            count++;
        }
    }
    return count;
}

void zadanie4() {
    int n;
    cin >> n;
    
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    int x;
    cin >> x;
    
    cout << skolko(arr, n, x) << endl;
}

int main() {
    //zadanie1();
    zadanie2();
    // zadanie3();
    // zadanie4();
    
    return 0;
}
