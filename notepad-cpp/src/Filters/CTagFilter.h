#ifndef DURKOJAK_CTAGFILTER_H
#define DURKOJAK_CTAGFILTER_H
#include "CFilter.h"


/**
* @brief Trieda CTagFilter filtruje poznámky na základe tagov
* */
class CTagFilter : public CFilter {
public:
    CTagFilter();
    void applyFilter(std::vector<std::shared_ptr<CNote>> & allNotes) override;
    void getParameter() override;
private:
    std::string tag_name;

};


#endif //DURKOJAK_CTAGFILTER_H
