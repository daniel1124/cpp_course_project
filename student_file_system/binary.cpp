#include<iostream>
using namespace std;

int main(){
	int ct;
	cin >> ct;
	int arr[ct];	
	for(int iter=0; iter<ct; iter++){
		int x=23,y,i=4,j=3;
		cin >> x;
		cin >> i;
		cin >> j;
		y = x & (1 << i);
		x = (((x >> j) & 1) ^1) << j ;
		arr[iter] = y + x;
	}
	for(int i=0; i< ct; i++)	
		cout << arr[i] << endl;

	
	return 0;
} 
