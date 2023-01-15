#include <iostream>
#include "graphics/TileOnMap.h"

using namespace sf;
using namespace std;


int main()
{
    sf::Keyboard::Key choice;
    int res_turn_oper;

    sf::Texture texture;
    texture.loadFromFile(RPG::tileset_path);
    sf::Text text;
    sf::Font font;
    font.loadFromFile(RPG::font_path);
    text.setFont(font);
    text.setCharacterSize(RPG::font_size);

    if (RPG::Game::startMenu(texture, text) != 1) return 0;

    auto* level = new RPG::Level();
    level->start(RPG::level_path);
    RPG::Game game = RPG::Game(1, level);

    sf::RenderWindow window(sf::VideoMode(level->get_size().second * RPG::tile_size.y * RPG::scale
                                          , level->get_size().first * RPG::tile_size.x * RPG::scale)
                            , RPG::window_title);
    int diff = 0, resInventory;

    do {
        try {
            //sf::RenderWindow window(sf::VideoMode(level.get_size().second * tile_size.y * scale, level.get_size().first * tile_size.x * scale), window_title);
            while (window.isOpen()) {
                while(res_turn_oper != -100 && window.isOpen()) {
                    RPG::draw(window, texture, text, *level, diff);
                    choice = RPG::get_input(window);
                    //~ - exit to main menu
                    if (choice == sf::Keyboard::Tilde or choice == sf::Keyboard::Escape) {
                        window.close();
                        break;
                    }
                    // Game - turn
                    res_turn_oper = game.turn_operatives(choice, window, &diff);
                    if (res_turn_oper == 77) {
                        resInventory = 0;
                        while (resInventory == 0) {
                            resInventory = game.inventoryActions(level->operatives[diff], texture, text);
                        }
                    }
                }
                if (choice == sf::Keyboard::Tilde or choice == sf::Keyboard::Escape) break;
                game.turn_enemies(window, texture, text);
                if (res_turn_oper == -100) {
                    diff = 0;
                    for (auto& curr_oper: level->operatives) {
                        curr_oper->update_time();
                    }
                    res_turn_oper = 0;
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
    } while (!level->check_flag() && choice != sf::Keyboard::Tilde && choice != sf::Keyboard::Escape);
    if (level->check_flag() > 0) {
        if (level->check_flag() == 1) {
            RPG::TileOnMap::drawMessage(texture, RPG::tile_size, "you win", text);
            // std::cout << "You are win!" << std::endl;
        }
        else if (level->check_flag() == 2) {
            RPG::TileOnMap::drawMessage(texture, RPG::tile_size, "you lose", text);
            // std::cout << "You are lose!" << std::endl;
        }
    }
    return 0;
}