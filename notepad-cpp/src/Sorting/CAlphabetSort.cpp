#include "CAlphabetSort.h"

CAlphabetSort::CAlphabetSort() : CSorting(){}

bool CAlphabetSort::sortNotes(const std::shared_ptr<CNote> &first, const std::shared_ptr<CNote> &second) {
    std::string str_first = first->getTitle();
    std::string str_second = second->getTitle();
    std::transform(str_first.begin(), str_first.end(), str_first.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    std::transform(str_second.begin(), str_second.end(), str_second.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    if(this->isAsc()) return str_first < str_second;
    return !(str_first < str_second);
}

bool CAlphabetSort::isSame(const std::shared_ptr<CNote> &first, const std::shared_ptr<CNote> &second) {
    if(strcasecmp(first->getTitle().c_str(),second->getTitle().c_str()) == 0) return true;
    return false;

}
