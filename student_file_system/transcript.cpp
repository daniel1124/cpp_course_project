#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

class Student{
	int score;
	string name;
	public:
		Student() {}
		Student(int scoreIn, string nameIn): score(scoreIn), name(nameIn) {}
		int getScore() const{ return score;}
		string getName() const{return name;}
		void setScore(int scoreIn) {score = scoreIn;}
		void setName(string nameIn) {name = nameIn;}
//	friend ostream & operator <<(ostream &, const Student &);
		bool operator<(const Student &) const;
//	friend istream & operator >>(istream &, Student &);
};

bool Student::operator<(const Student & stu) const{
	return getScore() < stu.getScore();
}

istream & operator >> (istream & is, Student & stu){
	int scoreIn;
	string nameIn;
	is >> nameIn;
	is >> scoreIn;
	stu.setName(nameIn);
	stu.setScore(scoreIn);
	return is;
}

ostream & operator << (ostream & os, Student & stu){
	os << stu.getName();
	return os;
}

int main()
{
	int t;
	vector<Student> v;
	cin >> t;

	while( t--) {
		int n;
		cin >> n;
		Student st;
		v.clear();
		for( int i = 0;i < n; ++i ) {
			cin >> st;
			v.push_back(st);
		}
		sort(v.begin(),v.end());
		for( int i = 0;i < v.size(); ++ i)
			cout << v[i] << endl;
		cout << "****" << endl;
	}
	return 0;
}
