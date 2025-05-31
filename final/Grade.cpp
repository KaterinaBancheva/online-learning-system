#include "Grade.h"
#include <iostream>

Grade::Grade(const MyString& course, const MyString& task, double grade, const MyString& description)
{
	this->course = course;
	this->task = task;
	this->grade = grade;
	this->description = description;
}

void Grade::printGrade() const
{
	std::cout << course << " | " << task << ' | ' << grade << ' | ' << description << std::endl;
}

void Grade::saveToFile(std::ofstream& ofs) const
{
	course.write(ofs);
	task.write(ofs);
	ofs.write((const char*)&grade, sizeof(double));
	description.write(ofs);
}

void Grade::readFromFile(std::ifstream& ifs)
{
	course.read(ifs);
	task.read(ifs);
	ifs.read((char*)&grade, sizeof(double));
	description.read(ifs);
}
