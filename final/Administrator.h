#pragma once
#include "User.h"

class Administrator : public User
{
public:
    Administrator();
    Administrator(const MyString& name, const MyString& familyName);

    void setPassword(const MyString& pass);
    void setId();
    void setNames(const MyString& name, const MyString& familyName);

    User* clone() const override;
    void printInfo() const override;
    ~Administrator() override = default;
};



