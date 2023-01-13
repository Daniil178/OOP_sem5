#include <iostream>
#include "graphics/TileOnMap.h"

using namespace sf;
using namespace std;

void draw(sf::RenderWindow& window, sf::Texture& texture, sf::Text& text, RPG::Level& level) {
    TileOnMap tileMap(texture, text, tile_size, scale);
    tileMap.load(level);
    window.clear(sf::Color::Black);
    tileMap.drawCells(window);
    tileMap.drawUnits(window);
    tileMap.drawTexts(window);
    window.display();
}


int main()
{
    sf::Keyboard::Key choice;
    int res_turn_oper;
    auto* level = new RPG::Level();
    level->start(level_path);
    RPG::Game game = RPG::Game(1, level);

    sf::RenderWindow window(sf::VideoMode(level->get_size().second * tile_size.y * scale
                                          , level->get_size().first * tile_size.x * scale)
                            , window_title);
    sf::Texture texture;
    texture.loadFromFile(tileset_path);
    sf::Text text;
    sf::Font font;
    font.loadFromFile(font_path);
    text.setFont(font);
    text.setCharacterSize(font_size);

    int diff = 0;

    do {
        try {
            //sf::RenderWindow window(sf::VideoMode(level.get_size().second * tile_size.y * scale, level.get_size().first * tile_size.x * scale), window_title);
            while (window.isOpen()) {
                draw(window, texture, text, *level);
                choice = RPG::get_input(window);
                //~ - exit to main menu
                if (choice == sf::Keyboard::Tilde) {
                    window.close();
                    break;
                }
                // Game - turn
                res_turn_oper = game.turn_operatives(choice, window, &diff);
                game.turn_enemies();
                if (res_turn_oper == -100) {
                    for (auto& curr_oper: level->operatives) {
                        curr_oper->update_time();
                    }
                }
                if (level->check_flag()) {
                    window.close();
                    break;
                }
            }
        } catch (exception& error) {
            std::cout << "\n\t\tUnexpected error... " << error.what() << std::endl;
            window.close();
            continue;
        }
    } while (!level->check_flag() && choice != sf::Keyboard::Tilde);
    if (level->check_flag() > 0) {
        if (level->check_flag() == 1) std::cout << "You are win!" << std::endl;
        else if (level->check_flag() == 2) std::cout << "You are lose!" << std::endl;
    }
    return 0;
}