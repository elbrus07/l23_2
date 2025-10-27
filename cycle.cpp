#include <iostream>
/*
	Циклы в С++
	цикл for 
	for(инициализация; условие; инкремент){		- заголовок цикла
		тело цикла
	}
	
	Цикл while 
	
	Цикл do while	- цикл с постусловием
	
	Синтаксис:
	do{
		тело цикла
	} while (условие)
	
	break
	continue

*/

int main(){

//	Пример:
	for (int i {0}; i < 10; i+=4){
		std::cout<<i<<"\n";		
	}


	int i {1};
	for (;i < 5; ){
		std::cout<<"Привет!"<< i <<"\n";		
		i++;
	}


	return 0;
}

