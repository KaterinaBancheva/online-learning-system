#include "Teacher.h"
#include <iostream>

Teacher::Teacher(const MyString& name, const MyString& familyName, const MyString& password)
	: User(name, familyName, password) 
{
	type = UserType::teacher;
}

User* Teacher::clone() const
{
	return new Teacher(*this);
}

void Teacher::printInfo() const
{
	std::cout << name << ' ' << familyName << " | " << "Teacher | " << id << "\n";
};











