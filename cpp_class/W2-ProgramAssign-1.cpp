/* by Guo Wei
 个人习惯：类名和函数名首字母大写，变量名第一个单词小写，后面的单词首字母大写
 */
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;
class Student
{
private:
    static const int GRADES = 4; //只和Student相关的常量，写在 CStudent类内部比较好
    string name;
    int id;
    int age;
    int score[GRADES];
public:
    int Average();
    string GetName() { return name; }
    //返回值不要设成 string & ,哪怕是 const string & 也不太好，因为这样等于向外暴露了 name 属性，“隐藏”的效果不好了
    //虽然效率低了点，但面向对象的思想本来就会用程序的运行效率换取工程实现的效率以及可维护性，可重用性等。
    int GetId() { return id; }
    int GetAge() { return age; }
    void SetName( const string & name_) { name = name_; }
    void SetAge( int age_) { age = age_; }
    void SetId( int id_) { id = id_; }
    void SetScore(int score_[]) {
        memcpy(score,score_,sizeof(score));
    }
    void Init(const char *);
};
void Student::Init(const char * line)
{
	const char * p = strchr(line,','); //p指向line中的第一个  ','
	string s = line;
	name = s.substr(0,p-line); // substr(i,l)取从下标i开始，长度为 l 的子串
	sscanf(p + 1, "%d,%d,%d,%d,%d,%d",&age,&id,score,score+1,score+2,score+3); // p + 1 指向后面的年龄，学号等的字符串
}
int Student::Average() {
	int sum = 0;
	for( int i = 0;i < Student::GRADES; ++i )
		sum += score[i];
	return sum / Student::GRADES;
}
int main()
{
	Student stu;
	char line[200];
	gets(line);
	stu.Init(line);
	printf("%s,%d,%d,%d",stu.GetName().c_str(),stu.GetAge(),stu.GetId(),stu.Average());
	return 0;
}