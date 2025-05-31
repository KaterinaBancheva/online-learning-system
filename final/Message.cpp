#include "Message.h"
#include <iostream>

Message::Message() : timestamp(std::time(nullptr))
{
    sender = MyString();
    //timestamp = 0;
    content = MyString();
}

Message::Message(const MyString& content, const MyString& sender)
    :sender(sender), timestamp(std::time(nullptr)), content(content) {}


void Message::printMessage() const
{
    const char* timeStr = std::ctime(&timestamp); // Not thread-safe
    if (timeStr)
    {
        char timePart[9];
        std::strncpy(timePart, timeStr + 11, 8); // HH:MM:SS is at position 11–18
        timePart[8] = '\0';

        std::cout << timePart << ", sent by " << sender << ": " << content << std::endl;
    }
    else
    {
        std::cout << "Invalid time, sent by " << sender << ": " << content << std::endl;
    }

    //std::cout << ctime(&timestamp) << ", sent by " << sender << ': ' << content << std::endl;
}

void Message::saveToFile(std::ofstream& ofs) const
{
    sender.write(ofs);
    ofs.write((const char*)&timestamp, sizeof(timestamp));
    content.write(ofs);
}

void Message::readFromFile(std::ifstream& ifs)
{
    sender.read(ifs);
    ifs.read((char*)&timestamp, sizeof(timestamp));
    content.read(ifs);
}


