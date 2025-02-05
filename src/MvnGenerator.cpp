#include "MvnGenerator.h"

#include <algorithm>
#include <filesystem>
#include <Windows.h>

MvnGenerator::MvnGenerator() {
    this->mArchetype = "maven-archetype-quickstart -DarchetypeVersion=1.5";
    this->mCompany = "com.schtuffs.project";
    this->mProjectName = "Project";
    this->mGenerate = false;
}

MvnGenerator::~MvnGenerator() {
    // Nothing todo
}

bool MvnGenerator::SetCompany(const std::string& company) {
    if (std::count(company.begin(), company.end(), '.') != 2 || company.length() == 0) {
        std::cout << "Not proper company\nTry format \"com.company.app-name\" or `com.company.app-name";
        return false;
    }
    this->mCompany = company;
    std::cout << "Company set to: " << this->mCompany << std::endl;
    this->mGenerate = true;
    return true;
}

bool MvnGenerator::SetProjectName(const std::string& name) {
    this->mProjectName = name;
    std::cout << "Project name set to: " << this->mProjectName << std::endl;
    this->mGenerate = true;
    return true;
}

bool MvnGenerator::SetArchetype(const std::string& archetype) {
    this->mArchetype = archetype;
    std::cout << "Archetype set to: " << this->mArchetype << std::endl;
    this->mGenerate = true;
    return true;
}

void MvnGenerator::SetGenerate(bool value) {
    this->mGenerate = value;
}

void MvnGenerator::Generate() {
    // Check if project should be generated
    if (!this->mGenerate) {
        return;
    }

    // Add all commands into string
    std::string command = "mvn archetype:generate -DgroupId=" + this->mCompany + " -DartifactId=" + this->mProjectName + " -DjavaCompilerVersion=23 -DarchetypeArtifactId=" + this->mArchetype + " -DinteractiveMode=false";
	system(command.c_str());

    // Set directory into project incase also compiling and running
    // Does not change console directory
    std::filesystem::current_path(this->mProjectName);
}

