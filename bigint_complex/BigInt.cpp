#include <cstdio>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cstring>

using namespace std;

class BigInt{
	private:
	int * num; // The number
	int len; // The highest position
	int sign; // pos:1, neg:-1, zero or null:0
	static const int MAX_LEN,MAX_INP;
	int intLen(int *); // find the highest position
	int bstDiv(BigInt &, const BigInt &, int, int); // use binary search to find the divisor (1~9), and update the reminder
	
	public:
	// getter
	int getLen() const {return len;} 
	const int * getNum() const {return num; } 
	int getSign() const {return sign;}
	// constructor
	BigInt():num(NULL),len(0),sign(0){} 
	BigInt(int);
	BigInt(int [], int, int);
	// deconstructor
	~BigInt(){if (num) delete [] num;}
	// operator overloading
	int operator>(const BigInt & );
	BigInt & operator=(const BigInt &); 
	BigInt operator+(const BigInt &);
	BigInt operator-(const BigInt &);
	BigInt operator*(const BigInt &);
	BigInt operator/(const BigInt &);
	BigInt & operator<<(int); 
	BigInt MyInput();
	
	int allNine(){
		int check = 1;
		for(int i=0; i<len; i++){
			if(num[i] != 9) check = 0;
		}
		return check; 
	}
	
	void addOne(){
		int nm[MAX_LEN];
		for(int i=1;i<len;i++) num[i] = 0;
		num[len+1] = 1;
		len ++;
	} 
};

// intLen()
int BigInt::intLen(int * nm){
	if(nm){
		int length = MAX_LEN;
		for (int i=MAX_LEN-1; i>=0; i--){
			if(nm[i] != 0) return length;
			else length--;
		}
		if (length == 0) {
			length ++;	
		}
		return length; 		
	}
	else return 0;
}

// Constructor
BigInt::BigInt(int x):len(1){
	num = new int[MAX_LEN];
	num[0] = x;
	for(int i=1;i<MAX_LEN;i++) num[i] = 0;
	if(x>0) sign = 1;
	else if(x<0) sign = -1;
	else sign = 0;
}
BigInt::BigInt(int nm[], int n, int sg):len(n),sign(sg){
	num = new int[MAX_LEN];
	memcpy(num, nm, sizeof(int)*n);
	for(int i=n;i<MAX_LEN;i++) num[i] = 0;
}

// Assigning Operator Overloading
BigInt & BigInt::operator=(const BigInt & b){
	if(num == b.num) return * this;
	if(num) delete [] num;
	if(b.num) {
		len = b.len;
		sign = b.sign;
		num = new int[MAX_LEN];
		memcpy(num, b.num, sizeof(int)*MAX_LEN);
	}
	else {
		num = NULL;
		len = 0;
		sign = 0;
	}
	return *this;
}

// <<
BigInt & BigInt::operator<<(int x){ // x is always non-negative
	if(x < 0) {
		cout << "can not use negative" << endl;
		return * this;
	}
	if(num){
		for(int i=len-1; i>=0; i--)	num[i+1] = num[i];
		num[0] = x;
		if(num[len] != 0) len++;
		return * this;		
	}
	else{
		num = new int[MAX_LEN];
		num[0] = x;
		len ++;
		if(x > 0) sign = 1;
		else sign = 0;
		return * this;
	}
}

// Compare
int BigInt::operator>(const BigInt & b){
	if(b.getNum() && getNum()){
		if(len > b.len) return 1;
		if(len < b.len) return -1;
		else{
			const int * an = getNum();
			const int * bn = b.getNum();
			for(int i=len-1;i>=0;i--){
				if(an[i] > bn[i]) return 1;
				if(an[i] < bn[i]) return -1;
			}
		}
		return 0;		
	}
	else {
		cout<<"Not comparable" << endl;
		return -100;
	}
}

// Add
BigInt BigInt::operator+(const BigInt & b){
	if(b.getNum() && getNum()){		
		if(getSign() == 0 && b.getSign() == 0) return BigInt(0);
//		if ( allNine() ) {
//			addOne(); 
//			return *this + b - BigInt(1);  	
//		}
		int sum[200] = {0};		
//		for(int i=0;i<MAX_LEN;i++) sum[i] = 0;
		const int * an = getNum();
		const int * bn = b.getNum();
		int len_max = max(getLen(), b.getLen()); 
		for(int i=0;i<len_max;i++){
			sum[i] += an[i] + bn[i];
			if(sum[i] >= 10){
				sum[i] -= 10;	
				sum[i+1] ++;
			}				
		}
		return BigInt(sum, intLen(sum), 1);
	}
	else return BigInt();
}

// subtract
BigInt BigInt::operator-(const BigInt & b){
	if(b.getNum() && getNum()){	
		int sub[MAX_LEN];
		const int * an;
		const int * bn;
		int len_max;
		for(int i=0;i<MAX_LEN;i++) sub[i] = 0;			
		int cmp = (*this > b);				
		if(cmp == 0) return BigInt(0);
		if(cmp == 1){			
			an = getNum();
			bn = b.getNum();
			len_max = getLen();
		}
		else{
			bn = getNum();
			an = b.getNum();
			len_max = b.getLen();
		}
		for(int i=0;i<len_max;i++){
			sub[i] += an[i] - bn[i];
			if(sub[i] < 0){
				sub[i] += 10;
				sub[i+1] --;
			}				
		}
		return BigInt(sub,intLen(sub),cmp);
	}
	else return BigInt();
}

// multiply
BigInt BigInt::operator*(const BigInt & b){
	if(b.getNum() && getNum()){	
		if(getSign() == 0 || b.getSign() == 0) return BigInt(0);
		int mul[MAX_LEN];
		const int * an = getNum();
		const int * bn = b.getNum();
		int len_a = getLen(); 
		int len_b = b.getLen();
		for(int i=0;i<MAX_LEN;i++) mul[i] = 0;							
		
		for(int i=0; i<len_a; i++){
			for(int j=0; j<len_b; j++){
				mul[j+i] += an[i]*bn[j] % 10;
				mul[j+i+1] += an[i]*bn[j] / 10;
				if(mul[j+i] >= 10){
					mul[j+i] -= 10;
					mul[j+i+1] ++;
				} 
				if(mul[j+i+1] >= 10){
					mul[j+i+1] -= 10;
					mul[j+i+2] ++;
				}
			}
		}						
		return BigInt(mul,intLen(mul),1);
	}
	else return BigInt();
}

// divide
BigInt BigInt::operator/(const BigInt & b){
	if(b.getNum() && getNum()){
		if (b.getSign() == 0 ){
				cout << "Not divisable" << endl;
				return BigInt();	
		}		
		int cmp = (*this > b);	
		if(cmp == -1) return BigInt(0);
		if(cmp == 0) return BigInt(1);		
		else {
			int div[MAX_LEN]; // result
			BigInt re(0); // reminder
			for(int i=0;i<MAX_LEN;i++) div[i] = 0;	
			const int * an = getNum();
			const int * bn = b.getNum();
			int len_a = getLen(); 
			int len_b = b.getLen();
			for(int i=len_a-1; i>=0; i--){
				re << an[i];
				while( (re > b) == -1 ){
					div[i] = 0;
					//cout << "i: " << i << " div: " << div[i] << endl;
					i--;
					re << an[i];					
				}
				//for(int i = re.getLen() -1; i >=0 ; i--) cout << re.getNum()[i]; cout<<endl;
				div[i] = bstDiv(re, b,1,9);
				//for(int i = re.getLen() -1; i >=0 ; i--) cout << re.getNum()[i]; cout<<endl;
				//cout << "i: " << i << " div: " << div[i] << endl;				
			}
			return BigInt(div,intLen(div),1);
		}		
	}
	else return BigInt();
}

// bstDiv()
int BigInt::bstDiv(BigInt & re, const BigInt & b, int lb, int ub){
	BigInt result;
	if((ub-lb) <= 1) {		
	 	result = BigInt(ub) * b; 
		if ((result > re) == 1){
			re = re - (BigInt(lb) * b);	
			//cout << "res " << lb << endl; 	
			return lb;
		}
		else{
			re = re - result;
			//cout << "res " << ub << endl; 				
			return ub;
		}
	}
	else{
		
		int mid = (lb + ub + 1)  / 2;
		//cout << " pros " << lb << ":" << mid << ":" << ub << endl; 		
		result = BigInt(mid) * b;
		int cmp = (result > re); 
		if( cmp == 0){
			re = re - result;
			return mid;			
		}
		if( cmp == 1 ) return bstDiv(re, b, lb, mid -1);
		if( cmp == -1 ) return bstDiv(re, b, mid, ub);   
	}
}

BigInt BigInt::MyInput(){
	if(num) delete [] num;
	char atemp[MAX_LEN];
	char tp;
	int itemp[MAX_LEN];
	gets(atemp);
	int k = strlen(atemp);
	for (int i=0;i<k;i++) {
		tp = atemp[i];
		itemp[k-1-i] = atoi(&tp);
	}	
	if(k==1 && itemp[0]==0) sign = 0;
	else sign = 1;
	return BigInt(itemp,k,sign);
} 

const int BigInt::MAX_LEN = 200;
const int BigInt::MAX_INP = 100;

int main(){
//	int an[2] = {2,1};
//	int bn[2] = {2,1};
//	BigInt a(an,sizeof(an)/sizeof(int),1),b(bn,sizeof(bn)/sizeof(int),1),c;
//	c = a*b;  	
	BigInt a,b,c;
	char choice[100]; 	
	a = a.MyInput();
	cin.getline(choice,10);	
	b = b.MyInput();
	
	if(*choice == '+') c = a + b;
	else if(*choice == '-') c = a - b;
	else if(*choice == '*') c = a * b;
	else if(*choice == '/') c = a/b;
	
	if (c.getSign() == -1) cout << "-";
	for(int i = c.getLen() -1; i >=0 ; i--) cout << c.getNum()[i]; cout<<endl;
	
//	cout << "a: " ;
//	for(int i = a.getLen() -1; i >=0 ; i--) cout << a.getNum()[i]; cout<<endl;
//	cout << "b: " ;
//	for(int i = b.getLen() -1; i >=0 ; i--) cout << b.getNum()[i]; cout<<endl;
//	cout << "c: "  ;
//	for(int i = c.getLen() -1; i >=0 ; i--) cout << c.getNum()[i]; cout<<endl;	
//	return 0;	
}






