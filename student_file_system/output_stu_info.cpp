#include <iostream>
#include <string>
using namespace std;

class Student {
	public:
		int id;
		string name;
		Student(){}
		Student(string nameIn, int idIn): id(idIn), name(nameIn){}
		void Read(){
			cin >> name;
			cin >> id;
		}
		void Print(){
			cout << id << " " << name << endl;
		}
};

int main()
{
	int t;
	cin >> t;
	Student s("Tom",12);
	while( t-- )	{
		int n;
		cin >> n;
		Student st;
		for( int i = 0;i < n; ++i) {
			st.Read();
			st.Print();
		}
		cout << "****" << endl;
	}
	return 0;
}
