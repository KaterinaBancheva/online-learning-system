#include "Administrator.h"
#include <iostream>

Administrator::Administrator() : Administrator("Admin", "Profile")
{ };

Administrator::Administrator(const MyString& name, const MyString& familyName)
	: User(" ", " ", "0000")
{
	type = UserType::admin;
}

void Administrator::setPassword(const MyString& pass)
{
	password = pass;
}

void Administrator::setId()
{
	id = 0;
}

User* Administrator::clone() const
{
	return new Administrator(*this);
}

void Administrator::printInfo() const
{
	std::cout << name << ' ' << familyName << " | " << "Administrator | " << id << "\n";
}
