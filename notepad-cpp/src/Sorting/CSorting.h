#ifndef DURKOJAK_CSORTING_H
#define DURKOJAK_CSORTING_H
#include "../Notes/CNote.h"
#include <cstring>

/**
* @brief Trieda CSorting je abstraktná parent trieda sortingov. Asc určuje zostupné/vzostupné poradie
* */
class CSorting {
public:
    CSorting();

    /**
* @brief Abstraktná metóda sortNotes slúži na porovnanie dvoch poznámok na základe daného kritéria
* */
    virtual bool sortNotes(const std::shared_ptr<CNote> &first, const std::shared_ptr<CNote> &second) = 0;

    /**
* @brief Abstraktná metóda isSame zistí, či dve poznámky na základe sortovacieho kritéria sú rovnako sortené
* */
    virtual bool isSame(const std::shared_ptr<CNote> &first, const std::shared_ptr<CNote> &second) = 0;

    bool isAsc() const;

    void setAsc(bool asc);

private:
    bool asc;
};


#endif //DURKOJAK_CSORTING_H
