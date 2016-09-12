#include<cstdio>
#include<iostream>

using namespace std;

int binaryFind(int head, int tail, int wood[], int N, int K){
	int smLen = (tail + head) /2 ;
	int ct = 0;
	for(int i=0; i< N; i++){
		ct += wood[i] / smLen;
	}
	
	
	if ( tail - head <= 1) {
		if (ct >= K) return smLen;
		else return 0;
	}
	
	if(ct >= K) return binaryFind(smLen, tail, wood, N, K);
	else return binaryFind(head, smLen, wood, N, K);
		
	
}


int main(){
//	freopen("myin.txt","r",stdin);
	int N,K;
	int maxLen = 0;
	cin >> N >> K;
	
	int wood[N];
	for (int i=0; i<N; i++){
		cin >> wood[i];
		if (wood[i] > maxLen) maxLen = wood[i];
	}
	

	cout << binaryFind(1, maxLen, wood, N, K);
	
	return 0;
}
