#include <iostream>
using namespace std;

// 1. Ручной ввод массива
void task1() {
    int n;
    cout << "Введите размер массива: ";
    cin >> n;
    
    int* arr = new int[n];
    cout << "Введите " << n << " элементов: ";
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    cout << "Ваш массив: ";
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    delete[] arr;
}

// 2. Случайный массив
void task2() {
    int size;
    cout << "Введите размер массива: ";
    cin >> size;
    
    int min_val, max_val;
    cout << "Введите минимальное значение: ";
    cin >> min_val;
    cout << "Введите максимальное значение: ";
    cin >> max_val;
    
    int* arr = new int[size];
    for(int i = 0; i < size; i++) {
        arr[i] = min_val + rand() % (max_val - min_val + 1);
    }
    
    cout << "Случайный массив: ";
    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    delete[] arr;
}

// 3. Равное количество 0 и 1
void task3() {
    int n;
    cout << "Введите n (массив будет из 2n элементов): ";
    cin >> n;
    
    int size = 2 * n;
    int* arr = new int[size];
    
    // Заполняем первую половину единицами, вторую - нулями
    for(int i = 0; i < n; i++) {
        arr[i] = 1;
    }
    for(int i = n; i < size; i++) {
        arr[i] = 0;
    }
    
    // Перемешиваем
    for(int i = 0; i < size; i++) {
        int j = rand() % size;
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    
    cout << "Массив с равным количеством 0 и 1: ";
    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    delete[] arr;
}

// 4. Сумма с чередованием знаков
void task4() {
    int n;
    cout << "Введите n (массив будет из 2n элементов): ";
    cin >> n;
    
    int size = 2 * n;
    int* A = new int[size];
    
    cout << "Введите " << size << " элементов: ";
    for(int i = 0; i < size; i++) {
        cin >> A[i];
    }
    
    int sum = 0;
    for(int i = 0; i < size; i += 2) {
        sum += A[i] - A[i+1];
    }
    
    cout << "Результат: " << sum << endl;
    
    delete[] A;
}

// 5. Два числа с суммой, близкой к p
void task5() {
    int n;
    cout << "Введите размер массива: ";
    cin >> n;
    
    int* arr = new int[n];
    cout << "Введите элементы массива: ";
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    int p;
    cout << "Введите число p: ";
    cin >> p;
    
    int num1 = arr[0];
    int num2 = arr[1];
    int min_diff = (arr[0] + arr[1] > p) ? (arr[0] + arr[1] - p) : (p - (arr[0] + arr[1]));
    
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            int sum = arr[i] + arr[j];
            int diff = (sum > p) ? sum - p : p - sum;
            if(diff < min_diff) {
                min_diff = diff;
                num1 = arr[i];
                num2 = arr[j];
            }
        }
    }
    
    cout << "Числа: " << num1 << " и " << num2 << endl;
    cout << "Их сумма: " << num1 + num2 << endl;
    cout << "Разница с p: " << min_diff << endl;
    
    delete[] arr;
}

// 6. Замена четных элементов
void task6() {
    int n;
    cout << "Введите размер массива: ";
    cin >> n;
    
    int* arr = new int[n];
    cout << "Введите элементы массива: ";
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    for(int i = 2; i < n; i += 2) {
        arr[i] = arr[i-1];
    }
    
    cout << "Измененный массив: ";
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    delete[] arr;
}

// 7. Поменять местами max и min
void task7() {
    int n;
    cout << "Введите размер массива: ";
    cin >> n;
    
    int* arr = new int[n];
    cout << "Введите элементы массива: ";
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    int min_index = 0;
    int max_index = 0;
    
    for(int i = 1; i < n; i++) {
        if(arr[i] < arr[min_index]) {
            min_index = i;
        }
        if(arr[i] > arr[max_index]) {
            max_index = i;
        }
    }
    
    int temp = arr[min_index];
    arr[min_index] = arr[max_index];
    arr[max_index] = temp;
    
    cout << "После обмена min и max: ";
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    delete[] arr;
}
