#pragma once
#include "Teacher.h"
#include "Administrator.h"
#include "Student.h"

class LoggedUser
{
private:
	Administrator* adminPtr = nullptr;
	Student* studentPtr = nullptr;
	Teacher* teacherPtr = nullptr;
	User* ptr;
public: 
	LoggedUser();
	LoggedUser(User* userPtr);

	User* getPtr() const;
	UserType getUserType() const;
	
	Administrator* getAdminPtr() const;
	Teacher* getTeacherPtr() const;
	Student* getStudentPtr() const;

	void setAllPoinetersToNull();
};

