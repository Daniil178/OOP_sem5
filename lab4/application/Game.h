#ifndef GAME_H
#define GAME_H

#include "Level.h"
#include "RPG_Object.h"

namespace RPG {

/**
 * @class Game - manager of game
 */
class Game {
public:
    /**
     * @brief constructor of Game
     * @param number_of_level (int) - number of level
     * @param level0 (Level&) - start level
     */
    Game(int number_of_level, const Level& level0); //initialisation of Game
//    int turn_operatives(); // return flag after change
//    int turn_enemies(); // return flag after change


protected:
    /**
     * @brief (int) - number of level
     */
    int number_of_level;
    /**
     * (Level) - start level
     */
    Level level;
};

} // RPG

#endif //GAME_H
