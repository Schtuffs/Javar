#include "MvnRunner.h"

#include <fstream>
#include <sstream>
#include <string>

MvnRunner::MvnRunner() {
    this->mRun = false;
    this->mCompile = false;
    this->mMainFile = "Main";
}

MvnRunner::~MvnRunner() {
    // Nothing todo
}

void MvnRunner::SetCompile(bool value) {
    this->mCompile = value;
}

void MvnRunner::SetRun(bool value) {
    this->mRun = value;
}

void MvnRunner::SetMainFile(const std::string& filename) {
    this->mMainFile = filename;
}

void MvnRunner::Compile() {
    // Check if should recompile
    if (!this->mCompile) {
        return;
    }
    // Complex command to compile
    system("mvn clean package");
}

void MvnRunner::Run() {
    // Check if should run
    if (!this->mRun) {
        return;
    }

    // Get current path
    auto curPath = this->CurrentPath();

    // Check each for the main file
    std::ifstream file("pom.xml");
    std::string line, mainPath, begGroup = "<groupId>", endGroup = "</groupId>";

    // Incase xml is in strange order
    bool isDependency = false;

    // Open and read file, checking for groupId
    if (file.is_open()) {
        while (getline(file, line)) {
            // Ensure dependencies don't get set as main
            if (line.find("<dependency>") < line.length()) {
                isDependency = true;
                continue;
            }
            // End of dependency tag
            if (line.find("</dependency>") < line.length()) {
                isDependency = false;
                continue;
            }
            // Finds group tag, requires not dependency
            if (line.find(begGroup) < line.length() && !isDependency) {
                mainPath = line.substr(line.find(begGroup) + begGroup.length(), line.find(endGroup) - (endGroup.length() + 1));
                break;
            }
        }
        file.close();
    }

    // Add mainfile to path and then run
    mainPath += "." + this->mMainFile;
    std::string command = "java -cp ./target/* " + mainPath;
    system(command.c_str());
}

std::filesystem::path MvnRunner::CurrentPath() {
    return std::filesystem::current_path();
}

void MvnRunner::SetPath(const std::filesystem::path& path) {
    try {
        std::filesystem::current_path(path);
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cout << "Invalid path passed: " << path << std::endl;
    }
}

std::vector<std::string> MvnRunner::ReadFolders() {
    std::vector<std::string> folders;
    for(const auto& entry : std::filesystem::directory_iterator("./")) {
        if (entry.is_directory()) {
            folders.push_back(entry.path().string().substr(2));
        }
    }
    return folders;
}

std::vector<std::string> MvnRunner::ReadFiles() {
    std::vector<std::string> files;
    for(const auto& entry : std::filesystem::directory_iterator("./")) {
        std::string name = entry.path().string().substr(2);
        if (name.find('.')) {
            files.push_back(name);
        }
    }
    return files;
}

