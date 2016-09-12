#include <iostream>
#include <string>
using namespace std;

class Student {
	private:
		int id;
		static int count;
	public:
		static void InitCount(){
			count = 0;
		}
		Student(){count++;}
		Student(int idIn) {id = idIn; count++;}
		Student(const Student & st) {
			id = st.id;
			count ++;
		}
		~Student(){count--;}
	friend void PrintCount();
	friend void Print(Student);
};

int Student::count;
void PrintCount() {
	cout << "Total " << Student::count << " students" << endl;
}
void Print(Student s)
{
	cout << "the id is " << s.id << endl;
}

int main()
{
	Student::InitCount();
	Student s;
	PrintCount();
	Student s1(10);
	Student s2(s1);
	PrintCount();
	Print(s2);
	PrintCount();
	return 0;
}
