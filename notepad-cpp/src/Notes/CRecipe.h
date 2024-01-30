#ifndef DURKOJAK_CRECIPE_H
#define DURKOJAK_CRECIPE_H
#include "CNote.h"
#include <cstring>

/**
* @brief Trieda CRecipe reprezentuje poznámku vo forme receptu
* */
class CRecipe : public CNote {
public:
    CRecipe();
    ~CRecipe() override;
    explicit CRecipe(const std::string & name);

    virtual void addIngredient();
    virtual void removeIngredient();

    virtual void addStep();
    virtual void removeStep();


    std::shared_ptr<CNote> copyPtr() override;


    void displayNote()const override;
    void contextMenu() override;
    void exportNote(int type) override;
    bool importNote(std::ifstream& file) override;
    bool containsText(const std::string & text_to_search) override;

private:
    std::vector<std::string> ingredients;
    std::vector<std::string> steps;

};



#endif //DURKOJAK_CRECIPE_H
