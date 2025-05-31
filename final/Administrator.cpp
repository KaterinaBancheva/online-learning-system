#include "Administrator.h"
#include <iostream>

Administrator::Administrator() : Administrator("Admin", "Profile")
{ };

Administrator::Administrator(const MyString& name, const MyString& familyName)
	: User(name, familyName, "0000")
{
	type = UserType::admin;
}

User* Administrator::clone() const
{
	return new Administrator(*this);
}

void Administrator::printInfo() const
{
	std::cout << name << ' ' << familyName << " | " << "Administrator | " << id << "\n";
}
