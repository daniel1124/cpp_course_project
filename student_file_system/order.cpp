#include <iostream>
#include <list>
using namespace std;

class MyLess: public binary_function<int, int, bool> {
	public:
		bool operator()(const int & x, const int & y) const{
			if ( x % 10 != y % 10)
				return x % 10 > y % 10;
			else{
				int xIn =x , yIn= y;
				if (x < 0) xIn = -x;
				if (y < 0) yIn = -y;
				return xIn > yIn;

			}
		}
};

int main()
{
	int t;
	cin >> t;
	list<int> lst;
	while( t--) {
		int n;
		cin >> n;
		lst.clear();
		int m;
		for( int i = 0;i < n; ++i) {
			cin >> m;
			lst.push_back(m);
		}
		lst.sort(MyLess());
		list<int>::iterator it;
		for( it = lst.begin(); it != lst.end(); ++ it) {
			cout << * it  << " ";
		}
		cout << endl;
	}
	return 0;
}
