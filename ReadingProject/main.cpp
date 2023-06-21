#include "File.h"
#include <filesystem>

int main() {
    std::ofstream("test.txt"); // create file

    std::cout << "Created file with permissions: ";
    demo_perms(std::filesystem::status("test.txt").permissions());

    std::filesystem::permissions(
        "test.txt",
        std::filesystem::perms::owner_all | std::filesystem::perms::group_all,
        std::filesystem::perm_options::add
    );

    std::cout << "After adding u+rwx and g+rwx:  ";
    demo_perms(std::filesystem::status("test.txt").permissions());

    
    File file;
    file.userFile();
    std::cout << std::endl;
    file.messageFile();
    return 0;

}