#include "Level.h"

#include <utility>

namespace RPG {

Level::Level(): size(std::make_pair(0, 0)), finish_flag(0) {}

Level::Level(coordinate size0): size(std::move(size0)), finish_flag(0) {}

Level::Level(coordinate size0,
             std::vector<Operative*> operatives,
             std::vector<Unit*> enemies)
                                        :
                                        size(std::move(size0)),
                                        operatives(std::move(operatives)),
                                        enemies(std::move(enemies)),
                                        finish_flag(0)
                                        {}

coordinate Level::get_size() {
    return size;
}

int Level::change_size(coordinate new_size) {
    if (new_size.first < 0 && new_size.second < 0) {
        return -1;
    }
    size = new_size;
    return 0;
}

void Level::start() {
    finish_flag = 0;
}

int Level::check_flag() const noexcept{
    return finish_flag;
}

int Level::shot(Wild* who, Direction where) {
    int res_attack = who->attack();
    if (res_attack != 0) {
        return res_attack;
    }
    int range_ = who->get_range();
    std::vector<RPG_Object*> targets;
    //targets.reserve(range_);
    for (int i = 0; i < range_; ++i) {
        targets.push_back(nullptr);
    }
    auto curr_target = targets.begin();
    coordinate pos = who->get_position(), max_pos;
    max_pos.first = pos.first + RPG_Object::DIR_POS[where].first * (range_ + 1);
    max_pos.second = pos.second + RPG_Object::DIR_POS[where].second * (range_ + 1);
    if ((max_pos.first > size.first) or (max_pos.second > size.second)) {
        max_pos.first = (max_pos.first > size.first) ? size.first : max_pos.first;
        max_pos.second = (max_pos.second > size.second) ? size.second : max_pos.second;
    }
    else if ((max_pos.first <= 0) or (max_pos.second <= 0)) {
        max_pos.first = (max_pos.first < 0) ? -1 : max_pos.first;
        max_pos.second = (max_pos.second < 0) ? -1 : max_pos.second;
    }

    for (pos += RPG_Object::DIR_POS[where]; pos != max_pos; pos += RPG_Object::DIR_POS[where]) {
        for (auto curr_oper: operatives) {
            if (curr_oper->get_position() == pos) {
                *curr_target = dynamic_cast<RPG_Object*>(dynamic_cast<Unit*>(curr_oper));
            }
        }
        for (auto curr_enemy: enemies) {
            if (curr_enemy->get_position() == pos) {
                *curr_target = dynamic_cast<RPG_Object*>(dynamic_cast<Unit*>(curr_enemy));
            }
        }

        if (map_[pos]->can_go_through() == false) {
            *curr_target = dynamic_cast<RPG_Object*>(map_[pos]);
        }
        ++curr_target;
    }
    curr_target = targets.begin();
    res_attack = 1;
    while (res_attack == 1 && curr_target <= targets.end()) {
        if (*curr_target != nullptr) {
            res_attack = (*curr_target)->get_damage(who->get_num_damage());
        }
        else {
            ++curr_target;
        }
    }

    // delete died unit...
    if (res_attack == 100) {
        Unit *curr_unit = dynamic_cast<Unit*>(*curr_target);
        UNIT_TYPE type_curr_enemy = curr_unit->get_type();
        if (type_curr_enemy == WILD) {
            enemies.erase(std::find(enemies.begin(), enemies.end(), dynamic_cast<Unit*>(curr_unit)));
            delete dynamic_cast<Wild*>(curr_unit);
        }
        else if (type_curr_enemy == RATIONAL) {
            enemies.erase(std::find(enemies.begin(), enemies.end(), dynamic_cast<Unit*>(curr_unit)));
            delete dynamic_cast<Rational*>(curr_unit);
        }
        else if (type_curr_enemy == FORAGER) {
            enemies.erase(std::find(enemies.begin(), enemies.end(), dynamic_cast<Unit*>(curr_unit)));
            delete dynamic_cast<Forager*>(curr_unit);
        }
        else if (type_curr_enemy == OPERATIVE) {
            operatives.erase(std::find(operatives.begin(), operatives.end(), dynamic_cast<Operative*>(curr_unit)));
            delete dynamic_cast<Operative*>(curr_unit);
            if (operatives.empty()) {
                finish_flag = 2;
            }
        }
        if (enemies.empty()) {
            finish_flag = 1;
        }
    }

    return (res_attack < 0 ? 0: res_attack);
}

Level::~Level() {
    for (auto curr_cell: map_) {
        delete curr_cell.second;
    }
    for (auto curr_operative: operatives) {
        delete curr_operative;
    }
    for (auto curr_enemy: enemies) {
        UNIT_TYPE type_curr_enemy = curr_enemy->get_type();
        if (type_curr_enemy == WILD) {
            delete dynamic_cast<Wild*>(curr_enemy);
        }
        else if (type_curr_enemy == RATIONAL) {
            delete dynamic_cast<Rational*>(curr_enemy);
        }
        else if (type_curr_enemy == FORAGER) {
            delete dynamic_cast<Forager*>(curr_enemy);
        }
        else {
            delete curr_enemy;
        }
    }
}

}// RPG