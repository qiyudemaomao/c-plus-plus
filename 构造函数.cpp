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
//#include"Tdate.h"     ���ļ��ṹ��Ҫ
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
//#include"Tdate.h"       ���ļ��ṹ��Ҫ
//#include<iostream>   ���ļ��ṹ��Ҫ
//using namespace std;   ���ļ��ṹ��Ҫ
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
//#include"student.h"    ���ļ��ṹ��Ҫ
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
//#include"Student.h"     ���ļ��ṹ��Ҫ
int main()
{
	int a,b,c,d;
	cin>>a>>b>>c>>d;
	Student s(a,b,c,d);
	s.out();
	return 0;
}