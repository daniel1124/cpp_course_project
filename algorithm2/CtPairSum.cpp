#include<cstdio>
#include<iostream>

using namespace std;

int an,bn,s;
int A[10000];

int pairSum(int bmap[]){
	int ct = 0;
	for(int i=0; i<an; i++){
		if (s >= A[i]){
			ct += bmap[s-A[i]];
		}
	}
	return ct;
}

int main(){
//	freopen("in.txt","r",stdin);
	int n,temp;
	cin >> n;
	while(n--){
		int bmap[10000] = {0};
		cin >> s;
		cin >> an;
		for(int i=0; i<an; i++){
			cin >> A[i];
		}
		
		cin >> bn;
		for(int i=0; i<bn; i++){
			cin >> temp;
			bmap[temp] ++;
		}
		cout << pairSum(bmap) << endl;
	} 
	
	
	return 0;
}
