#ifndef DURKOJAK_CTEXTFILTER_H
#define DURKOJAK_CTEXTFILTER_H

#include "CFilter.h"

/**
* @brief Trieda CTextFilter zistí, či sa v danej poznámke vyskytuje hľadaný text
* */
class CTextFilter : public CFilter {
public:
    CTextFilter();
    void getParameter() override;
    void applyFilter(std::vector<std::shared_ptr<CNote>> & allNotes ) override;
private:
    std::string text_to_search;

};


#endif //DURKOJAK_CTEXTFILTER_H
