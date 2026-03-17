# include <iostream>
# include <string>

class ddd
{
	public:
		std::string name;
};

class Date: public ddd
{
	private:
		int year;
		int month;
		int day;

	public:		
	
		Date(int y=0, int m=0, int d=0){
			year = y;
			month = m;
			day = d;			
		}

		Date(int y, int m, float d){
			year = y;
			month = m;
			day = d;			
		}		
		// сеттеры и геттеры
		void setDate(int y, int m, int d){
			year = y;
			month = m;
			day = d;			
		}

		std::string getDate(){
			std::string dd = std::to_string(year) + '-' + std::to_string(month) + '-' + std::to_string(day);
			return dd;
		}

		int getYear(){
			return year;
		}
		int getMonth(){
			return month;
		}
		int getDay(){
			return day;
		}

	
};



int main(){

/*
	'21.01.2026'
	'25.12.2025'
*/

	Date dt(2025,2,1);
	Date newdt;
	dt.name = "Привет";
	//dt.setDate(2025,11,8);
	
	std::cout<< dt.getDate()<<"   "<<newdt.getDate()<<"\n";
//	std::cout<< dt.getyear()<<"-"<<dt.month<<"-"<<dt.day<<"\n";
	


}
