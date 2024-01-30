#ifndef DURKOJAK_CALPHABETSORT_H
#define DURKOJAK_CALPHABETSORT_H

#include "CSorting.h"
/**
* @brief Trieda CAlphabetSort má naimplementované sortovacie metódy na základe abecedného poradia
* */
class CAlphabetSort : public CSorting {
public:
    CAlphabetSort();
    bool sortNotes(const std::shared_ptr<CNote> &first, const std::shared_ptr<CNote> &second) override;

    bool isSame(const std::shared_ptr<CNote> &first, const std::shared_ptr<CNote> &second) override;


};


#endif //DURKOJAK_CALPHABETSORT_H
