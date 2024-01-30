#include "CNameFilter.h"
#include "../CDirectory.h"

CNameFilter::CNameFilter() = default;
void CNameFilter::applyFilter(std::vector<std::shared_ptr<CNote>> &allNotes) {
    size_t check = 0;
    size_t vector_size = allNotes.size();

    for (size_t i = 0; i < vector_size; i++) {
        if (strcasecmp(allNotes[i]->getTitle().c_str(), this->name.c_str()) != 0) {
            allNotes.erase(allNotes.begin() + i);
            i--;
        }
        check++;
        if(check == vector_size) break;
    }

}

void CNameFilter::getParameter() {

    std::string name;
    std::cout << "Name of the note : ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);

    this->name = name;


}
