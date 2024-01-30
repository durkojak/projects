#include "CToDoList.h"

CToDoList::CToDoList() : CNote("") {}
CToDoList::CToDoList(const std::string &name) : CNote(name) {
    this->setName(name);
}
CToDoList::~CToDoList() = default;

void CToDoList::addTask() {
    while (true) {
        std::string task_name;

        std::cout << "Task : ";
        std::getline(std::cin,task_name);

        if (strcasecmp(task_name.c_str(), "stop") == 0) break;

        task_status tmp{task_name, false};

        tasks.push_back(tmp);
        this->logRecord("Added task " + tmp.task);
    }
}

void CToDoList::removeTask() {
    std::cout << "Select the number of the task you would like to remove : ";
    std::string indexString;
    std::getline(std::cin,indexString);
    for(char c : indexString){
        if(!std::isdigit(c)){
            std::cout << "Invalid option, returning back" << std::endl;
            return;
        }
    }
    size_t index = std::stoi(indexString);
    if(index >= tasks.size()){
        std::cout << "Invalid index" << std::endl;
        return;
    }
    this->logRecord("Removed task " + tasks[index].task);
    this->tasks.erase(this->tasks.begin() + index);
}

void CToDoList::editTask() {
    size_t index;
    std::string newBody;
    std::cout << "Select the number of the task you would like to edit : ";
    std::cin >> index;
    std::cout << "Text of the edited task : ";
    std::cin >> newBody;
    this->logRecord("Changed " + tasks[index].task + " to " + newBody);
    this->tasks[index].task = newBody;
}

void CToDoList::changeStatus() {
    size_t index;
    std::cout << "Select the number of the task which status you would like to change : ";
    std::cin >> index;
    if (!tasks[index].status) {
        this->logRecord("Changed the status of " + tasks[index].task + " to ✓");
        tasks[index].status = true;
    } else {
        tasks[index].status = false;
        this->logRecord("Changed the status of " + tasks[index].task + " to X");
    }
}

void CToDoList::remainingTasks() {
    for (size_t i = 0; i < tasks.size(); i++) {
        if (!tasks[i].status) std::cout << tasks[i].task << std::endl;
    }
}

void CToDoList::displayNote()const {
    std::cout << "ToDoList " << this->getTitle() << std::endl;
    for (size_t i = 0; i < tasks.size(); i++) {
        std::string mark = "X";
        if (tasks[i].status) mark = "✓";
        std::cout << i << " " << tasks[i].task << " -- " << mark << std::endl;
    }
}

void CToDoList::contextMenu() {
    std::cout << "Available actions with ToDoList" << this->getTitle() << std::endl;
    std::cout << "1. Remove task" << std::endl;
    std::cout << "2. Show remaining tasks" << std::endl;
    std::cout << "3. Edit task" << std::endl;
    std::cout << "4. Add task" << std::endl;
    std::cout << "5. Change status of a task" << std::endl;
    std::cout << "6. Edit title" << std::endl;
    std::cout << "7. Add tag" << std::endl;
    std::cout << "8. Remove tag" << std::endl;
    std::cout << "9. Print log record" << std::endl;
    std::cout << "10. Change date" << std::endl;

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
    if (option == 1) this->removeTask();
    else if (option == 2) this->remainingTasks();
    else if (option == 3) this->editTask();
    else if (option == 4) this->addTask();
    else if (option == 5) this->changeStatus();
    else if (option == 6) this->editTitle();
    else if (option == 7) this->addTag();
    else if (option == 8) this->removeTag();
    else if (option == 9) this->printLogRecord();
    else if (option == 10) this->changeDate();
    else std::cout << "Invalid option, returning back" << std::endl;
}

void CToDoList::exportNote(int type) {

    std::shared_ptr<CExporter> exportObj = nullptr;
    bool isMarkdown = false;
    bool isHtml = false;
    if (type == 1) {
        isHtml = true;
        exportObj = std::make_shared<CHtml>();
    }
    if(type == 2) exportObj = std::make_shared<CTxt>();
    if (type == 3) {
        exportObj = std::make_shared<CMarkDown>();
        isMarkdown = true;
    }

    std::string text_export;

    if (isMarkdown) {
        text_export += "# ToDoList " + this->getTitle() + "\n";
        for (size_t i = 0; i < tasks.size(); i++) {
            if (tasks[i].status) text_export += "> " + tasks[i].task + " " + "✓\\" + "\n";
            else text_export += "> " + tasks[i].task + " " + "X\\" + "\n";
        }
    }
    else if(isHtml){
        text_export += "<h1>TODOLIST" + this->getTitle() + "</h1>\n";
        for (size_t i = 0; i < tasks.size(); i++) {
            if (tasks[i].status) {
                text_export += tasks[i].task + "\n";
                text_export += "DONE <br>\n";
            }
            else {
                text_export += tasks[i].task + "\n";
                text_export += "X<br>\n";
            }
        }
    }
    else {
        text_export += "*****\n";
        text_export += "TODOLIST";
        text_export += this->getTitle() + "\n";
        for (size_t i = 0; i < tasks.size(); i++) {
            if (tasks[i].status) {
                text_export += tasks[i].task + "\n";
                text_export += "✓\n";
            }
            else {
                text_export += tasks[i].task + "\n";
                text_export += "X\n";
            }
        }
        text_export += "*****";
    }
    exportObj->exportFunct(text_export, this->getTitle());
}

std::shared_ptr<CNote> CToDoList::copyPtr() {
    return std::make_shared<CToDoList>(*this);
}

bool CToDoList::containsText(const std::string &text_to_search) {
    std::string joinedText;
    for(const auto & elem : tasks){
        joinedText += elem.task;
        joinedText += "\n";
    }

    std::string text_for_search = text_to_search;

    std::transform(joinedText.begin(), joinedText.end(), joinedText.begin(), [](unsigned char c) { return std::tolower(c); });
    std::transform(text_for_search.begin(), text_for_search.end(), text_for_search.begin(), [](unsigned char c) { return std::tolower(c); });


    size_t position = joinedText.find(text_for_search);
    if(position != std::string::npos) return true;
    return false;
}

bool CToDoList::importNote(std::ifstream &file) {
    std::string line;
    int parity = 0;

    task_status tmp;
    while (std::getline(file, line)) {
        if (line == "*****" && parity % 2 == 0) return true;
        if (line == "*****" && parity % 2 == 1) return false;
        if(parity % 2 == 0){
            tmp.task = line;
        }
        if(parity % 2 == 1){
            if(line == "X") tmp.status = false;
            else if(line == "✓") tmp.status = true;
            else return false;

            this->tasks.push_back(tmp);
            tmp = {};
        }
        parity++;
    }
    return false;
}