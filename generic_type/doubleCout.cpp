#include<iostream>
#include<iomanip>
using namespace std;

int main(){
	double x;
	cin >> x;
	cout << fixed<<setprecision(5) << x << endl;
	cout << scientific << setprecision(7) << x << endl;
}
