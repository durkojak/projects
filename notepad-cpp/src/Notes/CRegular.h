#ifndef DURKOJAK_CREGULAR_H
#define DURKOJAK_CREGULAR_H


#include "CNote.h"

/**
* @brief Trieda CRegular reprezentuje obyčajnú textovú poznámku
* */
class CRegular : public CNote{
public:
    CRegular();
    explicit CRegular(const std::string & name);
    ~CRegular() override;
    std::shared_ptr<CNote> copyPtr() override;


    void setBody(const std::string &body);
    virtual void appendText();
    bool containsText(const std::string & text_to_search) override;

    void displayNote()const override;
    void contextMenu() override;

    void exportNote(int type) override;
    bool importNote(std::ifstream& file) override;

private:
    std::string body;
};

#endif //DURKOJAK_CREGULAR_H
