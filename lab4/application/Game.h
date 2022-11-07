#ifndef GAME_H
#define GAME_H

#include "Level.h"

class Game {
public:
    Game(int number_of_level, Level map_); //initialisation of Game
    void start(); // setup all parameters
    void finish(); // end game
    void turn(); // do one turn with 2 teams
    void shot(Unit * who, Direction to);
protected:
    int number_of_level;
    Level map_;
    int finish_flag = 0; // 0 - don`t finish, 1 - win, 2 - lose
};

#endif //GAME_H
