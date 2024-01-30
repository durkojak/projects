#ifndef DURKOJAK_CSORTCLASS_H
#define DURKOJAK_CSORTCLASS_H
#include "CSorting.h"
/**
* @brief Trieda CSortClass  je využitá ako funktor, sorts_vector obsahuje sorting objekty, ktoré sa postupne využívajú.
* */
class CSortClass {
public:
    explicit CSortClass(std::vector<std::shared_ptr<CSorting>> & sorts);
    /**
* @brief V preťaženom operátore() využívam rekurziu na prejdenie sorts_vector.Ak sú dve poznámky rovnaké na základe
*        daného sortu, využije sa ďalší sort v poradí.
* @param index ukazuje na sort v sorts_vector, inkrementuje sa rekurzívnym volaním
* */
    bool operator()(const std::shared_ptr<CNote>& first, const std::shared_ptr<CNote>& second, size_t index = 0)const;
private:
    std::vector<std::shared_ptr<CSorting>> sorts_vector;
};


#endif //DURKOJAK_CSORTCLASS_H
