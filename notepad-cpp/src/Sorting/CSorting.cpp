#include "CSorting.h"

CSorting::CSorting() {
    this->asc = false;
}

bool CSorting::isAsc() const {
    return asc;
}

void CSorting::setAsc(bool asc) {
    CSorting::asc = asc;
}
