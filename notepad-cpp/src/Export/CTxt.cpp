#include "CTxt.h"

void CTxt::exportFunct(const std::string &text, const std::string &filename) {
    std::string nameOfFile = filename;
    nameOfFile += ".txt";
    std::ofstream file(nameOfFile);

    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    file << text;

    file.close();



    std::cout << "AsciiDoc conversion completed. Output file: " << nameOfFile << std::endl;
}

CTxt::CTxt() :CExporter() {}








