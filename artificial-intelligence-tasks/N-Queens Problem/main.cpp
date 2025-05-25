#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <thread>

int speed = 2000;
int variant = 1;
int stepVisualisation = 1;

const std::string RED = "\033[41m";
const std::string RESET = "\033[0m";
const std::string GREEN = "\033[42m";


class CStatus {
public:
    CStatus(bool mSuccess, int mConflictCount) : m_success(mSuccess), m_conflictCount(mConflictCount) {}

    CStatus() {}

    bool m_success;
    int m_conflictCount;
};

class CQueen {
public:
    int m_queenRow;
    int m_queenCol;

    CQueen(int row, int col) : m_queenRow(row), m_queenCol(col) {}

    bool attacks(const CQueen &other) const {
        // Same row
        if (m_queenRow == other.m_queenRow) return true;

        // Same column
        if (m_queenCol == other.m_queenCol) return true;

        // Same diagonal
        if (std::abs(m_queenRow - other.m_queenRow) == std::abs(m_queenCol - other.m_queenCol))
            return true;

        return false;
    }
};

class CPlayingBoard {
private:
    int m_boardSize;
    std::vector<CQueen> m_queens;
    std::mt19937 rng;

public:
    CPlayingBoard(int size) : m_boardSize(size), rng(std::random_device{}()) {
        for (int col = 0; col < m_boardSize; col++) {
            int randomRow = rand() % m_boardSize;
            m_queens.emplace_back(randomRow, col);
        }

    }

    int countConflicts() {
        int conflicts = 0;

        for (size_t i = 0; i < m_queens.size(); i++) {
            for (size_t j = i + 1; j < m_queens.size(); j++) {
                if (m_queens[i].attacks(m_queens[j])) {
                    conflicts++;
                }
            }
        }

        return conflicts;
    }

    // first variant - queen can move unlimited amount of tiles in column
    std::vector<std::pair<int, int>> getNeighboursFirstVariant() {
        std::vector<std::pair<int, int>> neighbors;

        for (int queenIdx = 0; queenIdx < m_boardSize; queenIdx++) {
            int currentRow = m_queens[queenIdx].m_queenRow;

            for (int newRow = 0; newRow < m_boardSize; newRow++) {
                if (newRow != currentRow) {
                    neighbors.push_back({queenIdx, newRow});
                }
            }
        }

        std::shuffle(neighbors.begin(), neighbors.end(), rng);

        return neighbors;
    }

    // second variant - queen can only move one tile
    std::vector<std::pair<int, int>> getNeighboursSecondVariant() {
        std::vector<std::pair<int, int>> neighbors;

        for (int queenIdx = 0; queenIdx < m_boardSize; queenIdx++) {
            int currentRow = m_queens[queenIdx].m_queenRow;

            if (currentRow - 1 >= 0) {
                neighbors.push_back({queenIdx, currentRow - 1});
            }
            if (currentRow + 1 < m_boardSize) {
                neighbors.push_back({queenIdx, currentRow + 1});
            }
        }

        std::shuffle(neighbors.begin(), neighbors.end(), rng);

        return neighbors;
    }

    void makeMove(int queenIdx, int newRow) {
        m_queens[queenIdx].m_queenRow = newRow;
    }

    CStatus hillClimbSolve(int maxIterations = 1000) {
        int currentConflicts = countConflicts();
        int iterations = 0;
        CStatus retObj;

        if (stepVisualisation == 1) {
            printBoard(currentConflicts, -1, false, false);
            std::cout << "_______________________________________________________________________________" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(speed));
        }


        while (currentConflicts > 0 && iterations < maxIterations) {
            bool improved = false;

            std::vector<std::pair<int, int>> neighbors;

            if (variant == 1) neighbors = getNeighboursFirstVariant();
            if (variant == 2) neighbors = getNeighboursSecondVariant();

            for (const auto &[queenIdx, newRow]: neighbors) {
                int oldRow = m_queens[queenIdx].m_queenRow;
                makeMove(queenIdx, newRow);



                int newConflicts = countConflicts();


                if (stepVisualisation == 1) {
                    printBoard(newConflicts, queenIdx, false, false);

                    std::cout << "_______________________________________________________________________________"
                              << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(speed));
                }

                if (newConflicts < currentConflicts) {
                    currentConflicts = newConflicts;
                    improved = true;
                    break;
                } else {
                    makeMove(queenIdx, oldRow);
                    if (stepVisualisation == 1) {
                        printBoard(currentConflicts, -1, false, false);
                        std::cout << "Solution didnt improve, going back..." << std::endl;
                        std::cout << "_______________________________________________________________________________"
                                  << std::endl;

                        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
                    }
                }
            }
            // RESTART
            if (!improved) {
                for (int i = 0; i < m_boardSize; i++) {
                    makeMove(i, rand() % m_boardSize);
                }
                currentConflicts = countConflicts();
                if (stepVisualisation == 1) {
                    std::cout << " " << std::endl;
                    std::cout << "DIDNT IMPROVE, PERFORMING A RESTART" << std::endl;
                    std::cout << " " << std::endl;

                    printBoard(currentConflicts, -1, false, false);
                    std::cout << "_______________________________________________________________________________"
                              << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(speed));


                }

            }

            iterations++;
        }

        retObj.m_conflictCount = currentConflicts;

        if (currentConflicts == 0) {
            retObj.m_success = true;
        } else {
            retObj.m_success = false;
        }

        return retObj;
    }

    void printBoard(int currentConflicts, int queenIdx, bool endFlag, bool zeroConflictFlag) {
        std::cout << "     ";
        for (int col = 0; col < m_boardSize; col++) {
            std::cout << col%10 << "   ";
        }
        std::cout << std::endl;

        // Print top horizontal line
        std::cout << "   ";
        for (int col = 0; col < m_boardSize; col++) {
            std::cout << "|---";
        }
        std::cout << "|" << std::endl;

        // Create a 2D representation of the board
        std::vector<std::vector<bool>> board(m_boardSize, std::vector<bool>(m_boardSize, false));

        // Mark queen positions
        for (const auto &queen: m_queens) {
            board[queen.m_queenRow][queen.m_queenCol] = true;
        }

        // Print the board
        for (int row = 0; row < m_boardSize; row++) {
            // Print row index
            std::cout << row%10 << "  |";

            for (int col = 0; col < m_boardSize; col++) {
                if (board[row][col]) {
                    if (endFlag) {
                        if (zeroConflictFlag) {
                            std::cout << GREEN << " ♛ " << RESET << "|";
                        } else {
                            std::cout << RED << " ♛ " << RESET << "|";
                        }
                    } else {
                        if (col == queenIdx) {
                            std::cout << GREEN << " ♛ " << RESET << "|";
                        } else {
                            std::cout << RED << " ♛ " << RESET << "|";

                        }

                    }
                } else {
                    std::cout << "   |"; // Empty square
                }
            }

            std::cout << std::endl;

            // Print horizontal line after each row
            std::cout << "   |";
            for (int col = 0; col < m_boardSize; col++) {
                std::cout << "---|";
            }
            std::cout << std::endl;
        }
        std::cout << "Conflict count : " << currentConflicts << std::endl;
    }

};

int main(int argc, char *argv[]) {
    srand(time(0));

    // Process command line arguments for speed
    if (argc > 1) {
        speed = atoi(argv[1]);
    }

    int n;
    std::cout << "Enter the width/height of the playing board ( and queen amount ) : ";
    std::cin >> n;

    // Get variant type
    std::cout << "Select queen movement variant:" << std::endl;
    std::cout << "  1 - Queens can move any number of tiles within their column" << std::endl;
    std::cout << "  2 - Queens can move only one tile at a time" << std::endl;
    std::cout << "Enter variant (1 or 2): ";
    std::cin >> variant;

    // Validate input
    if (variant != 1 && variant != 2) {
        std::cout << "Invalid variant. Using default (1)." << std::endl;
        variant = 1;
    }

    // Get step visualization preference
    std::cout << "Do you want to see step-by-step visualization?" << std::endl;
    std::cout << "  1 - Yes, show each step" << std::endl;
    std::cout << "  2 - No, show only final result" << std::endl;
    std::cout << "Enter choice (1 or 2): ";
    std::cin >> stepVisualisation;

    // Validate input
    if (stepVisualisation != 1 && stepVisualisation != 2) {
        std::cout << "Invalid variant. Using default (1)." << std::endl;
        variant = 1;
    }


    CPlayingBoard playingBoard(n);

    std::cout << "Solving with hill climbing..." << std::endl;
    CStatus retObj = playingBoard.hillClimbSolve(10000);

    if (retObj.m_success) {
        playingBoard.printBoard(retObj.m_conflictCount, -1, true, true);
        std::cout << GREEN << "Solution found!"  << RESET << std::endl;
    } else {
        playingBoard.printBoard(retObj.m_conflictCount, -1, true, false);
        std::cout << RED << "No solution found. Try running again or increasing maxIterations." << RESET << std::endl;
    }

    return 0;
}