#include "CShoppingList.h"

CShoppingList::CShoppingList() : CNote("") {}

CShoppingList::CShoppingList(const std::string &name) : CNote(name) {
    this->setName(name);
}

CShoppingList::~CShoppingList() = default;

void CShoppingList::addItem() {
    while (true) {
        std::string priceString;
        double priceDouble;
        std::string item;

        std::cout << "Item name : ";
        std::getline(std::cin, item);

        if (strcasecmp(item.c_str(), "stop") == 0) break;

        std::cout << "Price : ";
        std::getline(std::cin, priceString);

        if (strcasecmp(priceString.c_str(), "stop") == 0) break;
        for (char c: priceString) {
            if (!std::isdigit(c)) {
                if (c != '.') {
                    std::cout << "Invalid price, returning back." << std::endl;
                    return;
                }
            }
        }
        priceDouble = std::stod(priceString);

        ShoppingItem tmp{item, priceDouble};

        shopping_list.push_back(tmp);
        this->logRecord("Added " + tmp.item);
    }
}

void CShoppingList::removeItem() {
    std::cout << "Select the number of the item you would like to remove : ";
    std::string indexString;
    std::getline(std::cin,indexString);
    for(char c : indexString){
        if(!std::isdigit(c)){
            std::cout << "Invalid option, returning back" << std::endl;
            return;
        }
    }
    size_t index = std::stoi(indexString);
    if(index >= shopping_list.size()){
        std::cout << "Invalid index" << std::endl;
        return;
    }
    this->logRecord("Removed " + shopping_list[index].item);
    this->shopping_list.erase(this->shopping_list.begin() + index);
}

void CShoppingList::getPrice() const {
    double sum = 0;
    for (const auto &i: shopping_list) {
        sum += i.price;
    }
    std::cout << "Total price is " << sum << std::endl;
}

void CShoppingList::displayNote() const {
    std::cout << "SHOPPING LIST" << std::endl;
    std::cout << this->getTitle() << std::endl;
    if (shopping_list.empty()) {
        std::cout << "Shopping list is empty." << std::endl;
        return;
    }
    for (size_t i = 0; i < shopping_list.size(); i++) {
        std::cout << i << " " << shopping_list[i].item << " -- " << shopping_list[i].price << "€" << std::endl;
    }

}

void CShoppingList::contextMenu() {
    std::cout << "Available actions with Shopping list " << this->getTitle() << std::endl;
    std::cout << "1. Add item" << std::endl;
    std::cout << "2. Remove item" << std::endl;
    std::cout << "3. Cost of the list" << std::endl;
    std::cout << "4. Edit title" << std::endl;
    std::cout << "5. Add tag" << std::endl;
    std::cout << "6. Remove tag" << std::endl;
    std::cout << "7. Print log record" << std::endl;
    std::cout << "8. Change date" << std::endl;
    std::string optionString;
    std::getline(std::cin,optionString);
    for(char c : optionString){
        if(!std::isdigit(c)){
            std::cout << "Invalid option, returning back" << std::endl;
            return;
        }
    }
    if(optionString.empty()) {
        std::cout << "Invalid option, returning back" << std::endl;
        return;
    }
    int option = std::stoi(optionString);
    if (option == 1) this->addItem();
    else if (option == 2) this->removeItem();
    else if (option == 3) this->getPrice();
    else if (option == 4) this->editTitle();
    else if (option == 5) this->addTag();
    else if (option == 6) this->removeTag();
    else if (option == 7) this->printLogRecord();
    else if (option == 8) this->changeDate();
    else std::cout << "Invalid option, returning back" << std::endl;
}

void CShoppingList::exportNote(int type) {
    std::shared_ptr<CExporter> exportObj = nullptr;
    bool isMarkdown = false;
    bool isHtml = false;

    if (type == 1) {
        isHtml = true;
        exportObj = std::make_shared<CHtml>();
    }
    if (type == 2) exportObj = std::make_shared<CTxt>();
    if (type == 3) {
        exportObj = std::make_shared<CMarkDown>();
        isMarkdown = true;
    }

    std::string text_export;

    if (isMarkdown) {
        text_export = "# SHOPPING LIST : " + this->getTitle() + "\n";
        for (size_t i = 0; i < shopping_list.size(); i++) {
            text_export += shopping_list[i].item + " *" + std::to_string(shopping_list[i].price) + "*\n";
        }
    }
    else if(isHtml){
        text_export += "<h1>SHOPPING LIST : " + this->getTitle() + "</h1>\n";
        for (size_t i = 0; i < shopping_list.size(); i++) {
            text_export += shopping_list[i].item + " \n";
            text_export += std::to_string(shopping_list[i].price) + "<br>\n";
        }
    }
    else {
        text_export += "*****";
        text_export += "SHOPPING LIST\n";
        text_export += this->getTitle() + "\n";
        for (size_t i = 0; i < shopping_list.size(); i++) {
            text_export += shopping_list[i].item + "\n";
            text_export += std::to_string(shopping_list[i].price) + "\n";
        }
        text_export += "*****";
    }
    exportObj->exportFunct(text_export, this->getTitle());
}


std::shared_ptr<CNote> CShoppingList::copyPtr() {
    return std::make_shared<CShoppingList>(*this);
}

bool CShoppingList::containsText(const std::string &text_to_search) {
    std::string joinedText;
    for (const auto &elem: shopping_list) {
        joinedText += elem.item + " " + std::to_string(elem.price);
        joinedText += "\n";
    }


    std::string text_for_search = text_to_search;

    std::transform(joinedText.begin(), joinedText.end(), joinedText.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    std::transform(text_for_search.begin(), text_for_search.end(), text_for_search.begin(),
                   [](unsigned char c) { return std::tolower(c); });


    size_t position = joinedText.find(text_for_search);
    if (position != std::string::npos) return true;
    return false;
}

bool CShoppingList::importNote(std::ifstream &file) {
    std::string line;
    int parity = 0;

    ShoppingItem tmp;
    while (std::getline(file, line)) {
        if (line == "*****" && parity % 2 == 0) return true;
        if (line == "*****" && parity % 2 == 1) return false;
        if (parity % 2 == 0) {
            tmp.item = line;
        }
        if (parity % 2 == 1) {
            for (size_t i = 0; i < line.size(); ++i) if (!std::isdigit(line[i]) && line[i] != '.') return false;
            tmp.price = std::stod(line);
            this->shopping_list.push_back(tmp);
            tmp = {};
        }
        parity++;
    }
    return false;
}