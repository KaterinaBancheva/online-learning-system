#include "LoggedUser.h"

LoggedUser::LoggedUser()
{
	ptr = nullptr;
}

LoggedUser::LoggedUser(User* userPtr)
{
	ptr = userPtr;
	if (userPtr->getType() == UserType::admin)
		adminPtr = dynamic_cast<Administrator*>(userPtr);
	else if (userPtr->getType() == UserType::teacher)
		teacherPtr = dynamic_cast<Teacher*>(userPtr);
	else if (userPtr->getType() == UserType::student)
		studentPtr = dynamic_cast<Student*>(userPtr);

}

User* LoggedUser::getPtr() const
{
	return ptr;
}

UserType LoggedUser::getUserType() const
{
	if (adminPtr != nullptr)
		return UserType::admin;
	else if (studentPtr != nullptr)
		return UserType::student;
	else if (teacherPtr != nullptr)
		return UserType::teacher;
	else
		throw std::logic_error("No logged user!");
}

Administrator* LoggedUser::getAdminPtr() const
{
	return adminPtr;
}

Teacher* LoggedUser::getTeacherPtr() const
{
	return teacherPtr;
}

Student* LoggedUser::getStudentPtr() const
{
	return studentPtr;
}

void LoggedUser::setAllPoinetersToNull()
{
	adminPtr == nullptr;
	studentPtr = nullptr;
	teacherPtr = nullptr;
}
