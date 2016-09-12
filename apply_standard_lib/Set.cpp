#include<set>
#include<iostream>
using namespace std;
int main(){
//	freopen("in.txt","r", stdin);
	set<int> mySet;
	multiset<int> myMulSet;
	
	int n,x;
	string cmd;
	cin >> n;
	while(n--){
		cin >> cmd >> x;
		if(cmd== "add"){
			mySet.insert(x);
			myMulSet.insert(x);
			cout << myMulSet.count(x) << endl;
		}
		else if(cmd == "del"){
			cout << myMulSet.count(x) << endl;
			myMulSet.erase(myMulSet.lower_bound(x),myMulSet.upper_bound(x));
		}
		else if(cmd == "ask"){
			set<int>::const_iterator p;
			p = mySet.find(x);
			if(p != mySet.end()) cout << "1 " << myMulSet.count(x) << endl;
			else cout << "0 " << myMulSet.count(x) << endl;
		}
	}
	
	return 0;
}
