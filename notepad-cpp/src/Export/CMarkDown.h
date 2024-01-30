#ifndef DURKOJAK_CMARKDOWN_H
#define DURKOJAK_CMARKDOWN_H


#include "CExporter.h"

/**
* @brief Trieda CMarkDown slúži na export do markdown
* */
class CMarkDown :public CExporter{
public:
    CMarkDown();
    void exportFunct(const std::string& text,const std::string& filename) override;


};


#endif //DURKOJAK_CMARKDOWN_H
