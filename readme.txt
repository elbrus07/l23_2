1.
#include <iostream>
using namespace std;

int main() {
	double a, b, c;
	cout <<"Enter 3 numbers:";
	cin >> a >> b >> c;
	
	double max=a;
	if (b > max) max = b;
	if (c > max) max=c;
	
	cout <<"Max number:" << max << endl;
	return 0;
}
2.
#include <iostream>
using namespace std;

int main() {
	double a, b, c;
	cout <<"Enter 3 numbers:";
	cin >> a >> b >> c;
	
	double result;
	if (a != 0 && b != 0 && c != 0)
{
	result = a * b * c;
	cout << "Product numbers:" << result << endl;
	} else {
		result = a + b + c;
		cout <<"Summa number:" << result << endl;
	}
	
	return 0;
}
3. 
#include <iostream>
using namespace std;

int main() {
	double a, b, c;
	cout <<"Enter 3 numbers:";
	cin >> a >> b >> c;
	
	
	if (a > b) swap(a, b);
	if (b > c) swap(b, c);
	if (a > b) swap(a, b);
	
	cout <<"numbers order:" << a << " " << b << " " << c << endl;
	return 0;
}
6.
#include <iostream>
using namespace std;

int main() {
	double x, y;
	cout <<"Enter coordinats (x, y):";
	cin >> x >> y;
	
	if (x ==0 && y==0) {
		cout <<"starts coord:"<< endl;
	} else if (x == 0){
		cout <<" Ha Y"<< endl;
	} else if (y == 0) {
		cout <<" Ha x"<< endl;
	} else if (x > 0 && y > 0) {
		cout << " 1"<< endl;
	} else if (x < 0 && y > 0) {
		cout << " 2"<< endl;
	} else if (x < 0 && y < 0) {
		cout << " 3"<< endl;
	} else {
		cout << " 4"<< endl;
	}
	return 0;
}
7.
#include <iostream>
using namespace std;

int main() {
	double number;
	cout <<"Enter  number:";
	cin >> number;
	
	if (number == static_cats<int>(number)){
		cout << "integer:" << endl;
	} else {
		cout << "fractional number:"<< endl;
	return 0;
}
	
	
