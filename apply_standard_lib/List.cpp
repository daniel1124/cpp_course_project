#include<iostream>
#include<map>
#include<list>

using namespace std;

template <class T>
void PrintList (const list<T> & a){
	int lsize = a.size();
	if(lsize > 0){
		typename list<T>::const_iterator it;
		for(it = a.begin(); it != a.end(); it++){
			cout << *it << " ";
		}
	} 
	cout << endl;	
} 

int main(){
//	freopen("in.txt","r",stdin);
	typedef	map<int, list<int> > MyMap;
	MyMap dict;
	
	int n,id1,id2,num;
	string cmd;
	cin >> n;
	while(n--){
		cin >> cmd;
		if(cmd == "new"){
			cin >> id1;
			list<int> lst;
			dict.insert(make_pair(id1, lst ) );
		}
		else if(cmd == "add"){
			cin >> id1 >> num;
			dict[id1].push_back(num);
		}
		else if(cmd == "merge"){
			cin >> id1 >> id2;
			dict[id1].merge(dict[id2]);
		}
		else if(cmd == "out"){
			cin >> id1;
			dict[id1].sort();
			PrintList(dict[id1]);
		}
		else if(cmd == "unique"){
			cin >> id1;
			dict[id1].sort();
			dict[id1].unique();
		}
	}
	return 0;
}
