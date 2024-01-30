#ifndef DURKOJAK_CFILTER_H
#define DURKOJAK_CFILTER_H

#include <iostream>
#include <limits>
#include <ios>
#include <cstring>
#include <sstream>
#include "../Notes/CNote.h"
#include <unordered_set>
class CDirectory;

/**
* @brief Trieda CFilter je parent abstraktná trieda filtrov
* */
class CFilter {
public:
    /**
* @brief Abstraktná metóda applyFilter slúži na vyfiltrovanie poznámok na základe daného kritéria
* @param allNotes vektor, kde na počiatku sú všetky poznámky a postupne sa z tade filtrujú
* */
    virtual void applyFilter(std::vector<std::shared_ptr<CNote>> & allNotes ) = 0;
    /**
* @brief Abstraktná metóda getParameter získanie filtrovacieho parametru
* */
    virtual void getParameter() = 0;

};


#endif //DURKOJAK_CFILTER_H
