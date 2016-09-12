#include<iostream>
#include<map>
#include<cstdio>

using namespace std;

int main(){
//	freopen("in.txt","r",stdin);
	typedef multimap<int, int> MyMap;
	MyMap members;
	members.insert(make_pair(1000000000,1));	
	int n;
	scanf("%d",&n);
	
	while(n--){
		int id,value;
		scanf("%d %d",&id,&value);
		members.insert(make_pair(value,id));
		MyMap::const_iterator low,up;
		up = members.upper_bound(value);
		low = members.lower_bound(value);
		if(low != members.begin()){
			low--;
		}
		else {
			printf("%d %d\n",id,up->second);
			continue;
		}
		if( 2*value > low->first + up->first){
			printf("%d %d\n",id,up->second);	
		}
		else{
			printf("%d %d\n",id,low->second);	
		} 
		
	}
	
	return 0;
}
