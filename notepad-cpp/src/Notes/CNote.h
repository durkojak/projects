#ifndef DURKOJAK_CNOTE_H
#define DURKOJAK_CNOTE_H
#include<string>
#include <vector>
#include "CDate.h"
#include "../Export/CExporter.h"
#include "../Export/CHtml.h"
#include "../Export/CMarkDown.h"
#include "../Export/CTxt.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <limits>
#include <memory>
#include <fstream>
#include <cctype>
#include <cstring>

/**
* @brief Abstraktná parent trieda CNote reprezentuje poznámku. Má funkcie, ktoré majú všetky poznámky spoločné ale aj nejaké abstraktné.
*        master_directories = posloupnost directories od root až po poznámku
*        name = meno poznámky
*        tags = vektor tagov
*        date_of_creation = dátum vytvorenia poznámky
*        log = vektor zmien danej poznámky
* */
class CNote {
public:
    explicit CNote(const std::string & name);
    CNote();
    virtual ~CNote();

    /**
* @brief Metóda nameNote slúži na pomenovanie novej poznámky
* */
    virtual void nameNote();
    virtual std::string getTitle() const;
    virtual void editTitle();
    void setName(const std::string &name);

    virtual void addTag();
    virtual void removeTag();


    /**
* @brief Metóda logRecord slúži na zápis do logu danej poznámky
* @param action zmena v poznámke, ktorá bude zapísaná do logu
* */
    virtual void logRecord(const std::string & action);
    virtual void printLogRecord()const;

    virtual void createdDate();
    virtual void changeDate();
    const CDate &getDateOfCreation() const;


    /**
* @brief Abstraktná metóda importNote slúži na importovanie .txt poznámok
* */
    virtual bool importNote(std::ifstream& file) = 0;
    virtual std::shared_ptr<CNote> copyPtr() = 0;
    virtual void displayNote() const = 0;
    /**
* @brief Abstraktná metóda contextMenu ukáže užívateľovi možné akcie s daným druhom poznámky a zoberie user input
* */
    virtual void contextMenu() = 0;
    /**
* @brief Abstraktná metóda exportNote prichystá text poznámky určenej na export
* @param type určuje druh formátu exportu
* */
    virtual void exportNote(int type) = 0;
    /**
* @brief Abstraktná metóda containsText zistí, či sa vyskytuje hľadaný text v poznámke
* @param text_to_search hľadaný text
* */
    virtual bool containsText(const std::string & text_to_search) = 0;





    std::vector<std::string> tags;
    std::vector<std::string> master_directories;

private:
    std::string name;
    std::vector<std::string> log;
    CDate date_of_creation = {0,0,0,0,0,0};

};


#endif //DURKOJAK_CNOTE_H
