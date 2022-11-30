#ifndef LEVEL_H
#define LEVEL_H

#include "Operative.h"

namespace RPG {

class Level {
public:
    Level(coordinate size);

    explicit Level(std::vector<Unit *> enemies);

    // initialisation all params connected with level
    coordinate get_size(); // get size of map
    int change_size(coordinate new_size); // change size and rebuild level
protected:
    coordinate size;
    Map map_; // dict with all Cells != Floor
    std::vector<Operative> operatives;
    std::vector<Unit *> enemies;
};

} // RPG
#endif //LEVEL_H
