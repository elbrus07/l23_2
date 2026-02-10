#include <iostream>
#include <fstream>
#include <string> 
#include <array> 
#include <format> 
using namespace std;
/*
1. Реализовать функции для работы с файлом данных, в котором содержатся сведения о студентах:
	(Фамилия, Имя, Отчество, дата рождения, группа, номер зачетки, курс)
	Данные должны храниться в файле: db_stud.dat
	В каждой строке файла хранятся данные об одном студенте
	Функции: 
- запись в файл нового студента
- чтение данных об одном или нескольких указанных студентах, в указанном порядке сортировки
- подсчет количества студентов

Пример содержимого файла данных:
fam#name#otch#dt_r#gr#n_z#kurs
Алмазов#Алаз#Пахратович#2002-12-01#33#IVT22221#3
Баграев#Батраз#Аланович#2002-02-01#33#IVT22225#3
*/

/*
Функция записывает данные студента в файл.

param filename - Имя файла для записи данных
param surname - Фамилия студента
param name - Имя студента
param patronymic - Отчество студента
param date_of_birth - Дата рождения студента
param group - Группа студента
param record_book_number - Номер зачетной книжки
param course - Курс обучения

*/
int write_student_to_file(string filename, 
                   string surname, 
                   string name, 
                   string patronymic,
                   string date_of_birth,
                   string group,
                   string record_book_number,
                   string course) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        return -1;
    }

    file << surname << "#" << name << "#" << patronymic << "#"
         << date_of_birth << "#" << group << "#" << record_book_number << "#"
         << course << endl;

    file.close();
    return 0;
}

/*
Функция принимает строку в формате с разделителями '#' и возвращает массив из 7 строк, содержащих отдельные поля данных студента.
 
param str Входная строка с данными студента
return статический массив из 7 строк с полями данных:
         [0] - фамилия, [1] - имя, [2] - отчество, [3] - дата рождения,
         [4] - группа, [5] - номер зачетной книжки, [6] - курс
*/
string* split_stud_str(string str) {
    static string arr[7];
    int start = 0;
    int end = str.find("#");
    for(int i=0; i < 7; i++){
        arr[i] = str.substr(start, end-start);
        start = ++end;
        end = str.find("#", start);
    }
    
    return arr;
}

/*
Функция подсчитывает количество студентов с возможностью фильтрации
 
param filename Имя файла с данными студентов
param field Номер поля для фильтрации (0-6). По умолчанию -1 (без фильтра)
    Поля данных:
         0 - фамилия, 1 - имя, 2 - отчество, 3 - дата рождения,
         4 - группа, 5 - номер зачетной книжки, 6 - курс
param value Значение для фильтрации. По умолчанию пустая строка

return Количество студентов, удовлетворяющих условиям фильтра
 
*/
int count_students(string filename, int field =-1, string value="") {
    int count = 0;
    ifstream file(filename);
    string line;
    
    if (file.is_open()) {
        if (field == -1 or value == ""){
            while (getline(file, line)) {
                count++;
            }
        } else {
            while (getline(file, line)) {
                if (split_stud_str(line)[field] == value){
                    count++;
                }
            }
        }
        
        file.close();
    }
    
    return count;
}



/*
	Функция для печати списка студентов
*/

/*
	Функция для печати списка студентов
*/

void print_stud(string stud[][3], size_t n  ){
	
	for (int i= 0; i < n; i++){
		cout << format("{:<20}|{:<10}|{:<10}|",stud[i][0], stud[i][1], stud[i][2])<<"\n";
	}
		
}
  
int main(){
    
    string filename = "db_stud.dat";
	string stud[3][3]{{"Hello","212","3"},{"ОК","56","7"},{"YES","12","11"}};
	
	int n = 3;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n-1; j++){
				if (stud[j][1] > stud[j+1][1] ){
					for (int k = 0; k < n; k++){
						string z = stud[j][k];
						stud[j][k] = stud[j+1][k];
						stud[j+1][k] = z;
					}
				}
		}
		print_stud(stud, 3);
	}
	
	//	array<array<string, 3>, 3> stud {{"Привет","2","3"},{"ОК","56","7"},{"YES","12","11"}};
	print_stud(stud, 3);
	
	//	cout << format("{:<20}|{:<10}|{:<10}",stud[0][0],stud[0][1],stud[0][2])<<"\n";	    
    
    /*
    write_student_to_file(filename, "Сидоров", "Сидор", "Сидорович", 
                      "2003-05-15", "ИВТ-33", "66221", "2");
    */
    
    
    cout << count_students(filename) << endl;
    cout << count_students(filename, 6, "2") << endl;
    
    return 0;
}
