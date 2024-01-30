#include "CTextFilter.h"
CTextFilter::CTextFilter() = default;
void CTextFilter::getParameter() {
    std::string text;
    std::cout << "Text to search : ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin,text);

    this->text_to_search = text;

}
void CTextFilter::applyFilter(std::vector<std::shared_ptr<CNote>> & allNotes ) {
    size_t check = 0;
    size_t vector_size = allNotes.size();
    for(size_t i = 0; i < vector_size;i++){
        if(!allNotes[i]->containsText(this->text_to_search)){
            allNotes.erase(allNotes.begin() + i);
            i--;
        }
        check ++;
        if(check == vector_size) break;
    }

}