#ifndef DURKOJAK_CDATEFILTER_H
#define DURKOJAK_CDATEFILTER_H
#include "CFilter.h"
/**
* @brief Trieda CDateFilter filtruje na základe dátumu vzniku poznámky
* */
class CDateFilter : public CFilter{
public:
    CDateFilter();
    void getParameter() override;
    void applyFilter(std::vector<std::shared_ptr<CNote>> & allNotes ) override;
private:
    CDate filter_date = {0,0,0,0,0,0};



};


#endif //DURKOJAK_CDATEFILTER_H
