#include<cstdio> 
#include<string>
#include<iostream>
#include<cmath>

using namespace std;

// w:1, y:0

int countPaint(int ** paint, int ** canvas, int n){
	int c, r;
	int totalPaint = 0;
	for(r=1; r<n; r++)
		for(c=1; c<n+1; c++){
			paint[r+1][c] = (canvas[r][c]+paint[r][c]+
				paint[r-1][c]+ paint[r][c-1]+paint[r][c+1]) %2;
			totalPaint += paint[r+1][c];
		}
	for(c=1; c<n+1; c++){
		totalPaint += paint[1][c];
		if ((paint[n][c-1] + paint[n][c] + paint[n][c+1] +
				paint[n-1][c]) %2 != canvas[n][c] )
			return n*n + 1;
	}
	return totalPaint;
	
}

int findMinPaint(int ** paint, int ** canvas, int n){
	int c,ct;
	int currMin = n*n + 1;
	for ( c=1; c<n+1; c++)
		paint[1][c] = 0;
	
	int maxIter = pow(2,n) ;
	for(int i=0; i<maxIter; i++){
		
		ct = countPaint(paint, canvas, n);
		if(ct < currMin) currMin = ct;
		
		paint[1][1]++;
		c = 1;
		while (paint[1][c] > 1) {
			paint[1][c] = 0;
			c++;
			paint[1][c]++;
		}
	}
	return currMin;
}



int main() {
//	freopen("in.txt","r",stdin);
//	freopen("myout.txt","w",stdout);
	int cases, n, r, c;
	string temp;
	scanf("%d", &cases);
	while(cases--){
		scanf("%d", &n);
		int ** paint = new int *[n+1];
		int ** canvas = new int *[n+1];
		for(int i=0;i<n+1;i++){
			paint[i] = new int[n+2];
			canvas[i] = new int[n+2];
		}
		
		
		for ( r=0; r<n+1; r++ )
			paint[r][0] = paint[r][n+1] = 0;
		for ( c=1; r<n+1; r++ )
			paint[0][c] = 0;
		
		for(r=1; r<n+1; r++){
			cin >> temp;
			for(c=1; c<n+1; c++){
				canvas[r][c] = int(temp[c-1] == 'w');	
			}
		}
		
		int result = findMinPaint(paint,canvas,n);
		if(result == n*n + 1) printf("inf\n");
		else printf("%d\n",result);
		delete[] paint;
		delete[] canvas;
	}
		
	return 0;
}	





