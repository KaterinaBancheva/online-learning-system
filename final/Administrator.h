#pragma once
#include "User.h"

class Administrator : public User
{
public:
    Administrator();
    Administrator(const MyString& name, const MyString& familyName);

    User* clone() const override;
    void printInfo() const override;
};



