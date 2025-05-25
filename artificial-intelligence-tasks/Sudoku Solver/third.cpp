#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <dirent.h>
#include <algorithm>
#include <set>

class Tile {
public:
    int x;
    int y;
    int value;
    std::set<int> domain;

    Tile() : value(0) {
        for (int i = 1; i <= 9; i++) {
            domain.insert(i);
        }
    }
};

class Grid {
public:
    std::vector<std::vector<Tile>> m_sudokuGrid; // 2d array representing grid

    bool solve() {
        int row, col;

        if (!findEmptyCell(row, col)) {
            return true;
        }

        // current cell domain
        std::set<int> currentDomain = m_sudokuGrid[row][col].domain;

        // here i go only through valid domain unlike before
        for (int num : currentDomain) {

            std::vector<std::pair<int, int>> affected;
            std::vector<std::set<int>> oldDomains;

            m_sudokuGrid[row][col].value = num;

            if (updateDomains(row, col, num, affected, oldDomains)) {
                if (solve()) {
                    return true;
                }
            }


            for (size_t i = 0; i < affected.size(); i++) {
                int r = affected[i].first;
                int c = affected[i].second;
                m_sudokuGrid[r][c].domain = oldDomains[i];
            }
            m_sudokuGrid[row][col].value = 0;
        }

        return false;
    }


    bool updateDomains(int row, int col, int value, std::vector<std::pair<int, int>>& affected,
                       std::vector<std::set<int>>& oldDomains) {
        // domain remove in col
        for (int c = 0; c < 9; c++) {
            if (c != col && m_sudokuGrid[row][c].value == 0 &&
                m_sudokuGrid[row][c].domain.find(value) != m_sudokuGrid[row][c].domain.end()) {
                affected.push_back({row, c});
                oldDomains.push_back(m_sudokuGrid[row][c].domain);

                m_sudokuGrid[row][c].domain.erase(value);

                if (m_sudokuGrid[row][c].domain.empty()) {
                    return false;
                }
            }
        }

        // domain remove in column
        for (int r = 0; r < 9; r++) {
            if (r != row && m_sudokuGrid[r][col].value == 0 &&
                m_sudokuGrid[r][col].domain.find(value) != m_sudokuGrid[r][col].domain.end()) {
                // Save old domain
                affected.push_back({r, col});
                oldDomains.push_back(m_sudokuGrid[r][col].domain);

                // Remove value from domain
                m_sudokuGrid[r][col].domain.erase(value);

                if (m_sudokuGrid[r][col].domain.empty()) {
                    return false;
                }
            }
        }

        // domain removal in box
        int boxStartRow = row - row % 3;
        int boxStartCol = col - col % 3;

        for (int r = boxStartRow; r < boxStartRow + 3; r++) {
            for (int c = boxStartCol; c < boxStartCol + 3; c++) {
                if ((r != row || c != col) && m_sudokuGrid[r][c].value == 0 &&
                    m_sudokuGrid[r][c].domain.find(value) != m_sudokuGrid[r][c].domain.end()) {
                    affected.push_back({r, c});
                    oldDomains.push_back(m_sudokuGrid[r][c].domain);

                    m_sudokuGrid[r][c].domain.erase(value);

                    if (m_sudokuGrid[r][c].domain.empty()) {
                        return false;
                    }
                }
            }
        }

        return true;
    }


    bool findEmptyCell(int &row, int &col) {
        int minDomainSize = 10;
        bool foundEmpty = false;

        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if (m_sudokuGrid[r][c].value == 0) {
                    foundEmpty = true;

                    int domainSize = m_sudokuGrid[r][c].domain.size();

                    if (domainSize < minDomainSize) {
                        minDomainSize = domainSize;
                        row = r;
                        col = c;


                        if (domainSize == 1) {
                            return true;
                        }
                    }
                }
            }
        }

        return foundEmpty;
    }

    void initializeDomains() {
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if (m_sudokuGrid[r][c].value == 0) {
                    m_sudokuGrid[r][c].domain.clear();
                    for (int num = 1; num <= 9; num++) {
                        m_sudokuGrid[r][c].domain.insert(num);
                    }
                } else {
                    m_sudokuGrid[r][c].domain.clear();
                }
            }
        }

        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if (m_sudokuGrid[r][c].value != 0) {
                    int value = m_sudokuGrid[r][c].value;

                    for (int x = 0; x < 9; x++) {
                        if (x != c && m_sudokuGrid[r][x].value == 0) {
                            m_sudokuGrid[r][x].domain.erase(value);
                        }
                    }

                    for (int y = 0; y < 9; y++) {
                        if (y != r && m_sudokuGrid[y][c].value == 0) {
                            m_sudokuGrid[y][c].domain.erase(value);
                        }
                    }

                    int boxStartRow = r - r % 3;
                    int boxStartCol = c - c % 3;

                    for (int y = boxStartRow; y < boxStartRow + 3; y++) {
                        for (int x = boxStartCol; x < boxStartCol + 3; x++) {
                            if ((y != r || x != c) && m_sudokuGrid[y][x].value == 0) {
                                m_sudokuGrid[y][x].domain.erase(value);
                            }
                        }
                    }
                }
            }
        }
    }

    // build initial sudoku grid from file
    Grid(std::string filename) {
        std::string filepath = "sudoku_examples/" + filename;
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return;
        }

        std::string line;
        int y = 0;

        while (std::getline(file, line) && y < 9) {
            std::vector<Tile> row;
            std::istringstream iss(line);
            int value;
            int x = 0;

            while (iss >> value && x < 9) {
                Tile tile;
                tile.x = x;
                tile.y = y;
                tile.value = value;
                row.push_back(tile);
                x++;
            }

            if (x != 9) {
                std::cerr << "Error: Row " << y << " has incorrect number of values" << std::endl;
                return;
            }

            m_sudokuGrid.push_back(row);
            y++;
        }

        if (y != 9) {
            std::cerr << "Error: File has incorrect number of rows" << std::endl;
            return;
        }

        file.close();

        initializeDomains();
    }

    // visualisation of the grid
    void visualiseGrid() {
        std::cout << "┌───────┬───────┬───────┐" << std::endl;

        for (int y = 0; y < 9; y++) {
            std::cout << "│ ";

            for (int x = 0; x < 9; x++) {
                if (m_sudokuGrid[y][x].value == 0) {
                    std::cout << ". ";
                } else {
                    std::cout << m_sudokuGrid[y][x].value << " ";
                }

                if (x == 2 || x == 5) {
                    std::cout << "│ ";
                }
            }

            std::cout << "│" << std::endl;

            if (y == 2 || y == 5) {
                std::cout << "├───────┼───────┼───────┤" << std::endl;
            }
        }

        std::cout << "└───────┴───────┴───────┘" << std::endl;
    }

    void printDomains() {
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                std::cout << "Cell (" << r << "," << c << ") domain: ";
                if (m_sudokuGrid[r][c].value != 0) {
                    std::cout << "[value = " << m_sudokuGrid[r][c].value << "]";
                } else {
                    std::cout << "{";
                    for (int val : m_sudokuGrid[r][c].domain) {
                        std::cout << val << " ";
                    }
                    std::cout << "}";
                }
                std::cout << std::endl;
            }
        }
    }
};

int main() {
    // List Sudoku files
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ent;

    dir = opendir("sudoku_examples");

    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            std::string fileName = ent->d_name;
            // Only include txt files
            if (fileName.find(".txt") != std::string::npos) {
                files.push_back(fileName);
            }
        }
        closedir(dir);

        // Sort files alphabetically
        std::sort(files.begin(), files.end());

        // Show available files
        std::cout << "Available Sudoku puzzles:" << std::endl;
        for (size_t i = 0; i < files.size(); i++) {
            std::cout << i + 1 << ". " << files[i] << std::endl;
        }

        // Get user choice
        int choice;
        std::cout << "Enter number to select puzzle: ";
        std::cin >> choice;

        if (choice < 1 || choice > static_cast<int>(files.size())) {
            std::cout << "Invalid choice. Exiting." << std::endl;
            return 1;
        }

        std::string selectedFile = files[choice - 1];

        // Solve the selected puzzle
        Grid sudoku(selectedFile);
        std::cout << "Original Sudoku:" << std::endl;
        sudoku.visualiseGrid();

        // Solve the puzzle and measure time
        std::cout << "\nSolving...\n" << std::endl;

        // Get starting time
        auto start = std::chrono::high_resolution_clock::now();

        bool solved = sudoku.solve();

        // Get ending time
        auto end = std::chrono::high_resolution_clock::now();

        // Calculate duration
        std::chrono::duration<double, std::milli> duration = end - start;

        if (solved) {
            std::cout << "Solved in " << duration.count() << " milliseconds:" << std::endl;
            sudoku.visualiseGrid();
        } else {
            std::cout << "No solution exists for this puzzle" << std::endl;
        }

    } else {
        std::cerr << "Could not open directory 'sudoku_examples'" << std::endl;
        return 1;
    }

    return 0;
}