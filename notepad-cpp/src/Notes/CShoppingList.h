#ifndef DURKOJAK_CSHOPPINGLIST_H
#define DURKOJAK_CSHOPPINGLIST_H
#include "CNote.h"
#include <cstring>

/**
* @brief Struct ShoppingItem reprezentuje položku v nákupnom zozname
* */
struct ShoppingItem{
    std::string item;
    double price;
};

/**
* @brief Trieda CShoppingList reprezentuje poznámku vo forme nákupného zoznamu
* */
class CShoppingList : public CNote {
public:
    CShoppingList();
    explicit CShoppingList(const std::string & name);
    ~CShoppingList() override;
    std::shared_ptr<CNote> copyPtr() override;

    virtual void addItem();
    virtual void removeItem();

    bool importNote(std::ifstream &file) override;
    void exportNote(int type) override;

    /**
* @brief Metóda getPrice vypočíta celkovú cenu nákupu
* */
    virtual void getPrice() const;
    void displayNote()const override;
    void contextMenu() override;

    bool containsText(const std::string & text_to_search) override;

private:
    std::vector<ShoppingItem> shopping_list;

};


#endif //DURKOJAK_CSHOPPINGLIST_H
