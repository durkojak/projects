#ifndef DURKOJAK_CDIRECTORYFILTER_H
#define DURKOJAK_CDIRECTORYFILTER_H

#include "CFilter.h"
/**
* @brief Trieda CDirectoryFilter filtruje na základe directories v ktorých poznámky sú
* */
class CDirectoryFilter : public CFilter {
public:
    CDirectoryFilter();
    void applyFilter(std::vector<std::shared_ptr<CNote>> & allNotes) override;
    void getParameter() override;
private:
    std::string name_of_dir;
};


#endif //DURKOJAK_CDIRECTORYFILTER_H
