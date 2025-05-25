#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <dirent.h>
#include <algorithm>

class Tile {
public:
    int x;
    int y;
    int value;
};

class Grid {
public:
    std::vector<std::vector<Tile>> m_sudokuGrid; // 2d array representing grid

    bool solve() {
        int row, col;

        if (!findEmptyCell(row, col)) {
            return true;
        }

        for (int num = 1; num <= 9; num++) {
            if (isSafe(row, col, num)) {
                m_sudokuGrid[row][col].value = num;

                if (solve()) {
                    return true;
                }

                m_sudokuGrid[row][col].value = 0;
            }
        }

        return false;
    }

    bool findEmptyCell(int &row, int &col) {
        int minPossibilities = 10;
        bool foundEmpty = false;

        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if (m_sudokuGrid[r][c].value == 0) {
                    foundEmpty = true;

                    int count = 0;
                    for (int num = 1; num <= 9; num++) {
                        if (isSafe(r, c, num)) {
                            count++;
                        }
                    }

                    if (count < minPossibilities) {
                        minPossibilities = count;
                        row = r;
                        col = c;

                        if (count == 1) {
                            return true;
                        }
                    }
                }
            }
        }

        return foundEmpty;
    }

    bool isSafe(int row, int col, int num) {
        for (int x = 0; x < 9; x++) {
            if (m_sudokuGrid[row][x].value == num) {
                return false;
            }
        }

        for (int y = 0; y < 9; y++) {
            if (m_sudokuGrid[y][col].value == num) {
                return false;
            }
        }

        int boxStartRow = row - row % 3;
        int boxStartCol = col - col % 3;

        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (m_sudokuGrid[y + boxStartRow][x + boxStartCol].value == num) {
                    return false;
                }
            }
        }

        return true;
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