#ifndef _SESSION_H_
#define _SESSION_H_

#include <string>
#include <unordered_map>
#include <vector>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Session {
public:
    /**
    * Session is not loaded in the constructor,
    * we lazy load all sessions to save on file io
    */
    Session(std::string _name, std::string _path) : 
        name(_name), path(_path), loaded(false) {};

    json run(std::vector<std::string>& args);

private:

    std::string name;
    std::string path;

    std::string pwd;

    bool loaded;

    void load();
    bool loadFirefox();
    void saveFirefox();
    void saveConfig();
    void save();

};

#endif
