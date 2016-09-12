#include<iostream>
using namespace std;

template <class T>
class CArray3D{
	private:
		int dim1,dim2,dim3;
		T ***p;
	public:
		CArray3D(int d1, int d2, int d3):dim1(d1),dim2(d2),dim3(d3){
			p = new T**[dim1];
			for(int i=0; i<dim1; i++){
				p[i] = new T*[dim2];
				for(int j=0; j<dim2; j++){
					p[i][j] = new T[dim3];
				}
			}
		}
		T** operator[](int i){
			return p[i];
		}		
};


int main()
{

	CArray3D<int> a(3,4,5);
	
	int No = 0;
	
	for( int i = 0; i < 3; ++ i )		
		for( int j = 0; j < 4; ++j )
			for( int k = 0; k < 5; ++k )	
				a[i][j][k] = No ++;
	
	for( int i = 0; i < 3; ++ i )
		for( int j = 0; j < 4; ++j )
			for( int k = 0; k < 5; ++k )
				cout << a[i][j][k] << ",";
	
	return 0;

}

//��ʾ����������Զ����࣬��ģ������Ҳ���Զ�����ģ�档���磺
class A
{
	class B {                     

	};            
}; 

template <class T>
class S
{
	T x;
	class K {
		T a;
	};
};
