#ifndef DURKOJAK_CTODOLIST_H
#define DURKOJAK_CTODOLIST_H


#include "CNote.h"

/**
* @brief Struct task_status reprezentuje jednu úlohu v zozname a jej stav splnenia
* */
struct task_status{
    std::string task;
    bool status;
};
/**
* @brief Trieda CToDoList reprezentuje poznámku vo forme to do listu
* */
class CToDoList : public CNote {
public:
    CToDoList();
    explicit CToDoList(const std::string & name);
    ~CToDoList() override;
    std::shared_ptr<CNote> copyPtr() override;

    virtual void addTask();
    virtual void removeTask();
    virtual void editTask();
    /**
* @brief Metóda remainingTasks vypíše zostávajúce úlohy
* */
    virtual void remainingTasks();

    virtual void changeStatus();

    bool importNote(std::ifstream &file) override;
    void displayNote() const override;
    void contextMenu() override;
    void exportNote(int type) override;

    bool containsText(const std::string & text_to_search) override;
private:
    std::vector<task_status> tasks;

};


#endif //DURKOJAK_CTODOLIST_H
