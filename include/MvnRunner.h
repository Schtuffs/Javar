#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

class MvnRunner {
private:
    bool mCompile, mRun;
    std::string mMainFile;

    std::filesystem::path CurrentPath(); 
    void SetPath(const std::filesystem::path& path);
    std::vector<std::string> ReadFolders();
    std::vector<std::string> ReadFiles();

public:
    MvnRunner();

    // Tells program to recompile project
    void SetCompile(bool value);
    // Allows for running without changes
    void SetRun(bool value);
    // Sets name of file containing "public static main void(String[] args){}"
    void SetMainFile(const std::string& filename);
    // Compiles program
    void Compile();
    // Runs program
    void Run();

    ~MvnRunner();
};

