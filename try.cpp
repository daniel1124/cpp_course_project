#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

class base{
	protected:
	int * a[4];
	public:
	//	base(int ** newa, int newc){a = newa; c = newc;}
		virtual int ** geta(){}
		virtual int getb(){return 10;}
		int c;
};

class derive1: public base{
	int b;
	public: 
		int ** geta(){return a;}
	//	derive1(int newa, int newc, int newb):base(newa,newc),b(newb){}
	//		int geta(){return base::geta();}
			int getb(){return base::getb() + 88;}

};

class derive2: public base{
	int b;
	public: 
//		derive2(int newa, int newc, int newb):base(newa,newc),b(newb){}
//			int geta(){return base::geta();}
			

};




	

int main() {
	float a = 1566.0/80.0;
	printf("%f\n",a);
}
	

