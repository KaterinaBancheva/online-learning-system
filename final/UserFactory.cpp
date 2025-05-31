#include "UserFactory.h"
#include <iostream>

User* UserFactory::createUser(std::ifstream& ifs)
{
    UserType type = UserType();
    ifs.read((char*)&type, sizeof(type));
    
    switch (type)
    {
    case UserType::admin:
        return createAdministrator(ifs);
    case UserType::student:
        return createStudent(ifs);
    case UserType::teacher:
        return createTeacher(ifs);
    }
}

Teacher* UserFactory::createTeacher(std::ifstream& ifs)
{
    Teacher* teacher = new Teacher();
    teacher->readFromFile(ifs);
    return teacher;
}

Student* UserFactory::createStudent(std::ifstream& ifs)
{
    Student* student = new Student();
    student->readFromFile(ifs);
    return student;
}

Administrator* UserFactory::createAdministrator(std::ifstream& ifs)
{
    Administrator* admin = new Administrator();
    admin->readFromFile(ifs);
    return admin;
}
