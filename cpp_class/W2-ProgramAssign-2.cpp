//szewa 同学的代码
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
class CStudent {
private:
    char name[100], number[100];
    int age, mark_1, mark_2, mark_3, mark_4;
public:
    void setName(char * x);
    void getName(char * x);
    void setAge(int x);
    void getAge(int * x);
    void setNumber(char * x);
    void getNumber(char * x);
    void setMark(int x, int year);
    void getMark(int *x, int year);
    int getAverageMark();
};
void CStudent::setName(char * x) {
	strcpy(name, x);
}
void CStudent::getName(char * x) {
	strcpy(x, name);
}
void CStudent::setAge(int x) {
	age = x;
}
void CStudent::getAge(int * x) {
	* x = age;
}
void CStudent::setNumber(char * x) {
	strcpy(number, x);
}
void CStudent::getNumber(char * x) {
	strcpy(x, number);
}
void CStudent::setMark(int x, int year) {
	if      (year == 1) mark_1 = x;
	else if (year == 2) mark_2 = x;
	else if (year == 3) mark_3 = x;
	else if (year == 4) mark_4 = x;
}
void CStudent::getMark(int * x, int year) {
	if      (year == 1) *x = mark_1;
	else if (year == 2) *x = mark_2;
	else if (year == 3) *x = mark_3;
	else if (year == 4) *x = mark_4;
}
int CStudent::getAverageMark() {
	return (mark_1+mark_2+mark_3+mark_4)/4;
}

int main() {
	CStudent student1;
	char temp1[100];
	int temp2;
	int mean_mark;
	
	// input
	cin.getline(temp1, 100, ',');
	student1.setName(temp1);
	cin.getline(temp1, 100, ',');
	student1.setAge(strtol(temp1,0,10));
	cin.getline(temp1, 100, ',');
	student1.setNumber(temp1);
	cin.getline(temp1, 100, ',');
	student1.setMark(strtol(temp1,0,10),1);
	cin.getline(temp1, 100, ',');
	student1.setMark(strtol(temp1,0,10),2);
	cin.getline(temp1, 100, ',');
	student1.setMark(strtol(temp1,0,10),3);
	cin.getline(temp1, 100);
	student1.setMark(strtol(temp1,0,10),4);
	
	// Calculate average mark
	mean_mark = student1.getAverageMark();
	
	// output
	student1.getName(temp1);
	cout << temp1 << ',';
	student1.getAge(&temp2);
	cout << temp2 << ',';
	student1.getNumber(temp1);
	cout << temp1 << ',';
	cout << mean_mark <<endl;
	
	return 0;
}
