#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;

int main(){
//	freopen("myin.txt","r",stdin);
	int tune[9];
	int bestTune[9];
	int clock[9];
	bool check[4];
	int currMin = 28;
	for(int i=0;i<9;i++) {
		tune[i] = 0;
		scanf("%d",clock+i);
	}
	
	
	for(tune[1] =0; tune[1]<4; tune[1]++)
		for(tune[3] =0; tune[3]<4; tune[3]++)
			for(tune[5] =0; tune[5]<4; tune[5]++)
				for(tune[7] =0; tune[7]<4; tune[7]++){
					int ct=0;
					tune[0] = (4 - ( tune[1] + tune[3] + clock[0]) % 4) % 4; //124A
					tune[6] = (4 - ( tune[3] + tune[7] + clock[6]) % 4) % 4; //478G
					tune[8] = (4 - (tune[5] + tune[7] + clock[8]) % 4) % 4; //689I
					tune[2] = (4 - (tune[1] + tune[5] + clock[2]) % 4) % 4; //236C
					tune[4] = (4 - (tune[0] + tune[1] + tune[2] + clock[1]) % 4) % 4; //1235B
					
//					for(int i=0; i<9; i++) cout << tune[i] << " ";
					
					check[0] = (tune[0] + tune[3] + tune[4] + tune[6] + clock[3]) % 4 == 0; //1457D
					check[1] = (tune[0] + tune[2] + tune[4] + tune[6] + tune[8] + clock[4]) % 4 == 0; //13579E
					check[2] = (tune[2] + tune[4] + tune[5] + tune[8] + clock[5]) % 4 == 0; //3569F
					check[3] = (tune[4] + tune[6] + tune[7] + tune[8] + clock[7]) % 4 == 0; //5789H
					
					if (check[0] and check[1] and check[2] and check[3]){
						for(int i=0; i<9; i++){
							ct += tune[i];
						}
						if (ct < currMin) {
							memcpy(bestTune,tune,9*sizeof(int));
							currMin = ct;
						}
					}
				}
	if(currMin < 28){
		for(int i=0; i<9; i++){
			for(int j=0; j<bestTune[i]; j++)
				cout << i+1 << " ";
		}
	}
	return 0;
}
