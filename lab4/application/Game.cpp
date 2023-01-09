#include "Game.h"
#include <utility>

namespace RPG {

Game::Game(int num_of_levels, Level* level0):
                                            number_of_level(num_of_levels),
                                            level(level0)
                                            {}

static std::unordered_map<char, RPG::Direction> char_direction = {
        {sf::Keyboard::W, RPG::Up},
        {sf::Keyboard::S, RPG::Down},
        {sf::Keyboard::A, RPG::Left},
        {sf::Keyboard::D, RPG::Right}
};

int Game::turn_operatives(sf::Keyboard::Key choice, sf::RenderWindow& window, int* diff) {
    int res_turn = 0;
    auto curr_oper = level->operatives.begin() + *diff;
    std::cout << choice << std::endl;
    // e - end turn
    if (choice == sf::Keyboard::E) {
        return -100;
    }
    // r - reload weapon
    else if (choice == sf::Keyboard::R) {
        res_turn = (*curr_oper)->reload();
    }
    // f - choice direction and shoot
    else if (choice == sf::Keyboard::F) {
        sf::Keyboard::Key direction = get_input(window);
        if (direction == sf::Keyboard::W or direction == sf::Keyboard::S or direction == sf::Keyboard::A or direction == sf::Keyboard::D) {
            res_turn = level->shoot(*curr_oper, char_direction.at(direction));
        }
    }
    // g - take item
    else if (choice == sf::Keyboard::G) {
        res_turn = (*curr_oper)->take_item_to_inventory(level->map_);
    }
    // i - inventory mode
    else if (choice == sf::Keyboard::I) {
        //...
    }
    else if (sf::Keyboard::Num1 <= choice and choice <= sf::Keyboard::Num9) {
        int oper_num = choice - sf::Keyboard::Num1;
        if (oper_num >= 0 and oper_num < level->operatives.size()) {
            *diff = oper_num;
            //curr_oper = level.operatives.begin() + oper_num;
        }
        else {
            res_turn = -1;
        }
    }
    else {
        if (choice == sf::Keyboard::W or choice == sf::Keyboard::S or choice == sf::Keyboard::A or choice == sf::Keyboard::D) {
            res_turn = level->step_by_unit(*curr_oper, char_direction[choice]);
        }
    }
    return res_turn;
}

Game::~Game() {
    delete level;
}

} // RPG