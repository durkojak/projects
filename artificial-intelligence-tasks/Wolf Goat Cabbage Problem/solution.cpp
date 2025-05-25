#include <set>
#include <queue>
#include <iostream>
enum class FarmerLocation {
    startingLand,
    finishLand,
    boat
};
// class representing start and end point
class CLand {
public:
    // Default Constructor
    CLand() = default;

    // Copy Constructor
    CLand(const CLand &other) : entitiesOnLand(other.entitiesOnLand) {}

    // Destructor
    ~CLand() = default;

    // Copy Assignment Operator
    CLand &operator=(const CLand &other) {
        if (this != &other) { /
            entitiesOnLand = other.entitiesOnLand;
        }
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const CLand &land) {
        os << "{";
        bool first = true;
        for (auto &entity: land.entitiesOnLand) {
            if (entity.empty()) continue;
            if (!first) os << ", "; // Add a comma between elements
            os << entity;
            first = false;
        }
        os << "}";
        return os;
    }

    bool operator==(const CLand &rhs) const {
        return entitiesOnLand == rhs.entitiesOnLand;
    }

    bool operator!=(const CLand &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const CLand &rhs) const {
        return entitiesOnLand < rhs.entitiesOnLand;
    }

    bool operator>(const CLand &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const CLand &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const CLand &rhs) const {
        return !(*this < rhs);
    }

    // false means no danger, true means danger
    bool checkDanger() const {
        if (!entitiesOnLand.contains("Farmer")) {
            if (entitiesOnLand.contains("Wolf") && entitiesOnLand.contains("Goat")) {
                return true;
            } else if (entitiesOnLand.contains("Goat") && entitiesOnLand.contains("Cabbage")) {
                return true;
            }
        }
        return false;
    }


    std::set<std::string> entitiesOnLand;
};

class CBoat {
public:
    // Default Constructor
    CBoat() {

    }

    friend std::ostream &operator<<(std::ostream &os, const CBoat &boat) {
        if (boat.isFarmerOnBoat && !boat.farmersPassenger.empty()) {
            os << "{Farmer, " << boat.farmersPassenger << "}";
        } else if (boat.isFarmerOnBoat && boat.farmersPassenger.empty()) {
            os << "{Farmer}";
        } else {
            os << "{}";
        }
        return os;
    }

    bool operator<(const CBoat &rhs) const {
        if (isFarmerOnBoat < rhs.isFarmerOnBoat)
            return true;
        if (rhs.isFarmerOnBoat < isFarmerOnBoat)
            return false;
        return farmersPassenger < rhs.farmersPassenger;
    }

    bool operator>(const CBoat &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const CBoat &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const CBoat &rhs) const {
        return !(*this < rhs);
    }


    bool operator==(const CBoat &rhs) const {
        return isFarmerOnBoat == rhs.isFarmerOnBoat &&
               farmersPassenger == rhs.farmersPassenger;
    }

    bool operator!=(const CBoat &rhs) const {
        return !(rhs == *this);
    }

    void enterBoat(const std::string &farmer, const std::string other, CLand &landLeaving) {
        isFarmerOnBoat = true;
        farmersPassenger = other;
        landLeaving.entitiesOnLand.erase(farmer);
        if (other != "") {
            landLeaving.entitiesOnLand.erase(other);
        }
    }

    void leaveBoat(const std::string &farmer, const std::string other, CLand &landEntering) {
        isFarmerOnBoat = false;
        farmersPassenger = "";
        landEntering.entitiesOnLand.insert(farmer);
        if (other != "") {
            landEntering.entitiesOnLand.insert(other);
        }
    }


    bool isFarmerOnBoat = false;
    std::string farmersPassenger = "";
};

class CMapState {
public:

    CMapState(const std::set<std::string> &startEntities, const std::set<std::string> &endEntities, CBoat &otherBoat) {
        for (auto &entity: startEntities) {
            startLand.entitiesOnLand.insert(entity);
        }

        for (auto &entity: endEntities) {
            endLand.entitiesOnLand.insert(entity);
        }

        if (startEntities.contains("Farmer")) {
            farmerLocation = FarmerLocation::startingLand;
        } else if (endEntities.contains("Farmer")) {
            farmerLocation = FarmerLocation::finishLand;
        } else {
            farmerLocation = FarmerLocation::boat;
        }

        this->boat = otherBoat;
    }

    // Copy Constructor
    CMapState(const CMapState &other)
            : startLand(other.startLand),
              endLand(other.endLand),
              boat(other.boat),
              farmerLocation(other.farmerLocation),
              pathToThisState(other.pathToThisState) {}


    // Destructor
    ~CMapState() = default;

    // Copy Assignment Operator
    CMapState &operator=(const CMapState &other) {
        if (this != &other) {
            startLand = other.startLand;
            endLand = other.endLand;
            boat = other.boat;
            farmerLocation = other.farmerLocation;
            pathToThisState = other.pathToThisState;
        }
        return *this;
    }


    // Overloading the << operator for CMapState
    friend std::ostream &operator<<(std::ostream &os, const CMapState &state) {
        os << "startLand: " << state.startLand << "\n"
           << "boat: " << state.boat << "\n"
           << "endLand: " << state.endLand << "\n";


        return os;
    }

    bool operator<(const CMapState &rhs) const {
        if (startLand < rhs.startLand)
            return true;
        if (rhs.startLand < startLand)
            return false;
        if (endLand < rhs.endLand)
            return true;
        if (rhs.endLand < endLand)
            return false;
        return boat < rhs.boat;
    }

    bool operator>(const CMapState &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const CMapState &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const CMapState &rhs) const {
        return !(*this < rhs);
    }

    bool operator==(const CMapState &rhs) const {
        return startLand == rhs.startLand &&
               endLand == rhs.endLand &&
               boat == rhs.boat;
    }

    bool operator!=(const CMapState &rhs) const {
        return !(rhs == *this);
    }

    bool checkDangerOnMap() const {
        return startLand.checkDanger() || endLand.checkDanger();
    }

    CLand startLand;
    CLand endLand;
    CBoat boat;
    FarmerLocation farmerLocation;
    std::vector<CMapState> pathToThisState;
};

bool checkSolution(CMapState &mapState) {
    if (mapState.farmerLocation == FarmerLocation::finishLand &&
        mapState.endLand.entitiesOnLand.size() == 5) {
        int i = 1;
        for (CMapState &state: mapState.pathToThisState) {
            std::cout << "STEP " << i << " :\n" << state << "\n";
            i++;
        }
        std::cout << "STEP " << i << " :\n" << mapState << "\n";
        return true;
    }
    return false;
}


int main() {
    CBoat boat{};
    CMapState startingState({"Farmer", "Goat", "Cabbage", "Wolf", ""}, {""}, boat);

    // BFS
    std::queue<CMapState> q;
    std::set<CMapState> visited;

    q.push(startingState);
    visited.insert(startingState);


    while (!q.empty()) {
        CMapState currState = q.front();
        q.pop();

        if (currState.farmerLocation == FarmerLocation::startingLand && !currState.startLand.entitiesOnLand.empty()) {

            for (const auto &entity: currState.startLand.entitiesOnLand) {
                if (entity != "Farmer") {
                    CMapState toBoatState = currState;
                    toBoatState.boat.enterBoat("Farmer", entity, toBoatState.startLand);
                    toBoatState.farmerLocation = FarmerLocation::boat;
                    toBoatState.pathToThisState.push_back(currState);
                    if (visited.count(toBoatState) == 0 && !toBoatState.checkDangerOnMap()) {
                        q.push(toBoatState);
                        visited.insert(toBoatState);
                    }
                }
            }


        } else if (currState.farmerLocation == FarmerLocation::boat) {
            CMapState moveToStartState = currState;
            moveToStartState.boat.leaveBoat("Farmer", moveToStartState.boat.farmersPassenger,
                                            moveToStartState.startLand);
            moveToStartState.farmerLocation = FarmerLocation::startingLand;
            moveToStartState.pathToThisState.push_back(currState);

            CMapState moveToEndState = currState;
            moveToEndState.boat.leaveBoat("Farmer", moveToEndState.boat.farmersPassenger, moveToEndState.endLand);
            moveToEndState.farmerLocation = FarmerLocation::finishLand;
            moveToEndState.pathToThisState.push_back(currState);

            if (visited.count(moveToStartState) == 0 && !moveToStartState.checkDangerOnMap()) {
                q.push(moveToStartState);
                visited.insert(moveToStartState);
            }
            if (visited.count(moveToEndState) == 0 && !moveToEndState.checkDangerOnMap()) {
                if (checkSolution(moveToEndState)) break;

                q.push(moveToEndState);
                visited.insert(moveToEndState);
            }
        } else if (currState.farmerLocation == FarmerLocation::finishLand) {

            for (const auto &entity: currState.endLand.entitiesOnLand) {
                if (entity != "Farmer") {
                    CMapState toBoatState = currState;
                    toBoatState.boat.enterBoat("Farmer", entity, toBoatState.endLand);
                    toBoatState.farmerLocation = FarmerLocation::boat;
                    toBoatState.pathToThisState.push_back(currState);
                    if (visited.count(toBoatState) == 0 && !toBoatState.checkDangerOnMap()) {
                        q.push(toBoatState);
                        visited.insert(toBoatState);
                    }
                }
            }


        }


    }

    
    return EXIT_SUCCESS;

}












