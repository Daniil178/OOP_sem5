#ifndef UNIT_H
#define UNIT_H

//#include "Weapon.h"
//#include "help_func.h"
#include "Cell.h"

namespace RPG {

enum UNIT_TYPE {
    WILD = 0,
    RATIONAL,
    FORAGER,
    OPERATIVE
};

struct basic_unit_parameters {
    int max_health = 100;
    int current_health = 100;
    int time_to_step = 1;
    int max_time = 10;
    int current_time = 10;
    int view_radius = 3;
};

class Unit: public RPG_Object {
public:
    /**/explicit Unit(std::string name, UNIT_TYPE type, coordinate position); // initialisation all params of Units
    /**/UNIT_TYPE get_type(); // fet type of unit
    /**/ [[nodiscard]] basic_unit_parameters get_params() const noexcept; // get max and current health, time and view radius
    /**/ [[nodiscard]] coordinate get_position() const noexcept;
    /*0-died, 1 - leave*/int get_damage(int loss) override; // get damage after attack
    /**/int step(Direction new_position, Map& map_); // change position
protected:
    UNIT_TYPE type;
    std::string name;
    basic_unit_parameters params;
    coordinate position;
    /*current time*/int change_time(int loss_time);
};

} // RPG
#endif //UNIT_H
