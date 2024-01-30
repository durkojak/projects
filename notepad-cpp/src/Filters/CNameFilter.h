#ifndef DURKOJAK_CNAMEFILTER_H
#define DURKOJAK_CNAMEFILTER_H
#pragma once
#include "CFilter.h"

/**
* @brief Trieda CNameFilter filtruje na základe mien poznámok
* */
class CNameFilter : public CFilter {
public:
    CNameFilter();
    void applyFilter(std::vector<std::shared_ptr<CNote>> & allNotes) override;
    void getParameter() override;

private:
    std::string name;
};


#endif //DURKOJAK_CNAMEFILTER_H
