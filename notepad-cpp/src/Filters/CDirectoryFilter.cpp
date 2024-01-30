#include "CDirectoryFilter.h"

CDirectoryFilter::CDirectoryFilter() = default;

void CDirectoryFilter::getParameter() {

    std::string tag_name;
    std::cout << "Name of the directory : ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, tag_name);

    this->name_of_dir = tag_name;


}

void CDirectoryFilter::applyFilter(std::vector<std::shared_ptr<CNote>> &allNotes) {
    size_t check = 0;
    size_t size_of_vector = allNotes.size();

    for (size_t i = 0; i < size_of_vector; i++) {
        bool found = false;
        for (size_t a = 0; a < allNotes[i]->master_directories.size(); a++) {
            if (strcasecmp(this->name_of_dir.c_str(), allNotes[i]->master_directories[a].c_str()) == 0) {
                found = true;
                break;
            }

        }
        if (!found) {
            allNotes.erase(allNotes.begin() + i);
            i--;
        }
        check ++;
        if(check == size_of_vector) break;

    }
}
