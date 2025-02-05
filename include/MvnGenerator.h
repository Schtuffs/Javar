#pragma once
#include <iostream>
#include <string>

class MvnGenerator {
private:
    std::string mArchetype, mProjectName, mCompany;
    bool mGenerate;


public:
    MvnGenerator();

    // Sets company for the filesystem
    bool SetCompany(const std::string& company);
    // Name of the project being created
    bool SetProjectName(const std::string& name);
    // May change to have some archetypes
    bool SetArchetype(const std::string& archetype);
    // Allows running
    void SetGenerate(bool value);
    // Generates project
    void Generate();

    ~MvnGenerator();
};

