#pragma once
#include "MyVector.hpp"
#include "Answer.h"
#include <fstream>

class Task
{
private:
	MyString description;
	MyVector<Answer> answers;
public:
	Task() = default;
	Task(const MyString& description);

	void addAnswer(const Answer& answer); 
	void addAnswer(Answer&& answer); 

	void printTaskSubmissions() const;
	const MyString& getDescription() const;

	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);
};



