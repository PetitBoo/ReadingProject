#include "File.h"

void demo_perms(fs::perms p)
{
    std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
        << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
        << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
        << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
        << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
        << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
        << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
        << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
        << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
        << '\n';
}

void perms_group(int a)
{
    demo_perms(fs::status("Users.txt").permissions());
    switch (a) {
    case(1):
        fs::permissions("Users.txt", fs::perms::group_all);
    case(2):
        fs::permissions("Users.txt", fs::perms::group_write | fs::perms::group_read);
    case(3):
        fs::permissions("Users.txt", fs::perms::group_read);
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
            std::cout << "\tˆ¬ï: " << userName << "\t‹®£¨­: " << userLogin << "\t à®«ì: " << userPass << std::endl;
        }
        std::cout << std::endl;
        std::cout << "\tCurrently permission for Users.txt created: ";
        demo_perms(fs::status("Users.txt").permissions());
        fs::permissions("Users.txt",
            fs::perms::group_all | fs::perms::others_read,
            fs::perm_options::remove);
        
        int opt = 0;
        std::cout << "Do you want to stand new rights? Enter 1 - for rwx for group, 2 - for rw- for group, 3 - for r-- for group, 0 - for exit: ";
        std::cin >> opt;
       
        std::cout << "\tCurrently permission: ";
        demo_perms(fs::status("Users.txt").permissions());
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
        std::cout << "\t¥ ã¤ «®áì ®âªàëâì ä ©« Messages.txt" << std::endl;
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
        demo_perms(fs::status("Messages.txt").permissions());
        fs::permissions("Messages.txt",
            fs::perms::group_all | fs::perms::others_all,
            fs::perm_options::remove);

        std::cout << "\tCurrently permission: ";
        demo_perms(fs::status("Messages.txt").permissions());
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