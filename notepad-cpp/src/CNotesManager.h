#ifndef DURKOJAK_CNOTESMANAGER_H
#define DURKOJAK_CNOTESMANAGER_H
#include "CDirectory.h"
#include <iostream>
#include <ctime>
#include <memory>
#include "CConfigTool.h"


/**
 * @brief Trieda CNotesManager je jadro aplikácie. Core_directory je root directory,
 *        ptr_user je momentálny directory, v ktorom user je.
 * */
class CNotesManager {
public:

    CNotesManager();

    /**
 * @brief Funkcia run prijíma od usera požiadavky, ktoré sú potom sprostredkované ďalej.
 * @param configTool načítaný konfigurák
 * */
    void run(CConfigTool & configTool);

private:
    std::shared_ptr<CDirectory> core_directory;
    std::shared_ptr<CDirectory> ptr_user;


};


#endif //DURKOJAK_CNOTESMANAGER_H
