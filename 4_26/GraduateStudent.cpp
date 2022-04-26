// GraduateStudent.cpp: implementation of the GraduateStudent class.
//
//////////////////////////////////////////////////////////////////////

#include "GraduateStudent.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GraduateStudent::GraduateStudent(char *p,int a,char *q):Student(p,a)
{
	strcpy(tname,q);
}

void GraduateStudent::disp(ostream &out)
{
	out<<"name:"<<name<<','<<"score:"<<score<<','<<"Teacher:"<<tname<<endl;
}