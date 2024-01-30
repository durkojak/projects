#include "CNotesManager.h"

void CNotesManager::run(CConfigTool & configTool) {
    core_directory = std::make_shared<CDirectory>("root");
    core_directory->master_directories.emplace_back("root");
    ptr_user = core_directory;

    std::cout << "Welcome to NotesManager 1.0 created by durkojak!" << std::endl;

    std::time_t currentTime = std::time(nullptr);
    std::string currentTimeString = std::ctime(&currentTime);
    std::cout << "Current time: " << currentTimeString;

    while (true) {
        std::cout << "+--------------------------+" << std::endl;
        std::cout << "          DIR:" << ptr_user->getName() << std::endl;
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "1. Create a new subdirectory" << std::endl;
        std::cout << "2. Remove an existing subdirectory" << std::endl;
        std::cout << "3. Create a new note" << std::endl;
        std::cout << "4. Display notes and subdirectories of current directory" << std::endl;
        std::cout << "5. Display the content of a specific note" << std::endl;
        std::cout << "6. Access a specific note menu" << std::endl;
        std::cout << "7. Switch to a subdirectory" << std::endl;
        std::cout << "8. Switch back to the root directory" << std::endl;
        std::cout << "9. Remove an existing note" << std::endl;
        std::cout << "10. EXPORT MENU" << std::endl;
        std::cout << "11. Look for notes via filters" << std::endl;
        std::cout << "12. Sort all the notes" << std::endl;
        std::cout << "13. Import a .txt note" << std::endl;
        std::cout << "0. Turn off NotesManager 1.0" << std::endl;
        std::cout << "+--------------------------+" << std::endl;

        std::cout << "Your choice: ";
        int option;
        if (!(std::cin >> option)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer." << std::endl;
            continue;
        }
        else if (option == 0) break;

        else if (option == 1) {
            std::string name;
            std::cout << "Name of the subdirectory : ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin,name);
            ptr_user->addSubdirectory(name);
        }
        else if(option == 2){
            std::string name;
            std::cout << "Name of the subdirectory : ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin,name);
            ptr_user->removeSubdirectory(name);
        }

        else if(option == 3) ptr_user->addNote();

        else if (option == 4) ptr_user->showContent();

        else if(option == 5){
            std::string name;
            std::cout << "Name of the note : ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin,name);
            ptr_user->findNote(name,0,0);
        }
        else if(option == 6){
            std::string name;
            std::cout << "Name of the note : ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin,name);
            ptr_user->findNote(name,1,0);
        }
        else if(option == 7) ptr_user = ptr_user->switchDirectory();

        else if(option == 8) ptr_user = core_directory;

        else if(option == 9){
            std::string name;
            std::cout << "Name of the note : ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin,name);
            ptr_user->removeNote(name);
        }
        else if(option == 10) core_directory->exportMenu();
        else if(option == 11) core_directory->showFilterMenu(core_directory);

        else if(option == 12) core_directory->showSortMenu(core_directory);
        else if(option == 13) {
            std::string filename;
            std::cout << "Enter filename: " << std::endl;
            std::cin >> filename;
            ptr_user->isNote(filename,configTool);
        }
        else std::cerr << "Not a valid option, choose again." << std::endl;
    }
    return;
}

CNotesManager::CNotesManager() = default;
