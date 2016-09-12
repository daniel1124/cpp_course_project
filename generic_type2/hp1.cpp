#include <vector>

#include <iostream>

using namespace std;

class A {

    private :

         int nId;

    public:

    A(int n) {   nId = n;

    cout << nId << " constructor" << endl;  }

    ~A( )

     {cout << nId << " destructor" << endl; }

};

int main()  {

    vector<A*> vp;

    vp.push_back(new A(1));

    vp.push_back(new A(2));

    vp.clear(); A a(4);

    return 0;

}
