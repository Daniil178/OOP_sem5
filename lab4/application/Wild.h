#ifndef WILD_H
#define WILD_H

#include "Unit.h"

namespace RPG {

class Wild : virtual public Unit {
public:
    Wild(std::string name); // initialisation damage and range of attack
    int get_num_damage(); // get damage
    int get_range(); // get range of attack
    int get_accuracy(); // get accuracy of attack in %
    virtual int attack(Direction direct); // make damage to cell
protected:
    int damage;
    int range;
    int accuracy = 90; // in %
};

} // RPG

#endif //WILD_H
