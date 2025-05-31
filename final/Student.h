#pragma once
#include "User.h"
#include "Grade.h"

class Student : public User
{
private:
    MyVector<Grade> grades;
public:
    Student() = default;
    Student(const MyString& name, const MyString& familyName, const MyString& password);

    void reviewGrades();

    void printInfo() const override;
    User* clone() const override;

    void addGrade(const Grade& grade);
    void addGrade(Grade&& grade);

    void saveToFile(std::ofstream& ofs) const;
    void readFromFile(std::ifstream& ifs);
};



