#ifndef GAME_H
#define GAME_H

#include "Level.h"

namespace RPG {

class Game {
public:
    Game(int number_of_level, Level map_); //initialisation of Game
    void start(); // setup all parameters
    void finish(); // end game
    void turn(); // do one turn with 2 teams
    void shot(Unit *, Direction);

protected:
    int number_of_level;
    Level map_;
    int finish_flag; // 0 - don`t finish, 1 - win, 2 - lose
};

} // RPG

#endif //GAME_H
