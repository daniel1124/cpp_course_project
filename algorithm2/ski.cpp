#include<cstdio>
#include<iostream>

using namespace std;

int map[102][102];
int mem[102][102];
int mask[102][102];
int R,C;

int findPath(int x, int y) {
	mask[x][y] = 1;
	int incre[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
	int x1, y1;
	int maxStep = 1;
	for(int i=0; i<4; i++){
		x1 = x + incre[i][0];
		y1 = y + incre[i][1];
		if ( map[x][y] > map[x1][y1] and mask[x1][y1] == 0) {
			if (mem[x1][y1] == -1)	mem[x1][y1] = findPath(x1, y1);
			if (mem[x1][y1] + 1 > maxStep) maxStep = mem[x1][y1] + 1;
		}
	}
	mask[x][y] = 0;
	return maxStep;
}

int main(){
	
//	freopen("myin.txt","r",stdin);
	cin >> R >> C;
	
	for (int i=1; i<=R; i++)
		for(int j=1; j<=C; j++){
			cin >> map[i][j];
			mem[i][j] = -1;
		}
	
	for(int j=0; j<=C+1; j++){
		map[0][j] = 10001;
		map[R+1][j] = 10001;
		mem[0][j] = -1;
		mem[R+1][j] = -1;
	}
	
	for(int i=1; i<=R; i++){
		map[i][0] = 10001;
		map[i][C+1] = 10001;
		mem[i][0] = -1;
		mem[i][C+1] = -1;
	}
	
	int maxStep = 0;
	int tempStep;
	for (int i=1; i<=R; i++)
		for(int j=1; j<=C; j++){
			tempStep = findPath(i, j);
			if (tempStep > maxStep) maxStep = tempStep;
		}
	cout << maxStep;
	
	return 0;
	
}
