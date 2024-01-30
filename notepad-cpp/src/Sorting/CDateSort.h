#ifndef DURKOJAK_CDATESORT_H
#define DURKOJAK_CDATESORT_H

#include "CSorting.h"


/**
* @brief Trieda CDateSort má naimplementované sortovacie metódy na základe dátumu vzniku
* */
class CDateSort : public CSorting {
public:
    CDateSort();
    bool sortNotes(const std::shared_ptr<CNote> &first, const std::shared_ptr<CNote> &second) override;

    bool isSame(const std::shared_ptr<CNote> &first, const std::shared_ptr<CNote> &second) override;


};


#endif //DURKOJAK_CDATESORT_H
