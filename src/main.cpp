#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "shell/shell.h"

int main(int argc, char** argv) {
    Shell shell = Shell();

    // parse arguments into vector
    auto args = std::vector<std::string>();
    for (int i = 1; i < argc; i++)
        args.push_back(argv[i]);
    
    std::cout << shell.run(args) << std::endl;

    return 0;
}
