#pragma once
#include "User.h"
#include "Teacher.h"
#include "Administrator.h"
#include "Student.h"
#include <fstream>

class UserFactory
{
public:
	static User* createUser(std::ifstream& ifs);
private:
	static Teacher* createTeacher(std::ifstream& ifs);
	static Student* createStudent(std::ifstream& ifs);
	static Administrator* createAdministrator(std::ifstream& ifs);
};

