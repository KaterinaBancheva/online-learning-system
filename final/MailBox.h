#pragma once
#include "Message.h"
#include "MyString.h"
#include "MyVector.hpp"

class MailBox
{
private:
	MyString user;
	MyVector<Message> messages;
public:
	MailBox() = default;

	void addMessage(const Message& mess);
	void showMessages() const;
	void clear();

	void saveFoFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);
};


