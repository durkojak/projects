#ifndef DURKOJAK_CHTML_H
#define DURKOJAK_CHTML_H

#include "CExporter.h"

/**
* @brief Trieda CHtml slúži na export do HTML
* */
class CHtml :public CExporter{
public:
    CHtml();
    void exportFunct(const std::string& text, const std::string& filename) override;


};


#endif //DURKOJAK_CHTML_H
