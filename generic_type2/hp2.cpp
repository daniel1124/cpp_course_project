#include <vector>

#include <iostream>

#include <string>

using namespace std;

template <class T>

class MyClass

{

    vector<T>  array;

    public:

         MyClass ( T * begin,int n ):array(n)

{ copy( begin, begin + n, array.begin());}

void List() {

typename vector<T>::const_iterator i;

for(i=array.begin();i!=array.end();++i )

         cout << * i << "," ;

}

};

int main() {

    string array[4] =

{ "Tom","Jack","Mary","John"};

MyClass<string> obj(array,4);

    obj.List();

    return 0;

} 
