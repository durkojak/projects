#include "CDirectory.h"
CDirectory::CDirectory(const std::string &name) {
    this->name = name;
}

bool CDirectory::operator==(const CDirectory &other) const {
    return this->name == other.name;
}

CDirectory::CDirectory(const CDirectory &other) {
    this->name = other.name;
    this->subdirectories = other.subdirectories;
    this->notes.clear();
    for (const std::shared_ptr<CNote> &note: other.notes) {
        if (note) {
            std::shared_ptr<CNote> newNote = note->copyPtr();
            notes.push_back(newNote);
        } else notes.push_back(nullptr);

    }
}

CDirectory &CDirectory::operator=(const CDirectory &other) {
    if (this == &other) return *this;
    this->name = other.name;
    this->subdirectories = other.subdirectories;
    this->notes.clear();
    for (const std::shared_ptr<CNote> &note: other.notes) {
        if (note) {
            std::shared_ptr<CNote> newNote = note->copyPtr();
            notes.push_back(newNote);
        } else notes.push_back(nullptr);
    }
    return *this;
}

void CDirectory::addNote() {
    std::shared_ptr<CNote> note = nullptr;

    std::cout << "a. Regular note" << std::endl;
    std::cout << "b. Recipe" << std::endl;
    std::cout << "c. Shopping list" << std::endl;
    std::cout << "d. ToDoList" << std::endl;

    char option;
    std::cin >> option;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (option == 'a') {
        std::shared_ptr<CRegular> tmp = std::make_shared<CRegular>();
        tmp->nameNote();
        tmp->appendText();
        note = tmp;
    } else if (option == 'b') {
        std::shared_ptr<CRecipe> tmp = std::make_shared<CRecipe>();
        tmp->nameNote();
        tmp->addIngredient();
        tmp->addStep();
        note = tmp;
    } else if (option == 'c') {
        std::shared_ptr<CShoppingList> tmp = std::make_shared<CShoppingList>();
        tmp->nameNote();
        tmp->addItem();
        note = tmp;
    } else if (option == 'd') {
        std::shared_ptr<CToDoList> tmp = std::make_shared<CToDoList>();
        tmp->nameNote();
        tmp->addTask();
        note = tmp;
    }
    for(const std::shared_ptr<CNote> & elem : notes){
        if(elem->getTitle() == note->getTitle()){
            std::cout << "Name is already taken." << std::endl;
            return;
        }
    }
    note->master_directories = this->master_directories;
    note->createdDate();
    notes.push_back(note);
}

void CDirectory::removeNote(const std::string &targetName) {
    auto it = std::find_if(notes.begin(), notes.end(), [&targetName](const std::shared_ptr<CNote> note) {
        return note->getTitle() == targetName;
    });
    if(it == notes.end()){
        std::cerr << "This note doesn't exist" << std::endl;
        return;
    }
    notes.erase(it);
}

bool CDirectory::addSubdirectory(const std::string & name) {
    std::shared_ptr<CDirectory> subdirectory = std::make_shared<CDirectory>(name);
    subdirectory->master_directories.insert(subdirectory->master_directories.end(), this->master_directories.begin(),
                                            this->master_directories.end());
    subdirectory->master_directories.push_back(subdirectory->getName());
    subdirectories.push_back(subdirectory);

    return true;
}


void CDirectory::showContent() const {
    std::cout << "Subdirectories:" << std::endl;
    for (size_t i = 0; i < subdirectories.size(); i++) {
        std::cout << subdirectories[i]->getName() << std::endl;
    }
    std::cout << "Notes: " << std::endl;
    for (size_t i = 0; i < notes.size(); i++) {
        for (size_t x = 0; x < master_directories.size(); x++) std::cout << "/" << notes[i]->master_directories[x];
        std::cout << "\n";
        std::cout << notes[i]->getTitle() << " - " << notes[i]->getDateOfCreation();
        std::cout << "Tags : ";
        for (size_t a = 0; a < notes[i]->tags.size(); a++) {
            std::cout << notes[i]->tags[a] << "||";
        }
        std::cout << "\n";
    }
}

bool CDirectory::removeSubdirectory(const std::string &name) {
    auto it = std::find_if(subdirectories.begin(), subdirectories.end(),
                           [&name](const std::shared_ptr<CDirectory> &subdirectory) {
                               return subdirectory->getName() == name;
                           });
    if (it != subdirectories.end()) {
        subdirectories.erase(it);
        return true;
    } else {
        std::cout << "Subdirectory not found!" << std::endl;
        return false;
    }
}

const std::string &CDirectory::getName() const {
    return name;
}

void CDirectory::findNote(const std::string &name, int mode,int type) const {
    int index = -1;
    for (size_t i = 0; i < notes.size(); i++) {
        if (notes[i]->getTitle() == name) {
            index = i;
            break;
        }
    }
    if(index == -1){
        std::cerr << "This note isn't available." << std::endl;
        return;
    }
    if (mode == 0) notes[index]->displayNote();
    if (mode == 1) notes[index]->contextMenu();
    if (mode == 2) notes[index]->exportNote(type);
}


std::shared_ptr<CDirectory> CDirectory::switchDirectory() {
    std::cout << "Name of the directory you would like to change to" << std::endl;
    std::string name;
    std::cin >> name;
    auto it = std::find_if(subdirectories.begin(), subdirectories.end(),
                           [&name](const std::shared_ptr<CDirectory> &subdirectory) {
                               return subdirectory->getName() == name;
                           });
    if (it != subdirectories.end()) {
        return *it;
    } else {
        std::cout << "Subdirectory not found!" << std::endl;
        return std::make_shared<CDirectory>(*this);
    }
}

std::vector<std::shared_ptr<CNote>> CDirectory::showFilterMenu(std::shared_ptr<CDirectory> &core_directory) const {
    std::vector<std::shared_ptr<CFilter>> filters;
    std::cout << "*** FILTER MENU *** " << std::endl;
    std::cout << "1.Name filter" << std::endl;
    std::cout << "2.Tag filter" << std::endl;
    std::cout << "3.Text filter" << std::endl;
    std::cout << "4.Directory filter" << std::endl;
    std::cout << "5.Date filter" << std::endl;
    std::cout << "0.Stop" << std::endl;

    while (true) {
        int option;
        std::cout << "Choose a filter option" << std::endl;
        std::cin >> option;
        std::shared_ptr<CFilter> tmp_filter = nullptr;

        if (option == 1) {
            std::shared_ptr<CNameFilter> tmp = std::make_shared<CNameFilter>();
            tmp_filter = tmp;
        }
        else if (option == 2) {
            std::shared_ptr<CTagFilter> tmp = std::make_shared<CTagFilter>();
            tmp_filter = tmp;
        }
        else if(option == 3){
            std::shared_ptr<CTextFilter> tmp = std::make_shared<CTextFilter>();
            tmp_filter = tmp;
        }
        else if (option == 4) {
            std::shared_ptr<CDirectoryFilter> tmp = std::make_shared<CDirectoryFilter>();
            tmp_filter = tmp;
        }
        else if (option == 5) {
            std::shared_ptr<CDateFilter> tmp = std::make_shared<CDateFilter>();
            tmp_filter = tmp;
        }
        else if (option == 0) break;
        else{
            std::cout << "Invalid option" << std::endl;
            continue;
        }
        tmp_filter->getParameter();
        filters.push_back(tmp_filter);
    }

    std::vector<std::shared_ptr<CNote>> allNotes;
    core_directory->getAllNotes(allNotes);
    for (size_t i = 0; i < filters.size(); i++) {
        filters[i]->applyFilter(allNotes);
    }
    if(allNotes.empty()) std::cout << "There are no notes corresponding to your search." << std::endl;
    else for (const auto &elem: allNotes) {
        std::cout << elem->getTitle() << std::endl;
    }
    return allNotes;
}

void CDirectory::getAllNotes(std::vector<std::shared_ptr<CNote>> & allNotes) const {
    for (size_t i = 0; i < this->notes.size(); i++) {
        allNotes.push_back(this->notes[i]);
    }
    for (size_t i = 0; i < this->subdirectories.size(); i++) {
        this->subdirectories[i]->getAllNotes(allNotes);
    }
}

void CDirectory::showSortMenu(std::shared_ptr<CDirectory> &core_directory) {
    std::vector<std::shared_ptr<CNote>> allNotes;
    std::vector<std::shared_ptr<CSorting>> sorts;

    core_directory->getAllNotes(allNotes);

    std::cout << "Choose sort" << std::endl;
    std::cout << "1. Alphabet sort" << std::endl;
    std::cout << "2. Date sort" << std::endl;
    std::cout << "0. Stop" << std::endl;

    while (true) {
        int option;
        std::cout << "Choose a sort" << std::endl;
        std::cin >> option;
        std::shared_ptr<CSorting> tmp_sort = nullptr;

        if (option == 1) {
            std::shared_ptr<CAlphabetSort> tmp = std::make_shared<CAlphabetSort>();
            tmp_sort = tmp;
        }
        if (option == 2) {
            std::shared_ptr<CDateSort> tmp = std::make_shared<CDateSort>();
            tmp_sort = tmp;
        }
        if (option == 0) break;
        std::string quest;
        std::cout << "In ascending order? (y/n) : " << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin,quest);
        if(quest != "y" && quest != "n") return;
        if(quest == "y") tmp_sort->setAsc(true);
        else tmp_sort->setAsc(false);
        sorts.push_back(tmp_sort);
    }
    CSortClass sorter{sorts};
    std::sort(allNotes.begin(),allNotes.end(),sorter);

    for (const auto &elem: allNotes) {
        std::cout << elem->getTitle() << std::endl;
    }
}

void CDirectory::isNote(const std::string &filename,CConfigTool & configTool) {
    if(filename.size() < 4 || filename.substr(filename.size() - 4) != ".txt"){
        std::cerr << "File isn't a .txt file" << std::endl;
        return;
    }

    std::ifstream file;
    file.open(configTool.getImportDir() + filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        file.close();
        return;
    }

    std::string check_header;
    std::getline(file,check_header);

    if(check_header != "*****"){
        std::cerr << "This type of .txt isn't importable." << std::endl;
        file.close();
        return;
    }
    std::vector<std::string> headers= {"REGULAR","RECIPE","TODOLIST","SHOPPINGLIST"};
    std::string type_of_note;
    std::getline(file,type_of_note);

    auto it = std::find(headers.begin(),headers.end(),type_of_note);
    if(it == headers.end()){
        std::cerr << "This type of note isnt supported" << std::endl;
        file.close();
        return;
    }

    std::string title;
    std::getline(file,title);

    std::shared_ptr<CNote> new_note = nullptr;
    if(type_of_note == "REGULAR") new_note = std::make_shared<CRegular>(title);
    else if(type_of_note == "RECIPE") new_note = std::make_shared<CRecipe>(title);
    else if(type_of_note == "TODOLIST") new_note = std::make_shared<CToDoList>(title);
    else if(type_of_note == "SHOPPINGLIST") new_note = std::make_shared<CShoppingList>(title);
    new_note->master_directories = this->master_directories;
    if(!new_note->importNote(file)) {
        std::cerr << "Import failed" << std::endl;
        file.close();
        return;
    }
    this->notes.push_back(new_note);
    file.close();
}

void CDirectory::exportMenu() {
    std::vector<std::shared_ptr<CNote>> notes_to_export;
    std::string typeString;
    std::string countString;

    std::cout << "*** EXPORT MENU ***" << std::endl;
    std::cout << "Choose one of the following formats you would like to export to" << std::endl;
    std::cout << "1. HTML" << std::endl;
    std::cout << "2. Txt" << std::endl;
    std::cout << "3. Markdown" << std::endl;
    std::cout << "Choose a number : ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin,typeString);

    for(char c : typeString){
        if(!std::isdigit(c)){
            std::cout << "Invalid option, returning back" << std::endl;
            return;
        }
    }

    std::cout << "Choose which notes you would like to export" << std::endl;
    std::cout << "1. All" << std::endl;
    std::cout << "2. Notes found by search" << std::endl;
    std::cout << "3. Specific note" << std::endl;
    std::getline(std::cin,countString);

    for(char c : countString){
        if(!std::isdigit(c)){
            std::cout << "Invalid option, returning back" << std::endl;
            return;
        }
    }

    int count = std::stoi(countString);
    int type = std::stoi(typeString);

    if(count == 1){
        this->getAllNotes(notes_to_export);
        for(size_t i = 0; i < notes_to_export.size(); i++){
            notes_to_export[i]->exportNote(type);
        }
    }
    else if(count == 2){
        std::shared_ptr<CDirectory> core_directory = std::make_shared<CDirectory>(*this);
        notes_to_export = this->showFilterMenu(core_directory);
        for(size_t i = 0; i < notes_to_export.size(); i++){
            notes_to_export[i]->exportNote(type);
        }
    }
    else if(count == 3){
        std::string name;
        std::cout << "Name of the note you want to export" << std::endl;
        std::cin >> name;
        this->findNote(name,2,type);
    }
    else {
        std::cout<<"Invalid input" << std::endl;
    }
}
