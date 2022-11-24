#ifndef LEVEL_H
#define LEVEL_H

#include "Cell.h"
#include "Operative.h"

namespace RPG {

class Level {
public:
    Level(std::pair<uint, uint>, int size);

    explicit Level(const std::vector<Unit*> enemies);

    // initialisation all params connected with level
    std::pair<uint, uint> get_size(); // get size of map
    int change_size(std::pair<uint, uint> new_size); // change size and rebuild level
protected:
    std::unordered_map<uint, uint> size;
    std::unordered_map<std::pair<uint, uint>, Cell> map_; // dict with all Cells != Floor
    std::vector<Operative> operatives;
    std::vector<Unit*> enemies;
};

} // RPG
#endif //LEVEL_H
