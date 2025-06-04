#pragma once
#include "MyString.h"
#include "Mailbox.h"
#include <fstream>
#include "UserType.h"

class User
{
protected:
	static unsigned counter;
	MyString name;
	MyString familyName;
	unsigned id;
	MyString password;
	MailBox mail;
	UserType type;

	const MyString getPassword() const;

	void setName(const MyString& name);
	void setFamilyName(const MyString& familyName);
	void setPassword(const MyString& password);
	void confirmPassword(const MyString& password);
public:
	User();
	User(const User& other) = default;
	User(User&& other) = default;
	User(const MyString& name, const MyString& familyName, const MyString& password);

	const MyString& getName() const;
	const MyString& getFamilyName() const;
	UserType getType() const;
	unsigned getId() const;

	bool matchingPass(const MyString& password) const;

	void sendMessageTo(User* user, const Message& message);
	void receiveMessage(const Message& message);
	void checkMailbox() const;
	void changePassword(const MyString& password);

	virtual User* clone() const = 0;
	virtual void printInfo() const = 0;
	virtual ~User() = default;

	virtual void saveToFile(std::ofstream& ofs) const;
	virtual void readFromFile(std::ifstream& ifs);
};



