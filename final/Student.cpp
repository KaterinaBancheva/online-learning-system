#include "Student.h"
#include <iostream>

Student::Student(const MyString& name, const MyString& familyName, const MyString& password) : User(name, familyName, password) 
{
    type = UserType::student;
};

void Student::reviewGrades()
{
    for (size_t i = 0; i < grades.getSize(); i++)
    {
        grades[i].printGrade();
    }
}

void Student::printInfo() const
{
    std::cout << name << ' ' << familyName << " | " << "Student | " << id << "\n";
}

User* Student::clone() const
{
    return new Student(*this);
}

void Student::addGrade(const Grade& grade)
{
    grades.push_back(grade);
}

void Student::addGrade(Grade&& grade)
{
    grades.push_back(std::move(grade));
}

void Student::saveToFile(std::ofstream& ofs) const
{
    User::saveToFile(ofs);
    size_t size = grades.getSize();
    ofs.write((const char*)&size, sizeof(size_t));
    for (size_t i = 0; i < size; i++)
    {
        grades[i].saveToFile(ofs);
    }
}

void Student::readFromFile(std::ifstream& ifs)
{
    User::readFromFile(ifs);
    size_t size = 0;
    ifs.read((char*)&size, sizeof(size_t));
    for (size_t i = 0; i < size; i++)
    {
        grades[i].readFromFile(ifs);
    }
}
