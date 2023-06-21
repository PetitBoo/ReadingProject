#include "File.h"

void demo_perms(std::filesystem::perms p)
{
    using std::filesystem::perms;
    auto show = [=](char op, perms perm)
    {
        std::cout << (perms::none == (perm & p) ? '-' : op);
    };
    show('r', perms::owner_read);
    show('w', perms::owner_write);
    show('x', perms::owner_exec);
    show('r', perms::group_read);
    show('w', perms::group_write);
    show('x', perms::group_exec);
    show('r', perms::others_read);
    show('w', perms::others_write);
    show('x', perms::others_exec);
    std::cout << '\n';
}

void perms_group(int a)
{
    demo_perms(std::filesystem::status("Users.txt").permissions());
    switch (a) {
    case(1):
        std::filesystem::permissions("Users.txt", std::filesystem::perms::group_all);
    case(2):
        std::filesystem::permissions("Users.txt", std::filesystem::perms::group_write | std::filesystem::perms::group_read);
    case(3):
        std::filesystem::permissions("Users.txt", std::filesystem::perms::group_read);
    default:
        break;
    }
}

File::File() {};
File::~File() = default;

int File::userFile() {

    std::fstream users_file = std::fstream("Users.txt", std::ios::in | std::ios::out);

    if (!users_file)
    {
        users_file = std::fstream("Users.txt", std::ios::in | std::ios::out | std::ios::trunc);
    }

    if (!users_file.is_open())
    {
        std::cout << "\tCannot open Users.txt" << std::endl;
        return -1;
    }
    else
    {
        int a = 1;
        while (a != 0)
        {
            std::string name;
            std::string login;
            std::string pass;

            std::cout << "Enter name or 0 for exit:";
            std::cin >> name;
            if (name == "0") {
                a = 0;
                break;
            }
            std::cout << "Enter login:";
            std::cin >> login;
            std::cout << "Enter password:";
            std::cin >> pass;
            _users.emplace_back(name, login, pass);
        }
        _users.emplace_back("Claire", "Redfield", "Racoon");
        _users.emplace_back("Leon", "LSK", "Kennedy");
        _users.emplace_back("Jill", "JillValentine", "45613");
        _users.emplace_back("Chris", "RockLover", "Redfiiiiield");

        for (auto& user : _users)
        {
            users_file << user << std::endl;
        }
        std::cout << "\tAll users from User.txt:" << std::endl;

        users_file.seekg(0, std::ios::beg);

        std::string userName, userLogin, userPass;
        std::string line;

        std::cout << std::endl;
        while (getline(users_file, line))
        {
            std::istringstream input{ line };
            getline(input, userName, ';');
            getline(input, userLogin, ';');
            getline(input, userPass);
            std::cout << "\tName: " << userName << "\tLogin: " << userLogin << "\tPassword: " << userPass << std::endl;
        }
        std::cout << std::endl;
        std::cout << "\tCurrently permission for Users.txt created: ";
        demo_perms(std::filesystem::status("Users.txt").permissions());
        std::filesystem::permissions("Users.txt",
            std::filesystem::perms::owner_all | std::filesystem::perms::group_all,
            std::filesystem::perm_options::add);
        
        int opt = 0;
        std::cout << "Do you want to stand new rights? Enter 1 - for rwx for group, 2 - for rw- for group, 3 - for r-- for group, 0 - for exit: ";
        std::cin >> opt;
       
        std::cout << "\tCurrently permission: ";
        demo_perms(std::filesystem::status("Users.txt").permissions());
    }
    return 0;
}

int File::messageFile() {
    std::fstream messages_file = std::fstream("Messages.txt", std::ios::in | std::ios::out);
    if (!messages_file)
    {
        messages_file = std::fstream("Messages.txt", std::ios::in | std::ios::out | std::ios::trunc);
    }
    if (!messages_file.is_open())
    {
        std::cout << "\tCannot open Messages.txt" << std::endl;
        return -1;
    }
    else
    {
        _messages.emplace_back("Hi!", "Claire", "Jill");
        _messages.emplace_back("Hello! How are you?", "Jill", "Claire");
        _messages.emplace_back("I'm fine!", "Claire", "Jill");
        _messages.emplace_back("what do you think about rocks?", "Chris", "Jill");
        _messages.emplace_back("NOTHING!", "Jill", "Chris");
        for (auto& message : _messages)
        {
            messages_file << message << std::endl;
        }
        std::cout << std::endl;
        std::cout << "\tAll data from Messages.txt:" << std::endl;
        std::cout << std::endl;
        messages_file.seekg(0, std::ios::beg);
        std::string messageText, messageSender, messageReceiver;
        std::string line;

        while (getline(messages_file, line))
        {
            std::istringstream input{ line };
            getline(input, messageText, ';');
            getline(input, messageSender, ';');
            getline(input, messageReceiver);
            std::cout << "\t(from) " << messageSender << "\t(for) " << messageReceiver << "\t(message) " << messageText << std::endl;
        }
        std::cout << std::endl;
        std::cout << "\tCurrently permission for Users.txt created: ";
        demo_perms(std::filesystem::status("Messages.txt").permissions());
        std::filesystem::permissions("Messages.txt",
            std::filesystem::perms::group_write | std::filesystem::perms::group_read,
            std::filesystem::perm_options::remove);

        std::cout << "\tCurrently permission: ";
        demo_perms(std::filesystem::status("Messages.txt").permissions());
    }
    return 0;
}

std::ostream& operator <<(std::ostream& os, Message& message)
{
    os << message._text;
    os << ';';
    os << message._sender;
    os << ';';
    os << message._receiver;
    return os;
}
std::ostream& operator <<(std::ostream& os, User& user)
{
    os << user._name;
    os << ';';
    os << user._login;
    os << ';';
    os << user._pass;
    return os;
}