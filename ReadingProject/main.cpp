#include "File.h"
#include <filesystem>

int main() {
    File file;
    file.userFile();
    std::cout << std::endl;
    file.messageFile();
    return 0;
}