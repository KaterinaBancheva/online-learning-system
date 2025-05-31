#include "Task.h"
#include <iostream>

Task::Task(const MyString& description)
{
	if (description.getSize() == 0)
	{
		throw std::invalid_argument("Invalid task description!");
	}

	this->description = description;
}

void Task::addAnswer(const Answer& answer)
{
	answers.push_back(answer);
}

void Task::addAnswer(Answer&& answer)
{
	answers.push_back(std::move(answer));
}

void Task::printTaskSubmissions() const
{
	if (answers.getSize() == 0)
	{
		std::cout << "There are no answers!";
		return;
	}

	std::cout << "All submissions: \n";
	for (size_t i = 0; i < answers.getSize(); i++)
	{
		answers[i].printAnswer();
		std::cout << std::endl;
	}
}

const MyString& Task::getDescription() const
{
	return description;
}

void Task::saveToFile(std::ofstream& ofs) const
{
	description.write(ofs);
	ofs.write((const char*)answers.getSize(), sizeof(size_t));
	for (size_t i = 0; i < answers.getSize(); i++)
	{
		answers[i].saveToFile(ofs);
	}
}

void Task::readFromFile(std::ifstream& ifs)
{
	description.read(ifs);
	size_t size = 0;
	ifs.read((char*)&size, sizeof(size_t));
	for (size_t i = 0; i < size; i++)
	{
		MyString answer;
		MyString student;
		student.read(ifs);
		answer.read(ifs);
		Answer ans = Answer(student, answer);
		answers.push_back(std::move(ans));
	}
}

