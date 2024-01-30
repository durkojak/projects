#include "CRecipe.h"

CRecipe::CRecipe() : CNote("") {}

CRecipe::CRecipe(const std::string &name) : CNote(name){
    this->setName(name);
}

CRecipe::~CRecipe() = default;

void CRecipe::addIngredient() {
    while (true) {
        std::string ingredient;
        std::cout << "Insert ingredient : ";
        std::getline(std::cin,ingredient);
        if (strcasecmp(ingredient.c_str(), "stop") == 0) break;
        ingredients.push_back(ingredient);
    }
    this->logRecord("Added ingredients");
}

void CRecipe::removeIngredient() {
    std::cout << "Select the number of the ingredient you would like to remove : ";
    std::string indexString;
    std::getline(std::cin,indexString);
    for(char c : indexString){
        if(!std::isdigit(c)){
            std::cout << "Invalid option, returning back" << std::endl;
            return;
        }
    }
    size_t index = std::stoi(indexString);
    if(index >= this->ingredients.size()){
        std::cout << "Invalid ingredient index" << std::endl;
        return;
    }
    this->ingredients.erase(this->ingredients.begin() + index);
    this->logRecord("Removed ingredients");
}

void CRecipe::addStep() {
    while (true) {
        std::string step;
        std::cout << "Insert step : ";
        std::getline(std::cin,step);
        if (strcasecmp(step.c_str(), "stop") == 0) break;
        steps.push_back(step);
    }
    this->logRecord("Added steps");
}

void CRecipe::removeStep() {
    std::cout << "Select the number of the step you would like to remove : ";
    std::string indexString;
    std::getline(std::cin,indexString);
    for(char c : indexString){
        if(!std::isdigit(c)){
            std::cout << "Invalid option, returning back" << std::endl;
            return;
        }
    }
    size_t index = std::stoi(indexString);
    if(index >= this->steps.size()){
        std::cout << "Invalid step index" << std::endl;
        return;
    }
    this->steps.erase(this->steps.begin() + index);
    this->logRecord("Removed steps");
}


void CRecipe::displayNote() const{
    std::cout << "Recipe : " << this->getTitle() << std::endl;
    std::cout << "List of ingredients : " << std::endl;
    for (size_t i = 0; i < ingredients.size();i++) {
        std::cout << i << "." << ingredients[i] << std::endl;
    }
    std::cout << "Steps : " << std::endl;
    for (size_t i = 0; i < steps.size();i++) {
        std::cout << i <<"."<< steps[i] << std::endl;
    }
}

void CRecipe::contextMenu() {
    std::cout << "Available actions with Recipe " << this->getTitle() << std::endl;
    std::cout << "1. Add ingredient" << std::endl;
    std::cout << "2. Remove ingredient" << std::endl;
    std::cout << "3. Add steps" << std::endl;
    std::cout << "4. Remove steps" << std::endl;
    std::cout << "5. Edit title" << std::endl;
    std::cout << "6. Add tag" << std::endl;
    std::cout << "7. Remove tag" << std::endl;
    std::cout << "8. Print log record" << std::endl;
    std::cout << "9. Change date" << std::endl;

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
    if (option == 1) this->addIngredient();
    else if (option == 2) this->removeIngredient();
    else if (option == 3) this->addStep();
    else if (option == 4) this->removeStep();
    else if (option == 5) this->editTitle();
    else if (option == 6) this->addTag();
    else if (option == 7) this->removeTag();
    else if (option == 8) this->printLogRecord();
    else if (option == 9) this->changeDate();
    else std::cout << "Invalid option, returning back" << std::endl;
}

void CRecipe::exportNote(int type) {
    std::shared_ptr<CExporter> exportObj = nullptr;
    bool isMarkdown = false;
    bool isHtml = false;
    if (type == 1) {
        isHtml = true;
        exportObj = std::make_shared<CHtml>();
    }
    else if (type == 2) exportObj = std::make_shared<CTxt>();
    else if (type == 3) {
        exportObj = std::make_shared<CMarkDown>();
        isMarkdown = true;
    }

    std::string text_export;

    if (isMarkdown) {
        text_export += "# Recipe : " + this->getTitle() + "\n";
        text_export += "## Ingredients : \n";
        for (size_t i = 0; i < ingredients.size(); i++) {
            text_export += "> " + ingredients[i] + "\n";
        }
        text_export += "## Steps : \n";
        for (size_t i = 0; i < steps.size(); i++) {
            text_export += "> " + steps[i] + "\n";
        }
    }
    else if(isHtml){
        text_export += "<h1>RECIPE : " + this->getTitle() + "</h1>\n";
        text_export += "<h2>INGREDIENTS</h2>\n";
        for (size_t i = 0; i < ingredients.size(); i++) {
            text_export += ingredients[i] + "<br>\n";
        }
        text_export += "<h2>STEPS</h2>\n";
        for (size_t i = 0; i < steps.size(); i++) {
            text_export += steps[i] + "<br>\n";
        }
    }
    else {
        text_export += "*****\n";
        text_export += "RECIPE\n";
        text_export += this->getTitle() + "\n";
        text_export += "INGREDIENTS\n";
        for (size_t i = 0; i < ingredients.size(); i++) {
            text_export += ingredients[i] + "\n";
        }
        text_export += "+++++";
        text_export += "STEPS\n";
        for (size_t i = 0; i < steps.size(); i++) {
            text_export += steps[i] + "\n";
        }
        text_export += "*****\n";
    }
    exportObj->exportFunct(text_export, this->getTitle());
}

std::shared_ptr<CNote> CRecipe::copyPtr() {
    return std::make_shared<CRecipe>(*this);
}

bool CRecipe::containsText(const std::string &text_to_search) {
    std::string joinedText;
    for(const auto & elem : steps){
        joinedText += elem;
        joinedText += "\n";
    }
    for(const auto & elem : ingredients){
        joinedText += elem;
        joinedText += "\n";
    }

    std::string text_for_search = text_to_search;

    std::transform(joinedText.begin(), joinedText.end(), joinedText.begin(), [](unsigned char c) { return std::tolower(c); });
    std::transform(text_for_search.begin(), text_for_search.end(), text_for_search.begin(), [](unsigned char c) { return std::tolower(c); });

    size_t position = joinedText.find(text_for_search);
    if(position != std::string::npos) return true;
    return false;
}

bool CRecipe::importNote(std::ifstream & file) {
    std::string text;
    std::string line;
    std::string check_ing;
    std::getline(file,check_ing);
    bool passed = false;

    if(check_ing != "INGREDIENTS"){
        return false;
    }
    while (std::getline(file, line)) {
        if (line == "+++++") {
            passed = true;
            break;
        }
        this->ingredients.push_back(line);
    }
    if(!passed) return false;
    std::string check_step;
    std::getline(file,check_step);

    if(check_step != "STEPS"){
        return false;
    }

    while (std::getline(file, line)) {
        if (line == "*****") return true;
        this->steps.push_back(line);
    }
    return false;
}