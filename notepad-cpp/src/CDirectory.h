#ifndef DURKOJAK_CDIRECTORY_H
#define DURKOJAK_CDIRECTORY_H

#include "Notes/CNote.h"
#include "Notes/CShoppingList.h"
#include "Notes/CRegular.h"
#include "Notes/CRecipe.h"
#include "Notes/CToDoList.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <ios>
#include <limits>
#include "Filters/CFilter.h"
#include "Filters/CDateFilter.h"
#include "Filters/CNameFilter.h"
#include "Filters/CDirectoryFilter.h"
#include "Filters/CTagFilter.h"
#include "Filters/CTextFilter.h"
#include "Sorting/CSorting.h"
#include "Sorting/CAlphabetSort.h"
#include "Sorting/CDateSort.h"
#include "Sorting/CSortClass.h"
#include "CConfigTool.h"
#include <memory>

/**
 * @brief Trieda CDirectory slúži na prácu s directory a staranie sa o notes objekty.
 *        name = meno directory
 *        notes = vektor poznámok daného directory
 *        master_directories = posloupnost directories od root až po danú poznámku
 *        subdirectories = vektor directories v danom directory
 * */
class CDirectory {
public:
    bool operator==(const CDirectory & other) const;

    explicit CDirectory(const std::string & name);
    CDirectory(const CDirectory & other);
    CDirectory& operator=(const CDirectory & other);

    bool addSubdirectory(const std::string & name);
    bool removeSubdirectory(const std::string & name);
    /**
 * @brief Funkcia switchDirectory slúži na prepnutie do nejakého subdirectory v danom directory
 * @return pointer na cieľový directory
 * */
    std::shared_ptr<CDirectory> switchDirectory();
/**
 * @brief Funkcia addNote slúži na vytvorenie novej poznámky, na základe voľby usera.
 * */
    void addNote();
    void removeNote(const std::string & name);
    /**
 * @brief Funkcia isNote slúži na skontrolovanie súboru, ktorý user chce importovať, ak to prejde kontrolou, vytvorí sa objekt, na ktorý sa zavolá import
 * @param configTool načítanie import directory
 * @param filename názov súboru, ktorý chceme importovať
 * */
    void isNote(const std::string & filename,CConfigTool & configTool);
    /**
 * @brief Funkcia findNote slúži ako tool pre viacero funkcií, zisti to index poznámky a na základe inštrukcie to urobí danú akciu
 * @param name názov poznámky
 * @param mode 0 je ukázanie obsahu poznámky, 1 je menu danej poznámky, 2 slúži na export
 * @param type využíva sa pre export, určí či ide o HTML, MarkDown alebo Txt
 * */
    void findNote(const std::string & name, int mode,int type) const;
    void showContent() const;

    /**
 * @brief Funkcia showSortMenu vypýta druh sortu, vysortí poznámky a printne ich
 * @param core_directory root directory, z ktorého získam všetky poznámky vo filesystéme vďaka getAllNote
 * */
    void showSortMenu(std::shared_ptr<CDirectory> &core_directory);
    /**
* @brief Funkcia exportMenu slúži na výber druhu exportu a na základe množiny určenej vyhľadaním aplikovanie exportu
* @return vektor vyfiltrovaných notes, táto return hodnota sa využíva v exporte
* */
    void exportMenu();
    /**
* @brief Funkcia showFilterMenu slúži na zvolenie typu filtru, aplikovanie filtru a printnutie vyfiltrovaných poznámok
* @param core_directory root directory, z ktorého získam všetky poznámky vo filesystéme vďaka getAllNotes
* @return vektor vyfiltrovaných notes, táto return hodnota sa využíva v exporte
* */
    std::vector<std::shared_ptr<CNote>> showFilterMenu(std::shared_ptr<CDirectory> & core_directory) const;

    const std::string &getName() const;
    /**
 * @brief Funkcia getAllNotes slúži na získanie všetkých poznámok vo filesystéme, využíva rekurziu na prejdenie všetkých subdirectories
 * @param allNotes vektor, do ktorého funkcia uloží všetky poznámky
 * */
    void getAllNotes(std::vector<std::shared_ptr<CNote>> & allNotes) const;



    std::vector<std::shared_ptr<CNote>> notes;
    std::vector<std::shared_ptr<CDirectory>> subdirectories;
    std::vector<std::string> master_directories;
private:
    std::string name;


};

#endif //DURKOJAK_CDIRECTORY_H
