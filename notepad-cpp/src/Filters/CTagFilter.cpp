#include "CTagFilter.h"

CTagFilter::CTagFilter() = default;

void CTagFilter::getParameter() {

    std::string tag_name;
    std::cout << "Name of the tag : ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, tag_name);

    this->tag_name = tag_name;
}

void CTagFilter::applyFilter(std::vector<std::shared_ptr<CNote>> &allNotes) {
    size_t check = 0;
    size_t vector_size = allNotes.size();

    for (size_t i = 0; i < vector_size; i++) {
        bool keep = false;
        for (const auto &tag: allNotes[i]->tags) {
            if (strcasecmp(tag.c_str(), this->tag_name.c_str()) == 0) {
                keep = true;
                break;
            }
        }
        if (!keep) {
            allNotes.erase(allNotes.begin() + i);
            i--;
        }
        check++;
        if (check == vector_size)break;
    }

}