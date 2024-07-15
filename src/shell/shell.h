#ifndef _SHELL_H_
#define _SHELL_H_

#include <string>
#include <vector>
#include <unordered_map>

#include "session.h"

class Shell {
public:

    Shell(std::string path = "/home/daniel/.config/gsm");

    bool validSession(std::string& name);
    bool loadSession(std::string& name);
    bool saveSession(std::string& name);

    std::string run(std::vector<std::string>& args);

private:
    std::string config;
    std::string c_session;
    std::unordered_map<std::string, Session*> sessions;
};

#endif
