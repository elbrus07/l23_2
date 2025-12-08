#include <iostream>
#include <fstream>
#include <string> 

using namespace std;

int main(){
	ofstream ofile("probe.txt", ios::app);		// Открываем файл на запись.
												// ключ ios::app  значит, что данные должны добавляться в конец файла
												// если ключ не указать, то файл перезаписывается

	
	ofile << "\n Добавка1\n";		// Запись в файл
	ofile << "Добавка2\n";
	ofile << "Добавка3\n";
	ofile.close();				// Закрывем открытый файл

	ifstream ifile("probe.txt")	;		// Открываем файл на чтение
	
	if (!ifile.is_open()){			// Проверяем, успешность открытия файла 
		cout << "Ошибка открытия файла! \n";	
		return 1;
	}
	string str;
	while (!ifile.eof()){			// пока не достигнут конец файла
		getline(ifile, str);
		cout << str<<"\n";
	}
	ifile.close();
	return 0;
}
