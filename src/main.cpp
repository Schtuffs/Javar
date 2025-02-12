#include <iostream>
#include <vector>
#include <string>

#include "MvnGenerator.h"
#include "MvnRunner.h"

#define CODE_INVALID    -1
#define VERSION         "1.3"

// Changes the args to strings
std::vector<std::string> Parse(int argc, char** argv) {
    std::vector<std::string> args;
    for (int i = 1; i < argc; i++) {
        args.push_back(argv[i]);
    }
    return args;
}

// Check for command in args, returns the index
// Returns CODE_INVALID if index not found
int HasCommand(const std::vector<std::string>& args, const std::string& command, const std::string& deliminator = " ") {
    for (int i = 0; i < (int)(args.size()); i++) {
        std::string arg = args[i].substr(0, args[i].find(deliminator));
        if (arg.compare(command) == 0) {
            return i;
        }
    }
    return CODE_INVALID;
}

// Version info
void Version() {
    std::cout << "\nVersion " << VERSION << "\n";
    std::cout << "Can either generate a new maven project or run one\n";
    std::cout << "Allows quick start with basic maven project without needing\n";
    std::cout << "to look up the command for it\n";
    std::cout << "\n";
}

// Print help menu
void Help() {
    std::cout << "\n    Commands\n";
    std::cout << "\n    Generation\n";
    std::cout << "-h            Prints this menu\n";
    std::cout << "-v            Prints the program version\n";
    std::cout << "-company=     Company name, set with arg after '='\n";
    std::cout << "-name=        Name of the project, set with arg after '='\n";
    std::cout << "-archetype=   Specific archetype to use, set with arg after '='\n";
    std::cout << "              Recommended to leave untouched\n";
    std::cout << "-g            Generates the files, allows running with no changes\n";
    std::cout << "\n    Running\n";
    std::cout << "-c            Compiles the maven project in the current directory\n";
    std::cout << "-r            Runs the maven project in the current directory\n";
    std::cout << "              Must add the file containing static main method\n";
    std::cout << "              Add as last argument to default to Main\n";
    std::cout << std::endl;
}

// Perform the command line arguments
// Returns true if files should be created
void ParseCommands(MvnGenerator& mvnGenerator, MvnRunner& mvnRunner, std::vector<std::string>& args) {
    // Each check
    int index = CODE_INVALID;

    // Version info
    if ((index = HasCommand(args, "-v")) != CODE_INVALID) {
        Version();
    }

    // Help menu
    if ((index = HasCommand(args, "-h")) != CODE_INVALID || args.size() == 0) {
        Help();
    }

    // ----- Generation -----

    // Generate
    if ((index = HasCommand(args, "-g") != CODE_INVALID)) {
        mvnGenerator.SetGenerate(true);
    }

    // Company
    if ((index = HasCommand(args, "-company", "=")) != CODE_INVALID) {
        // Make substring with only user arg 
        std::string arg = args[index];
        arg = arg.substr(arg.find('=') + 1);

        // Fixes powershell parsing
        if (arg.find('.') > arg.length()) {
            arg += args[index + 1];
        }

        mvnGenerator.SetCompany(arg);
    }

    // Project name
    if ((index = HasCommand(args, "-name", "=")) != CODE_INVALID) {
        // Make substring with only user arg
        std::string arg = args[index];
        arg = arg.substr(arg.find('=') + 1);

        mvnGenerator.SetProjectName(arg);
    }
    // Archetype
    if ((index = HasCommand(args, "-archetype", "=")) != CODE_INVALID) {
        // Make substring with only user arg
        std::string arg = args[index];
        arg = arg.substr(arg.find('=') + 1);

        mvnGenerator.SetArchetype(arg);
    }

    // ----- Running -----

    // Compile
    if ((index = HasCommand(args, "-c")) != CODE_INVALID) {
        mvnRunner.SetCompile(true);
    }
    // Run
    if ((index = HasCommand(args, "-r")) != CODE_INVALID) {
        // Determine 
        if ((size_t)index < args.size() - 1) {
            std::string mainMethod = args[index + 1];
            mvnRunner.SetMainFile(mainMethod);
        }
        mvnRunner.SetRun(true);
    }
    // Compile and Run
    if ((index = HasCommand(args, "-cr")) != CODE_INVALID) {
        // Determine 
        if ((size_t)index < args.size() - 1) {
            std::string mainMethod = args[index + 1];
            mvnRunner.SetMainFile(mainMethod);
        }
        mvnRunner.SetCompile(true);
        mvnRunner.SetRun(true);
    }
}

int main(int argc, char** argv) {
    auto args = Parse(argc, argv);
    MvnGenerator mvnGenerator;
    MvnRunner mvnRunner;

    ParseCommands(mvnGenerator, mvnRunner, args);

    // Perform specified actions
    mvnGenerator.Generate();
    mvnRunner.Compile();
    mvnRunner.Run();

    return 0;
}
