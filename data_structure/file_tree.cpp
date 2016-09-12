#include<string>
#include<iostream>
#include<cstdio>
#include<set>

using namespace std;

void printDirectory(string s, int rank, string mark){
	multiset<string> files;
	if (rank == 0) cout << "ROOT" << endl;
		
	while(s != mark){
		if( s[0] == 'f') {
			files.insert(s);
		}
		else if( s[0] == 'd') {
			for(int i=0; i<rank+1; i++) cout << "|     ";
			cout << s << endl;
			cin >> s;
			printDirectory(s,rank+1, "]");
		}		
		cin >> s;
	}
	if( files.size() >0 ){
		multiset<string>::const_iterator it;
		for(it=files.begin(); it != files.end(); it++) {
			for (int i=0; i<rank; i++) cout << "|     ";
			cout << *it << endl;	
		}
	}
}

int main(){
//	freopen("myin.txt","r",stdin);
	string s;
	int caseNum = 1;
	cin >> s;
	while(s != "#"){
		cout << "DATA SET " << caseNum << ":" << endl;
		printDirectory(s, 0, "*");
		cout << endl;
		caseNum ++;
		cin >> s;
	}	
	return 0;
}
