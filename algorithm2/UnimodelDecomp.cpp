#include<cstdio>
#include<iostream>

using namespace std;

int mem[250][250];


int main(){
	freopen("myin.txt","r",stdin);
	int num;
	cin >> num;
	
	for(int i=0; i<250; i++) 
		for(int j=0; j<250; j++)
			mem[i][j] = 0; 

	
	for(int i=1; i<250; i++){
		for(int j=i/2; j>0; j--){
			
			if(j < i/2){
				mem[i][j] += mem[i][j+1];	
			}
				
			mem[i][j] += mem[i-2*j][j];
			if (2*j == i) mem[i][j] ++;
			if (i >= 3*j) mem[i][j] ++; 
			
		}
		
	}
	
	while(num != 0){
		
		cout << num << " " << mem[num][1] + 1 << endl;
		
		cin >> num;
	}
	return 0;
}
