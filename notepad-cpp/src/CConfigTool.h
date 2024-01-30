#ifndef DURKOJAK_CCONFIGTOOL_H
#define DURKOJAK_CCONFIGTOOL_H
#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>

/**
 * @brief Trieda CConfigTool slúži na prácu s konfigurákom.
 * */
class CConfigTool {
public:
    explicit CConfigTool(const std::string & config_route);

    /**
 * @brief Funkcia loadConfig slúži na načítanie konfiguráku a skontrolovanie jeho obsahu.Momentálne moja aplikácia
 *        akceptuje iba parameter import_directory, ktorý určuje directory, z ktorého budem importovať .txt files.
 * @return false, ak sa nepodarilo načítať konfigurák
 * */

    bool loadConfig();

    /**
 * @brief Funkcia isValid slúži na skontrolovanie path ku konfiguráku
 * @param path string, ktorý obsahuje načítanú path
 * @return false, ak to nie je skutočná path
 * */
    static bool isValid(const std::string & path);


    const std::string &getImportDir() const;

private:
    std::string m_FilePath;
    std::string import_dir;
};


#endif //DURKOJAK_CCONFIGTOOL_H
