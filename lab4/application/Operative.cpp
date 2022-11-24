#include "Operative.h"

Operative::Operative(std::pair<uint, uint> position, Weapon &basic_weapon,
                     std::string &name) : Unit(name, OPERATIVE, position), Forager(name), Rational(name) {
    current_weapon = basic_weapon;
}

