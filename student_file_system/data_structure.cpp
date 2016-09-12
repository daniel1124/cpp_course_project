#include <iostream>
#include <set>
using namespace std;


template<class T, class Pred = less<T> >
struct MySet{
	typedef typename set<T>::iterator iterator;
	set<T> * a;
	MySet(){}
	MySet(typename set<T>::iterator it1, typename set<T>::iterator it2){
		a = new set<T>(it1, it2);
	}
	pair<MySet<T>::iterator, MySet<T>::iterator> FindInterval(T s, T e){
		typename set<T>::iterator  it1 = a->upper_bound(s);
		typename set<T>::iterator  it2 = a->lower_bound(e);
		return make_pair(it1,it2);
	}
	void insert(T d){
		a->insert(d,Pred);
	}
	
	typename set<T>::iterator  upper_bound(T e){
		return a->upper_bound(e);
	}
	
};

template<class T>
void MyPrint(T iter1, T iter2){
	for(; iter1 != iter2; iter1++){
		cout << *iter1 << " ";
	}
}

int main()
{
	int t;
	cin >> t;
	MySet<int> stInt;
	int a[100];
	while(t--) {
		int n;
		cin >> n;
		for(int i = 0;i < n; ++i )
			cin >> a[i];
		MySet<int> stInt(a,a+n);
		MyPrint(stInt.begin(),stInt.end()); //输出全部内容
		cout << endl;
		int s,e;
		cin >> s >> e; // 后面要输出位于 s 和 e 之间的元素
		pair<MySet<int>::iterator, MySet<int>::iterator> p;
		p  = stInt.FindInterval(s,e);
		if( p.first != p.second) {
			MyPrint(p.first,p.second);
			cout << endl;
		}
		else
			cout << "Interval Not Found" << endl;
		cin >> n;
		MySet<double,greater<double> > stDouble;
		for( int i = 0;i < n; ++i)	{
			double d;
			cin >> d;
			stDouble.insert(d);
		}
		MyPrint(stDouble.begin(),stDouble.end());
		cout << endl;
		double w;
		cin >> w;
		cout << * stDouble.upper_bound(w) << endl;
	}
}
