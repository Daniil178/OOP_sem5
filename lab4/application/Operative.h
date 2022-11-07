#ifndef OPERATIVE_H
#define OPERATIVE_H

#include "Rational.h"
#include "Forager.h"
#include "Medicine_Kit.h"

class Operative: public Rational, public Forager {
public:
    Operative(Weapon basic_weapon, std::string name); // initialisation some params
    int choice_weapon(Weapon new_weapon); // take item from inventory
    int health(MED_KIT_HEALTH use_kit);
    int reload();
    virtual int attack(Direction direct) override;
protected:
    int time_to_reload;
};

#endif //OPERATIVE_H
