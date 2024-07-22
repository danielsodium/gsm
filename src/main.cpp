#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "shell/shell.h"

int main(int argc, char** argv) {

    if (argc == 1) return 0;

    Shell shell = Shell();

    // parse arguments into vector
    auto args = std::vector<std::string>();
    for (int i = 1; i < argc; i++)
        args.push_back(argv[i]);
    
    std::cout << shell.run(args).dump() << std::endl;

    return 0;
}
