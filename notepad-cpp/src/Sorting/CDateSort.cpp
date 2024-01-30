#include "CDateSort.h"

CDateSort::CDateSort() : CSorting() {}

bool CDateSort::sortNotes(const std::shared_ptr<CNote> &first, const std::shared_ptr<CNote> &second) {
    if(this->isAsc()) return first->getDateOfCreation() < second->getDateOfCreation();
    return !(first->getDateOfCreation() < second->getDateOfCreation());
}

bool CDateSort::isSame(const std::shared_ptr<CNote> &first, const std::shared_ptr<CNote> &second) {
    return first->getTitle() == second->getTitle();
}