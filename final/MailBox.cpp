#include "MailBox.h"

void MailBox::addMessage(const Message& mess)
{
	messages.push_back(mess);
}

void MailBox::showMessages() const
{
	for (size_t i = 0; i < messages.getSize(); i++)
	{
		messages[i].printMessage();
	}
}

void MailBox::clear()
{
	messages.clear();
}

void MailBox::saveFoFile(std::ofstream& ofs) const
{
	user.write(ofs);
	size_t size = messages.getSize();
	ofs.write((const char*)&size, sizeof(size));

	for (size_t i = 0; i < messages.getSize(); i++)
	{
		messages[i].saveToFile(ofs);
	}
}

void MailBox::readFromFile(std::ifstream& ifs)
{
	user.read(ifs);
	size_t size = 0;
	ifs.read((char*)&size, sizeof(size));

	for (size_t i = 0; i < size; i++)
	{
		Message temp(" ", " ");
		temp.readFromFile(ifs);
		messages.push_back(std::move(temp));
	}
}

	