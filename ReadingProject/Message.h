#pragma once
#include <string>
#include <iostream>

class Message
{
public:
    Message(const std::string& text, const std::string& sender, const std::string& receiver)
        : _text(text), _sender(sender), _receiver(receiver) {}

    friend std::ostream& operator <<(std::ostream& os, Message& message);

private:
    std::string _text;
    std::string _sender;
    std::string _receiver;
};