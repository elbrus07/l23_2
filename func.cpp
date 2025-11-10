/*
	Функции:
	Объявление функции:
	
	тип_возврата имя_функции(список параметров){
		тело функции
	}
	тип_возврата: тип значения, которе возвращает функция, например int
		должен в теле быть return значение
	или
	void - если функция ничего 	не возвращает
		не должно быть в теле return
	
	список параметров: тип_параметра1 имя_параметра1, тип_параметра2 имя_параметра2, ...
	
*/

#include <iostream>
#include <string>

int compare(int a, int b){
	if (a < b){
		return a;
	}else{
		return b;
	}
}

int main(){

	int a = 9;
	int b = 8;
	std::cout<< compare(a,b)<<"\n";
	
	std::string s = "hello !";

	std::cout<< s.size()<<"\n";

	s.replace(3,2,"tftt");
	int k0 = s.find('e');
	int k1 = s.find('d');
	
	std::cout<<k0<<" "<<k1<<"\n";
	
		
	
	

}



