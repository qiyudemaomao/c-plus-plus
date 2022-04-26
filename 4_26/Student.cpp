// Student.cpp: implementation of the Student class.
//
//////////////////////////////////////////////////////////////////////

#include "Student.h"
#include<cstring>

Student::Student(char *p,int a)
{
	strcpy(name,p);
	score=a;
}
 
void Student::disp(ostream &out)
{
	out<<"name:"<<name<<','<<"score:"<<score<<endl;
}