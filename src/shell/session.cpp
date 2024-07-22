#include "session.h"
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

void Session::load() {
    if (loaded) return;
    fs::path config(path);
    config /= name + ".json";

    // Create if doesn't exist
    if (!fs::exists(config)) {
        pwd = "";
        this->saveConfig();
    }
    else {

        std::ifstream fd(config.string());
        json data = json::parse(fd);
        pwd = data["pwd"];
    }

}

bool Session::loadFirefox() {

    fs::path firefox(path);
    firefox /= "firefox_sessions/" + name + ".jsonlz4";

    // Ignore if doesn't exist
    if (!fs::exists(firefox)) return false;

    fs::path firefox_session("/home/daniel/.mozilla/firefox/eqwuzwiy.default-release/sessionstore.jsonlz4");
    fs::copy_file(firefox, firefox_session, fs::copy_options::overwrite_existing); 
    return true;
}


void Session::saveConfig() {
    fs::path config(path);
    config /= name + ".json";

    // All data being saved
    json data;
    data["name"] = name;
    data["pwd"] = pwd;
    
    // Save file
    std::ofstream of;
    of.open(config, std::ofstream::out | std::ofstream::trunc);
    of << data.dump();
    of.close();
}

void Session::saveFirefox() {
    fs::path firefox_session("/home/daniel/.mozilla/firefox/eqwuzwiy.default-release/sessionstore-backups/recovery.jsonlz4");
    fs::path firefox_save(path);
    firefox_save /= "firefox_sessions/" + name + ".jsonlz4";
    fs::copy_file(firefox_session, firefox_save, fs::copy_options::update_existing); 
}

void Session::save() {
    saveConfig();
    saveFirefox();
}

json Session::run(std::vector<std::string>& args) {
    this->load();

    json res;
    // First arg is session
    if (args.size() == 1) {
        res["session"] = name;
    }
    else if (!args[1].compare("q")) {
        this->save();
        res["session"] = "?";
        res["output"] = "exit session";
    }

    else if (!args[1].compare("w")) {
        this->save();
        res["output"] = "saved session";
    }
    else if (!args[1].compare("autocomplete")) {
        //  TODO: implement autocomplete function

    }

    else if (!args[1].compare("set")) {
        if (args.size() < 4) {
            res["output"] = "invalid arguments";
        }
        else if (!args[2].compare("pwd")) {
            pwd = args[3];
            res["output"] = "set pwd";
            res["close"] = true;
            this->saveConfig();
        }
        else {
            // Join all arguments together
            std::string command = "";
            for (size_t i = 4; i < args.size(); i++) {
                command += args[i] + " ";
            }
            res["output"] = "shouldnt be here";
            res["close"] = true;
            // Do something with data here
        }
    }

    else if (!args[1].compare("firefox")) {
        if (loadFirefox()) {
            // Can't do it in ags for some reason
            system("killall firefox");
            res["run"] = "firefox";
            res["close"] = true;
        }
    }

    else if (!args[1].compare("edit")) {
        res["run"] = "neovide " + pwd;
        res["close"] = true;
    }

    else if (!args[1].compare("term")) {
        res["run"] = "kitty " + pwd;
        res["close"] = true;
    }

    return res;
}
