#ifndef RATIONAL_H
#define RATIONAL_H

#include "Wild.h"

class Rational: public Wild {
public:
    Rational(std::string name); // initialisation something
    WEAPON_TYPE get_current_weapon();
    int take_item(Item item); // take item from Floor
    int put_item(Item item); // put item on Floor
    virtual int attack(Direction direct) override;
protected:
    WEAPON_TYPE current_weapon;
};

#endif //RATIONAL_H
