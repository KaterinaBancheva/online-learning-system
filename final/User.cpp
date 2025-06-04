#include "User.h"
#include <iostream>

unsigned User:: counter = 0;

const MyString User::getPassword() const
{
    return password;
}

void User::setName(const MyString& name)
{
    if (name.getSize() == 0)
    {
        throw std::invalid_argument("Invalid name!");
    }

    this->name = name;
}

void User::setFamilyName(const MyString& familyName)
{
    if (familyName.getSize() == 0)
    {
        throw std::invalid_argument("Invalid family name!");
    }

    this->familyName = familyName;
}

void User::setPassword(const MyString& password)
{
    if (password.getSize() < 4)
        throw std::invalid_argument("Invalid password!");

    //confirmPassword(password);
    this->password = password;
}

void User::confirmPassword(const MyString& password)
{
    MyString toConfirm;
    std::cin >> toConfirm;
    if (toConfirm == password)
        this->password = password;
    else
        throw std::logic_error("Password not confirmed!");
}

User::User()
{
    id = 0;
    name = nullptr;
    familyName = nullptr;
    password = nullptr;
}
User::User(const MyString& name, const MyString& familyName, const MyString& password)
{
    id = counter++;
    setName(name);
    setFamilyName(familyName);
    setPassword(password);
}

const MyString& User::getName() const
{
    return name;
}

const MyString& User::getFamilyName() const
{
    return familyName;
}

UserType User::getType() const
{
    return type;
}

unsigned User::getId() const
{
    return id;
}

bool User::matchingPass(const MyString& password) const
{
    return this->password == password;
}

void User::sendMessageTo(User* user, const Message& message)
{
    user->receiveMessage(message);
}

void User::receiveMessage(const Message& message)
{
    mail.addMessage(message);
    std::cout << "Message sent to " << getName() << " " << getFamilyName() << "! \n";
}

void User::checkMailbox() const
{
    mail.showMessages();
}

void User::changePassword(const MyString& password)
{
    std::cout << "Enter current password: ";
    MyString pass;
    std::cin >> pass;
    if (getPassword() == pass)
    {
        setPassword(password);
        std::cout << "Password changed! \n";
    }
    else
    {
        std::cout << "Incorrect password! \n";
    }
}

void User::saveToFile(std::ofstream& ofs) const
{
    ofs.write((const char*)&type, sizeof(type));
    name.write(ofs);
    familyName.write(ofs);
    ofs.write((const char*)&id, sizeof(id));
    password.write(ofs);
    mail.saveFoFile(ofs);
}

void User::readFromFile(std::ifstream& ifs)
{
    ifs.read((char*)&type, sizeof(type));
    name.read(ifs);
    familyName.read(ifs);
    ifs.read((char*)&id, sizeof(id));
    password.read(ifs);
    mail.readFromFile(ifs);
}
