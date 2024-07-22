#include <filesystem>
namespace fs = std::filesystem;

#include "shell.h"

Shell::Shell(std::string _path) : path(_path), current_session("") {
    sessions = std::unordered_map<std::string, std::shared_ptr<Session>>();

    // Check if config directory exists and create if not
    fs::path config(path);
    if (!fs::exists(config)) {
        fs::create_directory(config);
    }

    // Check if firefox directory exists
    fs::path firefox(path);
    firefox /= "firefox_sessions";
    if (!fs::exists(firefox)) {
        fs::create_directory(firefox);
    }

    // Create all sessions unloaded
    for (const auto & entry : fs::directory_iterator(config)) {
        std::string s_name = entry.path().stem().string();
        sessions.insert(
            std::make_pair(s_name, 
                           std::make_shared<Session>(s_name, path)
            )
        );
    }
}

bool Shell::validSession(std::string& name) {
    for (auto it : sessions)
        if (!it.first.compare(name)) return true;
    return false;
}


json Shell::run(std::vector<std::string>& args) {
    if (!validSession(args[0])) {
         sessions.insert(
            std::make_pair(args[0], 
                           std::make_shared<Session>(args[0], path)
            )
        );
    }
    return sessions[args[0]]->run(args);
}
