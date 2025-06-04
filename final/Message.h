#pragma once
#pragma warning (disable: 4996)
#include "MyString.h"
#include <ctime>

class Message
{
private:
	MyString sender;
	time_t timestamp;
	MyString content;
public:
	Message(); 
	Message(const MyString& content, const MyString& sender);
	void printMessage() const;

	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);
};



