// Student.h: interface for the Student class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STUDENT_H__D19CF61B_8E86_4734_9AE4_9040F150C7C9__INCLUDED_)
#define AFX_STUDENT_H__D19CF61B_8E86_4734_9AE4_9040F150C7C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<iostream>
using namespace std;
class Student  
{
public:
	Student(char *,int);
	virtual void disp(ostream &);
protected:
	char name[20];
	int score;
};

#endif // !defined(AFX_STUDENT_H__D19CF61B_8E86_4734_9AE4_9040F150C7C9__INCLUDED_)
