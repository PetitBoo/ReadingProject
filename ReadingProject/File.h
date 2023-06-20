#pragma once
#include<fstream>
#include<vector>
#include<string>
#include <sstream>
#include"User.h"
#include"Message.h"
#include <filesystem>

namespace fs = std::filesystem;

void demo_perms(fs::perms p);
void perms_group(int a);

class File {
    std::vector<User> _users;
    std::vector<Message> _messages;

public:
    File();
    ~File();
    int userFile();
    int messageFile();
};