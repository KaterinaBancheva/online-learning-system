#pragma once
#include "User.h"

class Teacher : public User
{
public:
    Teacher() = default;
    Teacher(const MyString& name, const MyString& familyName, const MyString& password);

    User* clone() const override;
    void printInfo() const override;
    ~Teacher() override = default;
};


