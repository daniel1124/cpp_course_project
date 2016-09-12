#include<string>
#include<iostream>
#include<cstdio>

using namespace std;

int prefixNum(string s1, string s2){
	if(s1.length() ==0 or s2.length() == 0)
		return 0;
	else if (s1[0] != s2[0])
		return 0;
	else
		return 1 + prefixNum( s1.substr(1,s1.length()-1), s2.substr(1,s2.length()-1) );
}


int main(){
	int N,ct;
//	freopen("myin.txt","r", stdin);
	string s1,s2;
	cin >> N;
	cin >> s1;
	ct += s1.length();
	while(--N){
		
		cin >> s2;
		
		ct += s2.length() - prefixNum(s1,s2) +1 ; 
		
		s1 = s2;
	} 
	cout << ct;	
	return 0;
}
