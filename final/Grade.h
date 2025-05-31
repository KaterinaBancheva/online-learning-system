#pragma once
#include "MyString.h"

class Grade
{
private:
	MyString course;
	MyString task;
	double grade;
	MyString description;
public:
	Grade() = default;
	Grade(const MyString& course, const MyString& task, double grade, const MyString& description);
	void printGrade() const;

	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);
};


