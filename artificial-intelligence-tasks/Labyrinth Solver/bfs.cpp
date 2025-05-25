#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <queue>
#include <map>
#include <atomic>
#include <thread>
#include <filesystem>
#include <cassert>

const std::string RED = "\033[41m";
const std::string RESET = "\033[0m";
const std::string GREEN = "\033[42m";
const std::string MAGENTA = "\033[45m";
const std::string BLUE = "\033[44m";


class CCoord {
public:
    CCoord() {}

    CCoord(int xCord, int yCord) : xCord(xCord), yCord(yCord) {}

    bool operator<(const CCoord &rhs) const {
        if (xCord < rhs.xCord)
            return true;
        if (rhs.xCord < xCord)
            return false;
        return yCord < rhs.yCord;
    }

    bool operator>(const CCoord &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const CCoord &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const CCoord &rhs) const {
        return !(*this < rhs);
    }

    bool operator==(const CCoord &rhs) const {
        return xCord == rhs.xCord &&
               yCord == rhs.yCord;
    }

    bool operator!=(const CCoord &rhs) const {
        return !(rhs == *this);
    }

    friend std::ostream &operator<<(std::ostream &os, const CCoord &coord) {
        os << "xCord: " << coord.xCord << " yCord: " << coord.yCord;
        return os;
    }

    int xCord;
    int yCord;
};

class CMap {
public:


    int mapWidth;
    int mapHeight;
    std::set<CCoord> mapBlockages = {};
    CCoord start = {};
    CCoord end = {};
    std::map<CCoord, CCoord> predecessorMap; // value is the predecessor
};


bool qContains(std::queue<CCoord> q, const CCoord &target) {
    while (!q.empty()) {
        if (q.front() == target)
            return true;
        q.pop();
    }
    return false;
}


void createFinalOutput(const CMap &labyrinthMap) {
    system("clear");
    CCoord currCoord = labyrinthMap.end;
    CCoord predCoord = labyrinthMap.predecessorMap.at(currCoord);
    std::set<CCoord> path = {};

    while (currCoord != predCoord) {
        path.insert(currCoord);
        currCoord = predCoord;
        predCoord = labyrinthMap.predecessorMap.at(predCoord);
    }
    path.insert(currCoord);


    for (int y = 0; y < labyrinthMap.mapHeight; y++) {
        for (int x = 0; x < labyrinthMap.mapWidth; x++) {
            CCoord printCoord(x, y);
            if (labyrinthMap.mapBlockages.contains(printCoord)) {
                // print X
                std::cout << "X";
            } else if (printCoord == labyrinthMap.start) {
                // print S
                std::cout << BLUE << "S" << RESET;
            } else if (printCoord == labyrinthMap.end) {
                // print E
                std::cout << BLUE << "E" << RESET;
            } else if (path.contains(printCoord)) {
                // print o
                std::cout << GREEN << "o" << RESET;
            } else if (labyrinthMap.predecessorMap.contains(printCoord)) {
                // print #
                std::cout << RED << "#" << RESET;
            } else {
                // print " "
                std::cout << " ";
            }

        }
        std::cout << std::endl;
    }

    std::cout << "---------------------------------------" << std::endl;

    std::cout << "S Start" << std::endl;
    std::cout << "E End" << std::endl;
    std::cout << "# Opened node" << std::endl;
    std::cout << "o Path" << std::endl;
    std::cout << "X Wall" << std::endl;
    std::cout << "space Fresh node" << std::endl;

    std::cout << "---------------------------------------" << std::endl;

    std::cout << "Nodes expanded : " << labyrinthMap.predecessorMap.size() - 1 << std::endl;
    std::cout << "Path length : " << path.size() - 1 << std::endl;


}

void createStepOutput(const CMap &labyrinthMap, const CCoord &currCoord, const std::queue<CCoord> &q,
                      const std::set<CCoord> &visited) {
    for (int y = 0; y < labyrinthMap.mapHeight; y++) {
        for (int x = 0; x < labyrinthMap.mapWidth; x++) {
            CCoord printCoord(x, y);
            if (labyrinthMap.mapBlockages.contains(printCoord)) {
                // print X
                std::cout << "X";
            } else if (printCoord == labyrinthMap.start) {
                // print S
                std::cout << BLUE << "S" << RESET;
            } else if (printCoord == labyrinthMap.end) {
                // print E
                std::cout << BLUE << "E" << RESET;
            } else if (currCoord == printCoord) {
                // print o
                std::cout << MAGENTA << "!" << RESET;
            } else if (qContains(q, printCoord)) {
                // print #
                std::cout << GREEN << "?" << RESET;
            } else if (visited.contains(printCoord)) {
                std::cout << RED << "C" << RESET;
            } else {
                // print " "
                std::cout << " ";
            }

        }
        std::cout << std::endl;
    }
}

void createMap(const std::string &filePath, CMap &labyrinthMap) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filePath << std::endl;
        return;
    }

    std::string line;
    int y = 0;
    while (std::getline(file, line)) {
        if (line.find("start") != std::string::npos) {
            int x, y;
            sscanf(line.c_str(), "start %d, %d", &x, &y);
            labyrinthMap.start = CCoord(x, y);
        } else if (line.find("end") != std::string::npos) {
            int x, y;
            sscanf(line.c_str(), "end %d, %d", &x, &y);
            labyrinthMap.end = CCoord(x, y);
        } else {
            if (labyrinthMap.mapWidth == 0) {
                labyrinthMap.mapWidth = line.length();
            }
            for (int x = 0; x < line.length(); ++x) {
                if (line[x] == 'X') {
                    labyrinthMap.mapBlockages.insert(CCoord(x, y));
                }
            }
            ++y;
        }
    }
    labyrinthMap.mapHeight = y;

    file.close();
}

bool checkEnd(const CCoord &currCord, const CCoord &endCord) {
    return currCord == endCord;
}

bool checkValidCoord(const CCoord &newCoord, const std::set<CCoord> &visited, const CMap &labyrinthMap) {
    if (visited.contains(newCoord))
        return false;

    if (labyrinthMap.mapBlockages.contains(newCoord))
        return false;

    if (newCoord.xCord >= labyrinthMap.mapWidth ||
        newCoord.xCord < 0 ||
        newCoord.yCord >= labyrinthMap.mapHeight ||
        newCoord.yCord < 0)
        return false;

    return true;
}


bool agentMove(std::queue<CCoord> &q, std::set<CCoord> &visited, const CCoord &currCoord, CMap &labyrinthMap,
               bool stepVisualBool, bool endingVisualBool, int speedVisualisation) {
    // move up
    CCoord moveUp(currCoord.xCord, currCoord.yCord - 1);
    if (checkValidCoord(moveUp, visited, labyrinthMap)) {
        labyrinthMap.predecessorMap[moveUp] = currCoord;
        if (checkEnd(moveUp, labyrinthMap.end)) {
            if (endingVisualBool)
                createFinalOutput(labyrinthMap);
            return true;
        }
        q.push(moveUp);
        visited.insert(moveUp);
    }

    // move down
    CCoord moveDown(currCoord.xCord, currCoord.yCord + 1);
    if (checkValidCoord(moveDown, visited, labyrinthMap)) {
        labyrinthMap.predecessorMap[moveDown] = currCoord;
        if (checkEnd(moveDown, labyrinthMap.end)) {
            if (endingVisualBool)
                createFinalOutput(labyrinthMap);
            return true;
        }
        q.push(moveDown);
        visited.insert(moveDown);
    }

    // move left
    CCoord moveLeft(currCoord.xCord - 1, currCoord.yCord);
    if (checkValidCoord(moveLeft, visited, labyrinthMap)) {
        labyrinthMap.predecessorMap[moveLeft] = currCoord;
        if (checkEnd(moveLeft, labyrinthMap.end)) {
            if (endingVisualBool)
                createFinalOutput(labyrinthMap);
            return true;
        }
        q.push(moveLeft);
        visited.insert(moveLeft);
    }

    // move right
    CCoord moveRight(currCoord.xCord + 1, currCoord.yCord);
    if (checkValidCoord(moveRight, visited, labyrinthMap)) {
        labyrinthMap.predecessorMap[moveRight] = currCoord;
        if (checkEnd(moveRight, labyrinthMap.end)) {
            if (endingVisualBool)
                createFinalOutput(labyrinthMap);
            return true;
        }
        q.push(moveRight);
        visited.insert(moveRight);
    }

    if (stepVisualBool) {
        createStepOutput(labyrinthMap, currCoord, q, visited);
        std::this_thread::sleep_for(std::chrono::milliseconds(speedVisualisation));
        system("clear");
    }
    return false;
}

bool runBfs(CMap &labyrinthMap,  bool stepVisualBool,bool endingVisualBool, int speedVisualisation) {
    std::queue<CCoord> q;

    std::set<CCoord> visited;

    q.push(labyrinthMap.start);
    visited.insert(labyrinthMap.start);
    labyrinthMap.predecessorMap[labyrinthMap.start] = labyrinthMap.start;

    if (labyrinthMap.start == labyrinthMap.end) {
        if(endingVisualBool)
            createFinalOutput(labyrinthMap);
        return true;
    }

    while (!q.empty()) {
        CCoord currCoord = q.front();
        q.pop();

        if (agentMove(q, visited, currCoord, labyrinthMap,stepVisualBool,endingVisualBool,speedVisualisation)) {
            return true;
        }
    }

    return false;

}


int main() {
    std::string directoryPath = "test_data";

    for (const auto &entry: std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            std::string filePath = entry.path().string();
            CMap labyrinthMap = {};
            createMap(filePath, labyrinthMap);

            bool result = runBfs(labyrinthMap, false,false,0);
            if (!result) {
                std::cerr << "BFS failed on file: " << filePath << std::endl;
                assert(result);
            }

            std::cout << "BFS Passed: " << filePath << std::endl;
        }
    }
    std::cout << "All tests passed." << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "SELECT A .TXT FOR VISUALISATION" << std::endl;

    std::string visualisationFilePath;
    int choiceNum = 1;
    std::map<int, std::string> choices;

    for (const auto &entry: std::filesystem::directory_iterator(directoryPath)) {


        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            std::string filePath = entry.path().string();
            choices[choiceNum] = filePath;
            std::cout << choiceNum << ". " << filePath << std::endl;
            choiceNum++;
        }


    }
    int userChoice;

    std::cout << "Enter the number of the file you want to select: ";
    std::cin >> userChoice;

    if (choices.find(userChoice) == choices.end()) {
        std::cerr << "Invalid choice." << std::endl;
        return 1;
    }

    visualisationFilePath = choices.at(userChoice);


    bool steppingVisualisation;
    bool finalPathVisualisation;
    char steppingVisualChoice;
    char finalPathVisualChoice;
    int speedVisualisation;

    std::cout << "Do you want stepping visualisation? Y/N: ";
    std::cin >> steppingVisualChoice;
    steppingVisualisation = (steppingVisualChoice == 'Y' || steppingVisualChoice == 'y');

    if(steppingVisualisation){
        std::cout << "Write down the stepping visualisation speed in miliseconds : ";
        std::cin >> speedVisualisation;
    }

    std::cout << "Do you want to see the final path? Y/N: ";
    std::cin >> finalPathVisualChoice;
    finalPathVisualisation = (finalPathVisualChoice == 'Y' || finalPathVisualChoice == 'y');



    CMap labyrinthMap = {};
    createMap(visualisationFilePath, labyrinthMap);
    runBfs(labyrinthMap, steppingVisualisation, finalPathVisualisation,speedVisualisation);

    return 0;
}

