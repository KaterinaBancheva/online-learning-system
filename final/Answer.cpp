#include "Answer.h"
#include <iostream>

Answer::Answer(const MyString& student, const MyString& answer)
{
	if (answer.getSize() == 0)
	{
		throw std::invalid_argument("Invalid answer!");
	}

	if (student.getSize() == 0)
	{
		throw std::invalid_argument("Invalid sstudent!");
	}

	this->answer = answer;
	this->student = student;
}

void Answer::printAnswer() const
{
	std::cout << student << ' ' << answer << '\n';;
}

void Answer::saveToFile(std::ofstream& ofs) const
{
	student.write(ofs);
	answer.write(ofs);
}

void Answer::readFromFile(std::ifstream& ifs)
{
	student.read(ifs);
	answer.read(ifs);
}
