#include <iostream>
#include <string>
#include "CNotesManager.h"
#include "CConfigTool.h"



/**
 * @brief spustenie aplikácie
 * @param argv argumenty, prijímam path ku konfiguráku
 * @return 1 pri skončení aplikácie, 0 pri neúspešnom načítaní konfiguráku
 * */
int main(int argc, char *argv[]){
    std::string path = argv[1];
//    std::string path = "/home/jakub/durkojak/config.properties";
    CConfigTool configTool(path);
    if(!configTool.loadConfig()) return 0;

    CNotesManager app;


    try {
        app.run(configTool);
    } catch (const std::exception& ex) {
        std::cout << "Exception caught: " << ex.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception caught" << std::endl;
    }

    return 0;

}