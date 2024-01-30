#ifndef DURKOJAK_CEXPORTER_H
#define DURKOJAK_CEXPORTER_H
#include <iostream>
#include <string>
#include <fstream>

/**
* @brief Abstraktná parent trieda CExporter slúži na export poznámok do rôznych formátov
* */
class CExporter {
public:
    CExporter();
    /**
* @brief Abstraktná metóda exportFunct vytvorí file daného formátu a exportuje
* @param text telo prichystané pre daný typ formátu
* */
    virtual void exportFunct(const std::string& text, const std::string& filename) = 0;


};


#endif //DURKOJAK_CEXPORTER_H
