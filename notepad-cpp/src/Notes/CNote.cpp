#include "CNote.h"
CNote::CNote() {
    this->name = "";
}
CNote::CNote(const std::string & name) {
    this->name = name;
}

CNote::~CNote() = default;

void CNote::nameNote() {
    std::string name;
    std::cout << "Type a name for the note : ";
    std::getline(std::cin,name);
    this->name = name;
}

std::string CNote::getTitle() const {
    return this->name;
}

void CNote::editTitle() {
    std::cout << "New title: " << std::endl;
    std::string newTitle;
    std::getline(std::cin,newTitle);

    this->logRecord("Changed the name from " + this->name + " to " + newTitle);
    this->name = newTitle;
}
void CNote::addTag(){
    std::cout << "Add tag: " << std::endl;
    std::string newTag;
    std::getline(std::cin,newTag);

    this->logRecord("Added tag " + newTag);
    tags.push_back(newTag);
}
void CNote::removeTag(){
    std::cout << "Tag to be removed : ";

    std::string removedTag;
    std::getline(std::cin,removedTag);

    auto it = find(tags.begin(),tags.end(),removedTag);

    if(it != tags.end()) tags.erase(it);
    else{
        std::cout << "Tag wasn't found" << std::endl;
        return;
    }
    this->logRecord("Removed tag " + removedTag);

}


void CNote::createdDate(){
    std::time_t currentTime = std::time(nullptr);
    std::string currentTimeString = std::ctime(&currentTime);
    std::tm* currentTimeInfo = std::localtime(&currentTime);

    int year = currentTimeInfo->tm_year + 1900;
    int month = currentTimeInfo->tm_mon + 1;
    int day = currentTimeInfo->tm_mday;
    int hour = currentTimeInfo->tm_hour;
    int minute = currentTimeInfo->tm_min;
    int second = currentTimeInfo->tm_sec;
    CDate tmp{year,month,day,hour,minute,second};
    date_of_creation = tmp;
    this->logRecord("Created this note named " + this->name + " " + currentTimeString);
}

const CDate &CNote::getDateOfCreation() const {
    return date_of_creation;
}


void CNote::logRecord(const std::string & action) {
    log.push_back(action);
}


void CNote::printLogRecord() const {
    std::cout << "*** LOG RECORD ***" << std::endl;
    for(size_t i = 0;i<log.size();i++){
        std::cout << log[i] << std::endl;
    }
    std::cout << "*** LOG END ***" << std::endl;
}

void CNote::changeDate() {
    std::string yearString, monthString, dayString;
    std::cout << "Type date parameters" << std::endl;
    std::cout << "Year : ";
    std::getline(std::cin,yearString);

    for(const char c : yearString){
        if(!isdigit(c)){
            std::cout << "Invalid input" << std::endl;
            return;
        }
    }
    std::cout << "Month : ";
    std::getline(std::cin,monthString);

    for(const char c : monthString){
        if(!isdigit(c)){
            std::cout << "Invalid input" << std::endl;
            return;
        }
    }
    std::cout << "Day : ";
    std::getline(std::cin,dayString);
    for(const char c : dayString){
        if(!isdigit(c)){
            std::cout << "Invalid input" << std::endl;
            return;
        }
    }


    int day = std::stoi(dayString);
    int month = std::stoi(monthString);
    int year = std::stoi(yearString);

    std::vector<int> daysInMonths = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(day < 1 || day > daysInMonths[month-1] || month < 1 || month > 12){
        std::cout << "Invalid date." << std::endl;
        return;
    }

    this->date_of_creation.setDay(day);
    this->date_of_creation.setMonth(month);
    this->date_of_creation.setYear(year);
    this->logRecord("Changed date to " + std::to_string(year) + " " + std::to_string(month) + " " + std::to_string(day));

}
void CNote::setName(const std::string &name) {
    this->name = name;
}

