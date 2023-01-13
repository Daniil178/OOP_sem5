#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Level.h"
#include <cstring>

//static const std::string root_path = "/mnt/c/Users/danii";
static const std::string root_path = "/home/usik-dan";
//static const std::string level_path = "/ClionProjects/OOP_sem5/lab4/src/maps/TestMap.txt";
static const std::string level_path = "src/maps/map.txt";
//static const std::string tileset_path = "/ClionProjects/OOP_sem5/lab4/src/textures/tileset.png";
static const std::string tileset_path = "src/textures/tileset.png";
//static const std::string font_path = "/ClionProjects/OOP_sem5/lab4/src/textures/solo5.ttf";
static const std::string font_path = "src/textures/solo5.ttf";
static const std::string window_title = "Operation";
static const uint32_t font_size = 9;
static const float scale = 4.f;
static const sf::Vector2i tile_size(16, 16);

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
    Game(int number_of_level, Level* level0); //initialisation of Game

    /**
     * @brief turn of operatives - reactions of clicks
     * @param choice what player is click
     * @param window sf::window, in which player can click second choice (in shoot case)
     * @param diff what operative has turn
     * @return flag after change (if we want to finish turn)
     */
    int turn_operatives(sf::Keyboard::Key choice, sf::RenderWindow& window, int* diff);

    int turn_enemies(); // return flag after change

    /**
     * @brief free pointer of level
     */
    ~Game();

protected:
    /**
     * @brief (int) - number of level
     */
    int number_of_level;
    /**
     * (Level) - start level
     */
    Level* level;

    /**
     * @brief calculate path to point with algorithm lee
     * @param path vector, which will have resulting directions
     * @param from point from we start
     * @param to point where we go
     * @return true or false - Is exist the path?
     */
    bool pathToPoint(std::vector<Direction>& path, coordinate from, coordinate to);

    /**
     * @brief check situation: can unit see to point
     * @param unitCoorFrom coordinate from unit see
     * @param CoorTo coordinate where unit try see
     * @return can unit see to point
     */
    bool isSeeUnit(coordinate unitCoorFrom, coordinate CoorTo);

    void wildTurn(Wild* currWild);

};

static sf::Keyboard::Key get_input(sf::RenderWindow& window) {
    sf::Event event{};
    do {
        window.pollEvent(event);
        if (event.type == sf::Event::Closed) {
            return sf::Keyboard::Tilde;
        }
        if (event.type == sf::Event::KeyPressed) {
            return event.key.code;
        }
    }while (true);
}

} // RPG

#endif //GAME_H
