#include <iostream>
#include <vector>
#include <string>
#include<stdlib.h>
#include<cmath>
#include<sstream>
#include<set>
using namespace std;

template <class T>

void PrintAll( const T & c ) {

    typename T::const_iterator i;

    for( i = c.begin(); i != c.end(); ++i)

		i->Print();

};

class A {

    protected:

    int nVal;

    public:

         A(int i):nVal(i) { }

         void Print() const

{ cout << "A::Print: " << nVal << endl; }

};

class B:public A {

    public:

         B(int i):A(i) { }

         void Print()

{ cout << "B::Print: " << nVal << endl; }

};

int main(){
	int incre[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
	cout << 
}
