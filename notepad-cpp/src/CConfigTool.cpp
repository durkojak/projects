#include "CConfigTool.h"
#include <fstream>
#include <iostream>
#include <unistd.h>

CConfigTool::CConfigTool(const std::string &config_route) {
    this->m_FilePath = config_route;

}


bool CConfigTool::isValid(const std::string &path){
    return (access(path.c_str(), F_OK) != -1);

}

bool CConfigTool::loadConfig() {

    std::ifstream configFile(this->m_FilePath);

    if (!configFile.is_open()) {
        std::cout << "Error while opening the file, failed to load the config." << std::endl;
        return false;
    }

    std::map<std::string, std::string> configMap;

    std::string line;
    while (getline(configFile, line)) {
        line.erase(std::remove_if(line.begin(), line.end(), isspace),
                   line.end());
        if (line[0] == '#' || line.empty())
            continue;
        auto delimiterPos = line.find('=');
        if(delimiterPos == std::string::npos){
            std::cout << "Failed to load the config." << std::endl;
            return false;
        }
        auto name = line.substr(0, delimiterPos);
        auto value = line.substr(delimiterPos + 1);
        if (name != "import_directory" || !isValid(value) || value.back() != '/' || configMap.count(name) > 0) {
            std::cout << "Failed to load the config." << std::endl;
            return false;
        }
        configMap[name] = value;
    }
    if(configMap.empty()) {
        std::cout << "Failed to load the config" << std::endl;
        return false;
    }
    this->import_dir = configMap["import_directory"];
    return true;

}


const std::string &CConfigTool::getImportDir() const {
    return import_dir;
}


