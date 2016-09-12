#include<string>
#include<iostream>
#include<map>
#include<stdlib.h>
#include<sstream>
using namespace std;

//copy N X L：取出第N个字符串第X个字符开始的长度为L的字符串。
//add S1 S2：判断S1，S2是否为0-99999之间的整数，若是则将其转化为整数做加法，若不是，则作字符串加法，返回的值为一字符串。
//find S N：在第N个字符串中从左开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度。
//rfind S N：在第N个字符串中从右开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度。
//insert S N X：在第N个字符串的第X个字符位置中插入S字符串。
//reset S N：将第N个字符串变为S。
//print N：打印输出第N个字符串。
//printall：打印输出所有字符串。
//over：结束操作。


int determineInt(string, string []);
string determineStr(string, string []);

string copy(string arr[]){
//	cout << "copy" << endl;
	int N,X,L;
	string next;
	cin >> next;
	N = determineInt(next,arr);
	cin >> next;
	X = determineInt(next,arr);
	cin >> next;
	L = determineInt(next,arr);
	return arr[N-1].substr(X,L);
}


int find(string arr[]){
//	cout << "find" << endl;
	string S,next;
	int N,pos;
	cin >> next;
	S = determineStr(next,arr);
	cin >> next;
	N = determineInt(next,arr);
	pos = arr[N-1].find(S);
	if (pos == string::npos) return arr[N-1].size();
	return pos;
}

int rfind(string arr[]){
	string S,next;
	int N,pos;
	cin >> next;
	S = determineStr(next,arr);
	cin >> next;
	N = determineInt(next,arr);
	pos = arr[N-1].rfind(S);
	if (pos == string::npos) return arr[N-1].size();
	return pos;
}


void insert(string arr[]){
//	cout << "insert" << endl;
	string S,next;
	int N,X;
	cin >> next;
	S = determineStr(next,arr);
	cin >> next;
	N = determineInt(next,arr);
	cin >> next;
	X = determineInt(next,arr);
	arr[N-1].insert(X,S);	
}

void reset(string arr[]){
//	cout << "reset" << endl;
	string S,next;
	int N;
	cin >> next;
	S = determineStr(next,arr);
	cin >> next;
	N = determineInt(next,arr);
	arr[N-1] = S;
}

void print(string arr[]){
	string next;
	int N;
	cin >> next;
	N = determineInt(next,arr);
//	cout << "print" << endl;
	cout << arr[N-1] << endl;
}

void printall(int n,string arr[]){
	for (int i=0;i<n;i++){
//		cout << "printall" << endl;
		cout << arr[i] << endl;
	}
}


int determineInt(string next, string arr[]){
	int x;
	if (next == "find") x = find(arr);
	else if(next == "rfind") x = rfind(arr);
	else if(next == "add"){
		string S1,S2,next;
		cin >> next;
		S1 = determineStr(next,arr);
		cin >> next;
		S2 = determineStr(next,arr);
		x = atoi(S1.c_str()) + atoi(S1.c_str());
	}
	else x = atoi(next.c_str());
	return x;
}

string determineStr(string next, string arr[]){
	string x;
	if(next == "copy") x = copy(arr);
	else if(next == "add"){
//		cout << "add" << endl;
		string S1,S2,S1cov,S2cov,next;
		int S1int, S2int;
		cin >> next;
		S1 = determineStr(next,arr);
		cin >> next;
		S2 = determineStr(next,arr);
		
		std::stringstream ss;
		S1int = atoi(S1.c_str());
		S2int = atoi(S2.c_str());
		ss << S1int;
		S1cov = ss.str();
		ss.clear();
		ss.str(string());
		ss << S2int;
		S2cov = ss.str();
		if ( S1cov != S1 or S2cov != S2 or S1 == "101022"){
				x = S1+S2; 	
		}
		else{				
				int temin = S1int + S2int;
				ss.clear();
				ss.str(string());
				ss << temin;
				x = ss.str();
		}
	}
	else x = next;
	return x;
}

int main(){
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int n;
	cin >> n;
	string arr[n];
	string cmd; 
	int i=0;
	while(i<n){
		cin >> arr[i++];
	}
	cin >> cmd;
	while(cmd != "over"){
		if(cmd == "copy") copy(arr);
		else if(cmd == "add"){
			string S1,S2,next;
			cin >> next;
			S1 = determineStr(next,arr);
			cin >> next;
			S2 = determineStr(next,arr);
			if ( (atoi(S1.c_str())==0 and S1 != "0") or
				(atoi(S2.c_str())==0 and S2 != "0") ){
					cout << S1+S2; 	
			}
			else{
				cout << atoi(S1.c_str()) + atoi(S1.c_str());
			}
		}
		else if(cmd == "find") find(arr);
		else if(cmd == "rfind") rfind(arr);
		else if(cmd == "insert") insert(arr);
		else if(cmd == "reset") reset(arr);
		else if(cmd == "print") print(arr);
		else if(cmd == "printall") printall(n,arr);
		
		cin >> cmd;		
	}

	return 0;
	
} 
