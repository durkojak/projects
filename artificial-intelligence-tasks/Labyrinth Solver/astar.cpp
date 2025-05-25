#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <queue>
#include <map>
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

class CCoordHeuristic {
public:
    CCoordHeuristic() : heuristicValue(0), manhattanDist(0), currPathLength(0) {}

    CCoordHeuristic(const CCoord &other) {
        this->elemCoord = other;
    }

    void setHeuristicValue(const CCoordHeuristic &pred, int edgeLength, const CCoord &end) {
        this->manhattanDist = std::abs(elemCoord.xCord - end.xCord) +
                              std::abs(elemCoord.yCord - end.yCord);
        this->currPathLength = pred.currPathLength + edgeLength;
        this->heuristicValue = currPathLength + manhattanDist;
    }

    bool operator<(const CCoordHeuristic &rhs) const {
        return elemCoord < rhs.elemCoord;
    }

    bool operator>(const CCoordHeuristic &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const CCoordHeuristic &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const CCoordHeuristic &rhs) const {
        return !(*this < rhs);
    }

    bool operator==(const CCoordHeuristic &rhs) const {
        return elemCoord == rhs.elemCoord;
    }

    bool operator!=(const CCoordHeuristic &rhs) const {
        return !(rhs == *this);
    }


    CCoord elemCoord;
    int heuristicValue;
    int manhattanDist;
    int currPathLength;
};

class CMap {
public:


    int mapWidth;
    int mapHeight;
    std::set<CCoord> mapBlockages = {};
    CCoord start = {};
    CCoord end = {};
    std::map<CCoordHeuristic, CCoordHeuristic> predecessorMap; // value is the predecessor
};


struct ComparePriority {
    bool operator()(const CCoordHeuristic &a, const CCoordHeuristic &b) const {
        return a.heuristicValue > b.heuristicValue;
    }
};

bool qContains(std::priority_queue<CCoordHeuristic, std::vector<CCoordHeuristic>, ComparePriority> priorQ,
               const CCoordHeuristic &target) {
    while (!priorQ.empty()) {
        if (priorQ.top() == target)
            return true;
        priorQ.pop();
    }
    return false;
}


void createFinalOutput(const CMap &labyrinthMap) {
    system("clear");
    CCoord currCoord = labyrinthMap.end;
    CCoord predCoord = labyrinthMap.predecessorMap.at(currCoord).elemCoord;
    std::set<CCoord> path = {};

    while (currCoord != predCoord) {
        path.insert(currCoord);
        currCoord = predCoord;
        predCoord = labyrinthMap.predecessorMap.at(predCoord).elemCoord;
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

void createStepOutput(const CMap &labyrinthMap, const CCoordHeuristic &currCoord,
                      const std::priority_queue<CCoordHeuristic, std::vector<CCoordHeuristic>, ComparePriority> &priorQ,
                      const std::set<CCoordHeuristic> &visited) {
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
                std::cout << MAGENTA << "!" << RESET;
            } else if (qContains(priorQ, printCoord)) {
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

bool checkEnd(const CCoordHeuristic &currCord, const CCoordHeuristic &endCord) {
    return currCord == endCord;
}

bool
checkValidCoord(const CCoordHeuristic &newCoord, const std::set<CCoordHeuristic> &visited, const CMap &labyrinthMap) {
    if (visited.contains(newCoord)){
        auto it = visited.find(newCoord);
        CCoordHeuristic foundElement = *it;

        if(foundElement.heuristicValue <= newCoord.heuristicValue){
            return false;
        }
        else{
            return true;
        }
    }

    if (labyrinthMap.mapBlockages.contains(newCoord.elemCoord))
        return false;

    if (newCoord.elemCoord.xCord >= labyrinthMap.mapWidth ||
        newCoord.elemCoord.xCord < 0 ||
        newCoord.elemCoord.yCord >= labyrinthMap.mapHeight ||
        newCoord.elemCoord.yCord < 0)
        return false;

    return true;
}


bool agentMove(std::priority_queue<CCoordHeuristic, std::vector<CCoordHeuristic>, ComparePriority> &priorQ,
               std::set<CCoordHeuristic> &visited, const CCoordHeuristic &currCoord, CMap &labyrinthMap,
               bool stepVisualBool, bool endingVisualBool, int speedVisualisation) {
    // move up
    CCoord moveUp(currCoord.elemCoord.xCord, currCoord.elemCoord.yCord - 1);
    CCoordHeuristic moveUpWithHeuristic(moveUp);
    moveUpWithHeuristic.setHeuristicValue(currCoord, 1, labyrinthMap.end);

    if (checkValidCoord(moveUpWithHeuristic, visited, labyrinthMap)) {
        labyrinthMap.predecessorMap[moveUpWithHeuristic] = currCoord;
        if (checkEnd(moveUpWithHeuristic, labyrinthMap.end)) {
            if (endingVisualBool)
                createFinalOutput(labyrinthMap);
            return true;
        }
        priorQ.emplace(moveUpWithHeuristic);
        visited.insert(moveUpWithHeuristic);
    }

    // move down
    CCoord moveDown(currCoord.elemCoord.xCord, currCoord.elemCoord.yCord + 1);
    CCoordHeuristic moveDownWithHeuristic(moveDown);
    moveDownWithHeuristic.setHeuristicValue(currCoord, 1, labyrinthMap.end);

    if (checkValidCoord(moveDownWithHeuristic, visited, labyrinthMap)) {
        labyrinthMap.predecessorMap[moveDownWithHeuristic] = currCoord;
        if (checkEnd(moveDownWithHeuristic, labyrinthMap.end)) {
            if (endingVisualBool)
                createFinalOutput(labyrinthMap);
            return true;
        }
        priorQ.emplace(moveDownWithHeuristic);
        visited.insert(moveDownWithHeuristic);

    }

    // move left
    CCoord moveLeft(currCoord.elemCoord.xCord - 1, currCoord.elemCoord.yCord);
    CCoordHeuristic moveLeftWithHeuristic(moveLeft);
    moveLeftWithHeuristic.setHeuristicValue(currCoord, 1, labyrinthMap.end);

    if (checkValidCoord(moveLeftWithHeuristic, visited, labyrinthMap)) {
        labyrinthMap.predecessorMap[moveLeftWithHeuristic] = currCoord;
        if (checkEnd(moveLeftWithHeuristic, labyrinthMap.end)) {
            if (endingVisualBool)
                createFinalOutput(labyrinthMap);
            return true;
        }
        priorQ.emplace(moveLeftWithHeuristic);
        visited.insert(moveLeftWithHeuristic);

    }

    // move right
    CCoord moveRight(currCoord.elemCoord.xCord + 1, currCoord.elemCoord.yCord);
    CCoordHeuristic moveRightWithHeuristic(moveRight);
    moveRightWithHeuristic.setHeuristicValue(currCoord, 1, labyrinthMap.end);
    if (checkValidCoord(moveRightWithHeuristic, visited, labyrinthMap)) {
        labyrinthMap.predecessorMap[moveRightWithHeuristic] = currCoord;
        if (checkEnd(moveRightWithHeuristic, labyrinthMap.end)) {
            if (endingVisualBool)
                createFinalOutput(labyrinthMap);
            return true;
        }
        priorQ.emplace(moveRightWithHeuristic);
        visited.insert(moveRightWithHeuristic);

    }

    if (stepVisualBool) {
        createStepOutput(labyrinthMap, currCoord, priorQ, visited);
        std::this_thread::sleep_for(std::chrono::milliseconds(speedVisualisation));
        system("clear");
    }
    return false;
}

bool runAstar(CMap &labyrinthMap, bool stepVisualBool,bool endingVisualBool, int speedVisualisation) {
    std::priority_queue<CCoordHeuristic, std::vector<CCoordHeuristic>, ComparePriority> priorQ;
    std::set<CCoordHeuristic> visited;

    CCoordHeuristic start(labyrinthMap.start);
    start.setHeuristicValue(start, 0, labyrinthMap.end);

    priorQ.push(start);
    visited.insert(start);
    labyrinthMap.predecessorMap[start] = start;

    if (labyrinthMap.start == labyrinthMap.end) {
        if (endingVisualBool)
            createFinalOutput(labyrinthMap);
        return true;
    }

    while (!priorQ.empty()) {
        CCoordHeuristic currCoord = priorQ.top();
        priorQ.pop();

        if (agentMove(priorQ, visited, currCoord, labyrinthMap, stepVisualBool,endingVisualBool,speedVisualisation)) {
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

            bool result = runAstar(labyrinthMap, false,false,0);
            if (!result) {
                std::cerr << "A* failed on file: " << filePath << std::endl;
                assert(result);
            }

            std::cout << "A* Passed: " << filePath << std::endl;
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
    runAstar(labyrinthMap, steppingVisualisation, finalPathVisualisation,speedVisualisation);

    return 0;
}
