#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void listFiles(const fs::path& directory) {
    for (const auto& entry : fs::directory_iterator(directory)) {
        std::cout << entry.path().filename() << std::endl;
    }
}

void createDirectory(const fs::path& directory) {
    if (!fs::exists(directory)) {
        fs::create_directory(directory);
        std::cout << "Directory created: " << directory << std::endl;
    } else {
        std::cout << "Directory already exists: " << directory << std::endl;
    }
}

void copyFile(const fs::path& source, const fs::path& destination) {
    if (fs::exists(source)) {
        fs::copy_file(source, destination, fs::copy_options::overwrite_existing);
        std::cout << "File copied: " << destination << std::endl;
    } else {
        std::cout << "Source file does not exist: " << source << std::endl;
    }
}

void moveFile(const fs::path& source, const fs::path& destination) {
    if (fs::exists(source)) {
        fs::rename(source, destination);
        std::cout << "File moved: " << destination << std::endl;
    } else {
        std::cout << "Source file does not exist: " << source << std::endl;
    }
}

int main() {
    fs::path currentDir = fs::current_path();
    std::string command;

    while (true) {
        std::cout << "Current directory: " << currentDir << std::endl;
        std::cout << "Enter command (ls, mkdir, cp, mv, exit): ";
        std::cin >> command;

        if (command == "ls") {
            listFiles(currentDir);
        } else if (command == "mkdir") {
            std::string dirName;
            std::cin >> dirName;
            createDirectory(currentDir / dirName);
        } else if (command == "cp") {
            std::string source, destination;
            std::cin >> source >> destination;
            copyFile(currentDir / source, currentDir / destination);
        } else if (command == "mv") {
            std::string source, destination;
            std::cin >> source >> destination;
            moveFile(currentDir / source, currentDir / destination);
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Invalid command. Try again." << std::endl;
        }
    }return 0;
}