#ifndef RPG_OBJECT_H
#define RPG_OBJECT_H

#include "help_func.h"

namespace RPG {

enum Direction {
    Left = 0,
    Down,
    Up,
    Right
};

enum TYPE_OBJECT {
    ITEM = 0,
    UNIT
};

class RPG_Object {
public:
    virtual int get_damage(int) = 0;
    static std::unordered_map<Direction, coordinate> DIR_POS;
};

} // RPG

#endif //RPG_OBJECT_H
