#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Level.h"
#include "../graphics/TileOnMap.h"
#include <cstring>
#include <thread>
#include <chrono>

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

    int turn_enemies(sf::RenderWindow& window, sf::Texture& texture, sf::Text& text); // return flag after change

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

    void wildTurn(Wild* currWild, sf::RenderWindow& window, sf::Texture& texture, sf::Text& text);

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
