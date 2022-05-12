//////           Tdate.h     //
class Tdate
{
public:
	Tdate(int,int,int);
	~Tdate();
	void print();
private:
	int year;
	int month;
	int day;
};
//////        Student.h   //
//#include"Tdate.h"     多文件结构需要
#include<iostream>
using namespace std;
class Student
{
public:
	Student(int,int,int,int);
	~Student();
	void out();
private:
	int num;
	Tdate t;
};
///////           Tdate.cpp
//#include"Tdate.h"       多文件结构需要
//#include<iostream>   多文件结构需要
//using namespace std;   多文件结构需要
Tdate::Tdate(int a,int b,int c)
{
	year=a;
	month=b;
	day=c;
	cout<<"construct Tdate"<<endl;
}
Tdate::~Tdate()
{
	cout<<"distruct Tdate"<<endl;
}
void Tdate::print()
{
	cout<<year<<'/'<<month<<'/'<<day<<endl;
}
//////          Student.cpp
//#include"student.h"    多文件结构需要
Student::Student(int a,int b,int c,int d):t(b,c,d)
{
	num=a;
	cout<<"construct Student"<<endl;
}
Student::~Student()
{
	cout<<"distruct Student"<<endl;
}
void Student::out()
{
	cout<<num<<',';
	t.print();
}
///////        studate.cpp
//#include"Student.h"     多文件结构需要
int main()
{
	int a,b,c,d;
	cin>>a>>b>>c>>d;
	Student s(a,b,c,d);
	s.out();
	return 0;
}