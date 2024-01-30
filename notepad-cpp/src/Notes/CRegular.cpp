#include "CRegular.h"

CRegular::CRegular() : CNote("") {}

CRegular::CRegular(const std::string &name) : CNote(name) {
    this->setName(name);
}

CRegular::~CRegular() = default;


void CRegular::appendText() {
    std::string text;
    std::cout << "Write the content of the note : " << std::endl;
    std::getline(std::cin, text);
    std::cout << "User input: " << text << std::endl;
    this->body = text;
    this->logRecord("Added text");
}


void CRegular::displayNote() const {
    std::cout << "Regular note : " << this->getTitle() << std::endl;
    std::cout << "Content : " << this->body << std::endl;
}

void CRegular::contextMenu() {
    std::cout << "Available actions with Regular note " << this->getTitle() << std::endl;
    std::cout << "1. Append text" << std::endl;
    std::cout << "2. Edit title" << std::endl;
    std::cout << "3. Add tag" << std::endl;
    std::cout << "4. Remove tag" << std::endl;
    std::cout << "5. Print log record" << std::endl;
    std::cout << "6. Change date" << std::endl;

    std::string optionString;
    std::getline(std::cin, optionString);
    for (char c: optionString) {
        if (!std::isdigit(c)) {
            std::cout << "Invalid option, returning back" << std::endl;
            return;
        }
    }
    if(optionString.empty()) {
        std::cout << "Invalid option, returning back" << std::endl;
        return;
    }
    int option = std::stoi(optionString);
    if (option == 1) this->appendText();
    else if (option == 2) this->editTitle();
    else if (option == 3) this->addTag();
    else if (option == 4) this->removeTag();
    else if (option == 5) this->printLogRecord();
    else if (option == 6) this->changeDate();
    else std::cout << "Invalid option, returning back" << std::endl;
}

void CRegular::exportNote(int type) {

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

    std::string textToExport;
    if (isMarkdown) {
        textToExport += "# " + this->getTitle() + "\n";
        textToExport += this->body;
    }
    else if(isHtml){
        textToExport += "<h1>REGULAR : " + this->getTitle() + "</h1>\n";
        textToExport += this->body + "\n";
    }
    else {
        textToExport += "*****\n";
        textToExport += "REGULAR\n";
        textToExport += this->getTitle() + "\n";
        textToExport += this->body + "\n";
        textToExport += "*****";
    }
    exportObj->exportFunct(textToExport, this->getTitle());
}

std::shared_ptr<CNote> CRegular::copyPtr() {
    return std::make_shared<CRegular>(*this);
}


bool CRegular::containsText(const std::string &text_to_search) {
    std::string text_for_search = text_to_search;

    std::transform(this->body.begin(), this->body.end(), this->body.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    std::transform(text_for_search.begin(), text_for_search.end(), text_for_search.begin(),
                   [](unsigned char c) { return std::tolower(c); });


    size_t position = this->body.find(text_for_search);
    if (position != std::string::npos) return true;
    return false;
}

void CRegular::setBody(const std::string &body) {
    CRegular::body = body;
}

bool CRegular::importNote(std::ifstream &file) {
    std::string text = "";
    std::string line;
    bool success = false;
    while (std::getline(file, line)) {
        if (line == "*****") {
            success = true;
            break;
        }
        text += line;
        text += '\n';
    }
    if (!success || text == "") return false;
    this->setBody(text);
    return true;
}