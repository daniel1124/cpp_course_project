#include <iostream>
#include <map>
using namespace std;

struct Student
{
	int id;
	string name;
	int score;
	Student(int id_,const string & nm,int sc):
		id(id_),name(nm),score(sc) { }
	Student() { }


};

struct Info
{
	string name;
	int score;
	Info(const string & s,int sc):name(s),score(sc) { }
};

pair<int,Info>  MyMakePair(const Student & st){
	Info myInfo(st.name,st.score);
	int myId = st.id;
	return make_pair(myId,myInfo);
	
}

Student MyFind(map<int,Info> & mp, int score){
	map<int,Info>::const_iterator i;
	for(i = mp.begin(); i != mp.end(); i++){
		if (i->first == score){
			Student st(i->first, i->second.name, i->second.score);
			return st;
		}
	}
}

int main()
{
	std::map<int,Info>  mp;
	int t;
	cin >> t;
	while( t -- ) {
		mp.clear();
		int n;
		cin >> n;
		Student st;
		for( int i = 0;i < n; ++i) {
			cin >> st.id >> st.name >> st.score;
			mp.insert(MyMakePair(st));
		}
		cin >> n;
		st = MyFind(mp,n) ;
		cout << st.name << " " << st.score  << endl;
	}
	return 0;
}
