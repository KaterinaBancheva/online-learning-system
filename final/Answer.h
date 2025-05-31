#pragma once
#include "MyString.h"
#include <fstream>

class Answer
{
private:
	MyString student;
	MyString answer;
public:
	Answer() = default;
	Answer(const MyString& student, const MyString& answer);
	void printAnswer() const;

	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);
};
