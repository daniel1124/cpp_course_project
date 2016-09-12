#include <iostream>
using namespace std;
// 0,1,2,3
// 4,5,6,7
// 8,9,10,11

class Array2 {
	int **num;
	int row;
	int col;
	public:
		Array2(){}	
		Array2(int i, int j){
			num = new int*[i];
			for (int k=0; k<i; k++)	num[k] = new int[j];
		}
		int * operator[](int i) {
			return num[i];
		}
		friend ostream & operator<<(ostream & os, const Array2 & a);
};

	ostream & operator<<(ostream & os, const Array2 & a){
	os << a[a.row][a.col];
	return os; 
}

int main() {
	Array2 a(3,4);
	int i,j;
	for(  i = 0;i < 3; ++i )
		for(  j = 0; j < 4; j ++ )
			a[i][j] = i * 4 + j;
	for(  i = 0;i < 3; ++i ) {
		for(  j = 0; j < 4; j ++ ) {
			cout << a[i][j] << ",";
		}
		cout << endl;
	}
	cout << "next" << endl;
	Array2 b; 	b = a;
	for(  i = 0;i < 3; ++i ) {
		for(  j = 0; j < 4; j ++ ) {
			cout << b[i][j] << ",";
		}
		cout << endl;
	}
	return 0;
}

