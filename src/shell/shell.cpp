#include "shell.h"
#include <fstream>
#include <filesystem>

Shell::Shell(std::string path) {
    // Replace later with default config
    config = path;

    for (const auto & entry : std::filesystem::directory_iterator(config))
        sessions.insert(std::make_pair(entry.path().stem().string(), nullptr));

    sessions = std::unordered_map<std::string, Session*>();
    c_session = "";
}

std::string Shell::run(std::vector<std::string>& args) {
    // we are in a session
    if (args.size() > 1) {
        if (!validSession(args[0]))
            return "{'output':'Invalid Session'}";

        return sessions[args[0]]->run();
    }

    if (args[0].compare("ls") == 0) {

        //  TODO: Write ls function

    }

    return "";
}

bool Shell::validSession(std::string& name) {
    auto sess = sessions.find(name);
    return sess != sessions.end();
}

bool Shell::loadSession(std::string& name) {
    if (!validSession(name)) return false;
    if (sessions[name] == nullptr) {

        std::string path = config + "/" + name + ".json";
        std::ifstream fs(path);
        
        // Create empty if doesn't exist
        if (!fs.good()) {
            sessions[name] = new Session();
            return true;
        }

        std::string data;
        std::string temp;
        while (fs >> temp)
            data += temp;

        sessions[name] = new Session(data);

    }
    return true;
}

bool Shell::saveSession(std::string& name) {
    if (!validSession(name)) return false;
    
    std::ofstream fs;
    std::string path = config + "/" + name + ".json";

    // Clear data in file 
    fs.open(path, std::ofstream::out | std::ofstream::trunc);
    fs << sessions[name]->string();
    fs.close();

    return true;
}


