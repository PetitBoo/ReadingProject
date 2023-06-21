#pragma once
#include<fstream>
#include<vector>
#include<string>
#include <sstream>
#include"User.h"
#include"Message.h"
#include <filesystem>

void demo_perms(std::filesystem::perms p);

class File {
    std::vector<User> _users;
    std::vector<Message> _messages;

public:
    File();
    ~File();
    int userFile();
    int messageFile();
};