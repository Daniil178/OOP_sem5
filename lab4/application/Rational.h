#ifndef RATIONAL_H
#define RATIONAL_H

#include "Wild.h"

namespace RPG {

class Rational : public Wild {
public:
    explicit Rational(std::string name, coordinate pos); // initialisation something
    /**/Weapon* get_current_weapon();
    /**/int take_item(Item* item, Map& map_); // take item from Floor
    /**/int put_item(Item* item, Map& map_); // put item on Floor
    /// @brief method attack: loss time and check accuracy
    /// \return int - result of attack: \n
    /// 0 - all of good \n
    /// 1 - you are missing
    /// -1 - you don't have weapon
    int attack() override;

protected:
    Weapon* current_weapon{};// = new Weapon();
};

} // RPG

#endif //RATIONAL_H
