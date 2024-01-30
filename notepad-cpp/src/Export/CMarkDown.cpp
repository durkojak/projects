#include "CMarkDown.h"

CMarkDown::CMarkDown() : CExporter(){}

void CMarkDown::exportFunct(const std::string &text, const std::string &filename) {
    std::string nameOfFile = filename;
    nameOfFile += ".md";
    std::ofstream file(nameOfFile);

    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    file << text;

    file.close();



    std::cout << "Markdown conversion completed. Output file: " << nameOfFile << std::endl;


}


