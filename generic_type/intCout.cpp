#include<iostream>
#include<iomanip>
using namespace std;

int main(){
	int x;
	cin >> x;
	cout << hex << x << endl;
	cout << dec<<setw(10) << setfill('0') << x << endl;
	return 0;
}
