#include "Rational.h"

namespace RPG {

Rational::Rational(std::string name, coordinate pos):
                                                    Unit(std::move(name), RATIONAL, pos),
                                                    Wild(std::move(name), pos)
                                                    {
    damage = 0;
    range = 0;
                                                    }

int Rational::attack() {
    if (current_weapon == nullptr) {
        return -1; // haven't weapon
    }
    if (current_weapon->shot() < 0) {
        return -2; // hasn't ammo's
    }

    params.current_time -= 1;
    if (GetRandomNumber(0, 100) > accuracy) {
        return 1; // missing
    }
    return 0;
}

int Rational::take_item(Item* item, Map& map_) {

    if (item->get_type() != WEAPON) {
        return -2; // bad type
    }
    if (!map_[position].take_item(item)) {
        return -1; // bad take
    }
    current_weapon = dynamic_cast<Weapon*>(item);
    return 0;
}

int Rational::put_item(Item* item, Map &map_) {
    if (map_[position].put_item(item)) {
        return -1; // bad put ?wtf?
    }
    current_weapon = nullptr;
    return 0;
}

Weapon* Rational::get_current_weapon() {
    return current_weapon;
}

} // RPG