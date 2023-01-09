#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Level.h"
#include <cstring>

static const std::string root_path = "/mnt/c/Users/danii";
static const std::string level_path = "/ClionProjects/OOP_sem5/lab4/src/maps/TestMap.txt";
static const std::string tileset_path = "/ClionProjects/OOP_sem5/lab4/src/textures/tileset.png";
static const std::string tileset_path1 = "/mnt/c/Users/danii/Downloads/scopus_1.png";
static const std::string font_path = "/ClionProjects/OOP_sem5/lab4/src/textures/solo5.ttf";
static const std::string window_title = "Operation";
static const uint font_size = 9;
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

    int turn_operatives(sf::Keyboard::Key choice, sf::RenderWindow& window, int* diff); // return flag after change
    int turn_enemies(); // return flag after change

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
