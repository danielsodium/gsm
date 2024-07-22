#ifndef _SHELL_H_
#define _SHELL_H_

#include <string>
#include <vector>
#include <unordered_map>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "session.h"

class Shell {
public:
    Shell(std::string _path = "/home/daniel/.config/gsm");

    bool validSession(std::string& name);

    json run(std::vector<std::string>& args);

private:
    std::string path;
    std::string current_session;
    std::unordered_map<std::string, std::shared_ptr<Session>> sessions;
};

#endif
