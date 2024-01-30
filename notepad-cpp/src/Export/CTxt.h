#ifndef DURKOJAK_CTXT_H
#define DURKOJAK_CTXT_H


#include "CExporter.h"

/**
* @brief Trieda CTxt slúži na export do obyčajného textového súboru
* */
class CTxt : public CExporter{
public:
    CTxt();
    void exportFunct(const std::string& text, const std::string& filename) override;

};


#endif //DURKOJAK_CTXT_H
