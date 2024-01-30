#include "CHtml.h"
CHtml::CHtml() :CExporter(){}

void CHtml::exportFunct(const std::string& text,const std::string& filename) {
    std::string nameOfFile = filename;
    nameOfFile += ".html";
    std::ofstream file(nameOfFile);

    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    file << "<html>\n";
    file << "<body>\n";
    file << "<p>" << text << "</p>\n";
    file << "</body>\n";
    file << "</html>\n";

    file.close();



    std::cout << "HTML conversion completed. Output file: " << nameOfFile << std::endl;


}








