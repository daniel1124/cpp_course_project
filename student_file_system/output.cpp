#include <iostream>
using namespace std;

class base{
	int val;
	int type; // 0:A, 1:B
	public:
		const static char typeName[2];
		base(int valIn, int typeIn): val(valIn), type(typeIn){}
		int getVal() const {return val;}
		int getType() const {return type;}
};

class A: public base{
	public:
		A(int k): base(k,0){}	
};

class B: public base{
	public:
		B(int k): base(k,1){}	
};

void PrintInfo(const base * a){
	cout << base::typeName[a->getType()] << " " << a->getVal() << endl;
}

const char base::typeName[2] = {'A','B'}; 

base * a[100];

int main()
{
	int t;
	cin >> t;
	while( t -- ) {
		int n;
		cin >> n;
		for( int i = 0;i < n; ++i)	{
			char c; int k;
			cin >> c >> k;
			if( c == 'A')
				a[i] = new A(k);
			else
				a[i] = new B(k);
		}
		cout << n << endl;
		for( int i = 0;i < n; ++i)
			PrintInfo(a[i]);
		cout << "****" << endl;
	}
}
