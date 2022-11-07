#ifndef LEVEL_H
#define LEVEL_H

#include <map>
#include "Cell.h"
#include "Operative.h"

class Level {
public:
    Level(std::pair<uint, uint>, int size); // initialisation all params connected with level
    std::pair<uint, uint> get_size(); // get size of map
    int change_size(std::pair<uint, uint> new_size); // change size and rebuild level
protected:
    std::map<uint, uint> size;
    std::map<std::pair<uint, uint>, Cell> map_; // dict with all Cells != Floor
    std::vector<Operative> operatives;
    std::vector<Unit> enemies;
};

#endif //LEVEL_H
