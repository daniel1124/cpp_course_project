#include<cstdio>
#include<queue>
#include<iostream>
using namespace std;

int ct_pfac (int n){
	int a = 2;
	int ct = 0;
	while(a*a <= n){
		if(n%a == 0){
			ct ++;
			n = n/a;	
		}
		while(n%a == 0){
			n = n/a;
		}
		a++;
	}
	if(n > 1 and ct > 0) return ct+1;
	return ct;
} 

class myCompare1: public binary_function<int, int, bool>{
	public:
		bool operator()(int x, int y) const {
			int ctx = ct_pfac(x);
			int cty = ct_pfac(y);
			if(ctx == cty) return x < y;
			return ctx < cty;
		}
};

class myCompare2: public binary_function<int, int, bool>{
	public:
		bool operator()(int x, int y) const {
			int ctx = ct_pfac(x);
			int cty = ct_pfac(y);
			if(ctx == cty) return x > y;
			return ctx > cty;
		}
};

int main(){
	freopen("in.txt","r",stdin);
	
	typedef priority_queue<int,vector<int>,myCompare1> MyQueue1;
	typedef priority_queue<int,vector<int>,myCompare2> MyQueue2;

	MyQueue1 data1;
	MyQueue2 data2;
		
	int n,temp;
	scanf("%d",&n);
	printf("%d",n);
	while(n--){
		for(int i=0; i<10; i++){
			cin >> temp;
//			scanf("%d", &temp);
			data1.push(temp);
			data2.push(temp);
		}
//		printf("%d %d\n",data1.top(),data2.top());
		cout << data1.top() << " " << data2.top() << endl;
		data1.pop(),data2.pop();
	}
	
	
	return 0;
}
