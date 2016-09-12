#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

class Try{
	private:	
		int *a;	
		int len;
	public:
		int getLen(){return len;}
		const int * geta() const {return a;}
		Try():a(NULL),len(5){}
		Try(int s =6):a(NULL),len(s){}
		Try(const Try & other){
			a = new int[100];			
			memcpy(a,other.geta(),sizeof(int)*100);
		}
		Try & operator=(const Try & other){
			
		}
		
};


int main(){
	Try a;
	cout << a.getLen();
	return 0;
}
