#include <iostream>

#include <string>

using namespace std;

template <class T> 

class myclass {

       T * p;

       int nSize;

public:

       myclass (const T * a, int n)  {

              p = new T[n];

              for( int i = 0;i < n;++i )

                     p[i] = a[i];

              nSize = n;

       }

       ~myclass( ) {

              delete [] p;

       }

       void Show()

       {

              for( int i = 0;i < nSize;++i ) {

                     cout << p[i];

              }

       }

};

int main() {

       char * szName = "TomHanks";

       myclass<char >obj(szName, 8);

       obj.Show();  return 0;

}
