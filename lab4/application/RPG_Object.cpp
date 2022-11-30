#include "RPG_Object.h"

namespace RPG {
    std::unordered_map<Direction, coordinate> RPG_Object::DIR_POS = {{Left, std::make_pair(-1, 0)},
                                                                {Down, std::make_pair(0, 1)},
                                                                {Up, std::make_pair(0, -1)},
                                                                {Right, std::make_pair(1, 0)}};
} // RPG