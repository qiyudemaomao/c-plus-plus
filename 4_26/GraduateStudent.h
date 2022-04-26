// GraduateStudent.h: interface for the GraduateStudent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRADUATESTUDENT_H__539434EF_6CB7_490B_A2D8_243603451A42__INCLUDED_)
#define AFX_GRADUATESTUDENT_H__539434EF_6CB7_490B_A2D8_243603451A42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include"Student.h"

class GraduateStudent: public Student  
{
public:
	GraduateStudent(char *,int ,char *);
	void disp(ostream &);
protected:
	char tname[20];
};

#endif // !defined(AFX_GRADUATESTUDENT_H__539434EF_6CB7_490B_A2D8_243603451A42__INCLUDED_)
