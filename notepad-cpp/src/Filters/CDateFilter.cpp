#include "CDateFilter.h"
CDateFilter::CDateFilter() = default;

void CDateFilter::getParameter() {
    int year, month, day = 0;
    std::cout << "Type date parameters" << std::endl;
    std::cout << "Year : ";
    std::cin >> year;
    std::cout << "Month : ";
    std::cin >> month;
    std::cout << "Day : ";
    std::cin >> day;

    this->filter_date.setDay(day);
    this->filter_date.setMonth(month);
    this->filter_date.setYear(year);
}


void CDateFilter::applyFilter(std::vector<std::shared_ptr<CNote>> &allNotes) {
    size_t check = 0;

    size_t vector_size = allNotes.size();
    for(size_t i = 0; i < vector_size;i++){
        if(allNotes[i]->getDateOfCreation() != this->filter_date){
            allNotes.erase(allNotes.begin() + i);
            i--;
        }
        check ++;
        if(check == vector_size) break;
    }
}







