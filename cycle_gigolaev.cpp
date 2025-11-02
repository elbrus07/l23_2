#include <iostream>
#include <cmath>

int main(){
  //1. Для введённого пользователем целого числа выдать максимальную цифру, минимальную цифру и их произведение
  
  /*
  int n;
  std::cout << "Введите целое число: ";
  std::cin >> n;
  n = std::abs(n);
  
  int max = n % 10;
  int min = n % 10;
  int t = n / 10;
  
  for (; t > 0; t /= 10) {
    int d = t % 10;
    if (d > max) max = d;
    if (d < min) min = d;
  }
  
  while (t > 0) {
    int d = t % 10;
    if (d > max) max = d;
    if (d < min) min = d;
    t /= 10;
  }

  do {
    if (t > 0) {
      int d = t % 10;
      if (d > max) max = d;
      if (d < min) min = d;
      t /= 10;
    }
  } while (t > 0);
  
  std::cout << "Максимальная цифра: " << max << std::endl;
  std::cout << "Минимальная цифра: " << min << std::endl;
  std::cout << "Произведение: " << max * min << std::endl;
  */
  
  
  //2. Последовательность содержит некоторое количество натуральных чисел и заканчивается числом 0 (0 не является элементом последовательности). Найти сумму вех элементов последовательности
  
  /*
  int s = 0;
  for (;;) {
    int n;
    std::cout << "Введите число (0 для завершения): ";
    std::cin >> n;
    if (n == 0) break;
    s += n;
  }
  std::cout << "Сумма: " << s << std::endl;
  */
  
  /*
  int s = 0;
  int n;
  std::cout << "Введите число (0 для завершения): ";
  std::cin >> n;
  while (n != 0) {
    s += n;
    std::cout << "Введите число (0 для завершения): ";
    std::cin >> n;
  }
  std::cout << "Сумма: " << s << std::endl;
  */
  
  /*
  int s = 0;
  int n;
  do {
    std::cout << "Введите число (0 для завершения): ";
    std::cin >> n;
    if (n != 0) s += n;
  } while (n != 0);
  std::cout << "Сумма: " << s << std::endl;
  */
  
  //3. Дано целое число. Удалить из него заданную цифру. Например, если задано 1464235 и цифра 4, то должно получиться 16235.
  
  /*
  int num, digit_remove;
  std::cout << "Введите число: ";
  std::cin >> num;
  std::cout << "Введите цифру для удаления: ";
  std::cin >> digit_remove;
  
  int res = 0;
  int multiplier = 1;
  for (int temp = num; temp > 0; temp /= 10) {
    int digit = temp % 10;
    if (digit != digit_remove) {
      res += digit * multiplier;
      multiplier *= 10;
    }
  }
  std::cout << "Результат: " << res << std::endl;
  */
  
  /*
  int num, digit_remove;
  std::cout << "Введите число: ";
  std::cin >> num;
  std::cout << "Введите цифру для удаления: ";
  std::cin >> digit_remove;
  
  int res = 0;
  int multiplier = 1;
  int temp = num;
  while (temp > 0) {
    int digit = temp % 10;
    if (digit != digit_remove) {
      res += digit * multiplier;
      multiplier *= 10;
    }
    temp /= 10;
  }
  std::cout << "Результат: " << res << std::endl;
  */
  
  /*
  int num, digit_remove;
  std::cout << "Введите число: ";
  std::cin >> num;
  std::cout << "Введите цифру для удаления: ";
  std::cin >> digit_remove;
  
  int res = 0;
  int multiplier = 1;
  int temp = num;
  do {
    int digit = temp % 10;
    if (digit != digit_remove) {
      res += digit * multiplier;
      multiplier *= 10;
    }
    temp /= 10;
  } while (temp > 0);
  std::cout << "Результат: " << res << std::endl;
  */
  
  //4. Для каждого натурального числа в промежутке от N до M вывести все делители, кроме единицы и самого числа. Значения N и M вводятся с клавиатуры.
  
  /*
  int N, M;
  std::cout << "Введите N и M: ";
  std::cin >> N >> M;
  
  for (int i = N; i <= M; ++i) {
    std::cout << "Делители " << i << ": ";
    for (int j = 2; j < i; ++j) {
      if (i % j == 0) {
        std::cout << j << " ";
      }
    }
    std::cout << std::endl;
  }
  */
  
  /*
  int N, M;
  std::cout << "Введите N и M: ";
  std::cin >> N >> M;
  
  int i = N;
  while (i <= M) {
    std::cout << "Делители " << i << ": ";
    int j = 2;
    while (j < i) {
      if (i % j == 0) {
        std::cout << j << " ";
      }
      ++j;
    }
    std::cout << std::endl;
    ++i;
  }
  */
  
  /*
  int N, M;
  std::cout << "Введите N и M: ";
  std::cin >> N >> M;
  
  int i = N;
  do {
    std::cout << "Делители " << i << ": ";
    int j = 2;
    do {
      if (j < i && i % j == 0) {
        std::cout << j << " ";
      }
      ++j;
    } while (j < i);
    std::cout << std::endl;
    ++i;
  } while (i <= M);
  */
  
  //5. Вывести на экран двумерную таблицу умножения.
  
  /*
  std::cout << "Таблица умножения:" << std::endl;
  for (int i = 2; i <= 9; ++i) {
    for (int j = 2; j <= 9; ++j) {
        std::cout << i << " * " << j << " = " << (i * j) << "\t";
    }
    std::cout << std::endl;
  }
  */
  
  /*
  std::cout << "Таблица умножения:" << std::endl;
  int i = 2;
  while (i <= 9) {
    int j = 2;
    while (j <= 9) {
      std::cout << i << " * " << j << " = " << (i * j) << "\t";
      ++j;
    }
    std::cout << std::endl;
    ++i;
  }
  */
  
  /*
  std::cout << "Таблица умножения:" << std::endl;
  int i = 2;
  do {
    int j = 2;
    do {
      std::cout << i << " * " << j << " = " << (i * j) << "\t";
      ++j;
    } while (j <= 9);
    std::cout << std::endl;
    ++i;
  } while (i <= 9);
  */
   
  return 0;
}
