#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

#include "json.hpp"
using json = nlohmann::json;

namespace fs = std::filesystem;

void getDir(std::vector<std::string>& dir) {
    std::string path = "/home/daniel/.local/share/nvim/possession/";
    for (const auto & entry : fs::directory_iterator(path))
    dir.push_back(entry.path().stem().string());
}

bool validSession(std::string& cmd) {
    std::vector<std::string> dir = std::vector<std::string>();
    getDir(dir);

    for (std::string file : dir) {
        if (file.compare(cmd) == 0) {
            return true;
        }
    }
    return false;
}

std::string getPwd(std::string& path) {
    std::string fullp = "/home/daniel/.local/share/nvim/possession/" + path + ".json";
    std::ifstream fs(fullp);

    if (!fs.good()) {
        exit(1);
    }

    json data = json::parse(fs);
    std::string pwd = data["cwd"];
    return pwd;
}

int main(int argc, char** argv) {

    json res;

    if (argc < 2) return 0;

    std::string cmd = argv[1];

    if (argc == 2) {

        if (cmd.compare("exit") == 0 || cmd.compare("q") == 0 || cmd.compare(":q") == 0 ) {
            res["output"] = "hi";
            res["close"] = true;
        }
        else if (cmd.compare("ls") == 0) {
            auto dir = std::vector<std::string>();
            getDir(dir);

            std::string combined = "";
            for (std::string file : dir)
                combined += file + "\\n";

            res["output"] = combined;

        }
        else {
            // Switching into session
            if (!validSession(cmd)) {
                res["output"] = "Invalid session";
                std::cout << res.dump() << std::endl;
                return 1;
            }

            res["output"] = "Session: " + cmd;
            res["session"] = cmd;

        }
    }
    else {
        if (!validSession(cmd)) {
            res["output"] = "Invalid session";
            std::cout << res.dump() << std::endl;
            return 1;
        }

        std::string app = argv[2];

        if (app.compare("cd") == 0) {
            res["output"] = "Session reset";
            res["session"] = "?";
        }
        else if (app.compare("nv") == 0) {

            res["output"] = "Launching Neovide";
            res["output"] = "Launching Neovide";

            res["run"] = "neovide +\\\"Pl " + cmd + "\\\" & disown";
            res["close"] = true;
        }
        else if (app.compare("term") == 0) {
            res["output"] = "Launching kitty";
            res["run"] = "kitty " + getPwd(cmd);
            res["close"] = "true";
        }

    }

    std::cout << res.dump() << std::endl;
    return 0;
}
