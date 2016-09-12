#include <iostream >

using namespace std;

template <class T>

class myclass {

       T i;

       public:

       myclass (T a)  

{ i = a; }

       void show( )

{ cout << i << endl;     }

};

int main() {

       myclass<string> obj("This");

       obj.show();

       return 0;

}
