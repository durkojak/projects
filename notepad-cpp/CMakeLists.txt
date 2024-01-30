cmake_minimum_required(VERSION 3.25)
project(durkojak)

set(CMAKE_CXX_STANDARD 14)

add_executable(durkojak
        src/main.cpp src/CNotesManager.h src/CDirectory.h src/CDirectory.cpp src/CConfigTool.h src/CNotesManager.cpp src/CConfigTool.cpp src/Export/CExporter.h src/Export/CExporter.cpp src/Export/CHtml.cpp src/Export/CHtml.h src/Export/CMarkDown.h src/Export/CMarkDown.cpp src/Export/CTxt.h src/Export/CTxt.cpp src/Filters/CFilter.h src/Filters/CDateFilter.h src/Filters/CDateFilter.cpp src/Filters/CFilter.cpp src/Filters/CTagFilter.h src/Filters/CTagFilter.cpp src/Sorting/CSorting.h src/Sorting/CDateSort.h src/Sorting/CDateSort.cpp src/Sorting/CSorting.cpp src/Sorting/CAlphabetSort.h src/Sorting/CAlphabetSort.cpp src/Notes/CDate.h src/Notes/CNote.cpp src/Notes/CDate.cpp src/Notes/CRecipe.h src/Notes/CRecipe.cpp src/Notes/CRegular.h src/Notes/CRegular.cpp src/Notes/CShoppingList.h src/Notes/CShoppingList.cpp src/Notes/CToDoList.h src/Notes/CToDoList.cpp src/Filters/CDirectoryFilter.h src/Filters/CDirectoryFilter.cpp src/Filters/CNameFilter.h src/Filters/CNameFilter.cpp src/Filters/CTextFilter.h src/Filters/CTextFilter.cpp src/Sorting/CSortClass.h src/Sorting/CSortClass.cpp)
