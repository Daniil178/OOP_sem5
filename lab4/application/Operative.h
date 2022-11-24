#ifndef OPERATIVE_H
#define OPERATIVE_H

#include "Rational.h"
#include "Forager.h"
#include "Medicine_Kit.h"

namespace RPG {

class Operative : public Rational, public Forager {
public:
    Operative(std::pair<uint, uint> position, Weapon &basic_weapon, std::string &name); // initialisation some params
    int choice_weapon(Weapon new_weapon); // take item from inventory
    int health(Medicine_Kit use_kit);
    int reload();
    virtual int attack(Direction direct) override;

protected:
    int time_to_reload;
};

} // RPG

#endif //OPERATIVE_H
