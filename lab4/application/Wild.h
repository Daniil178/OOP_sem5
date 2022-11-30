#ifndef WILD_H
#define WILD_H

#include "Unit.h"

namespace RPG {

class Wild : virtual public Unit {
public:
    Wild(std::string name, coordinate start_pos); // initialisation damage and range of attack
    /**/[[nodiscard]] int get_num_damage() const noexcept; // get damage
    /**/[[nodiscard]] int get_range() const noexcept; // get range of attack
    /**/[[nodiscard]] int get_accuracy() const noexcept; // get accuracy of attack in %
    /*?*/virtual int attack(); // make damage to cell
protected:
    int damage = 25;
    int range;
    const int accuracy = 90; // in %
};

} // RPG

#endif //WILD_H
