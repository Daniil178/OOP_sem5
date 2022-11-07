#ifndef UNIT_H
#define UNIT_H

#include <string>
#include "Weapon.h"

enum Direction {
    Left = 0,
    Down,
    Up,
    Right
};

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
    int accuracy = 90; // in %
    int view_radius = 3;
};

class Unit {
public:
    Unit(std::string name, UNIT_TYPE type, std::pair<uint, uint> position); // initialisation all params of Units
    UNIT_TYPE get_type(); // fet type of unit
    basic_unit_parameters get_basic_params(); // get max and current health, time and view radius
    int change_params(int loss_time);
    int get_damage(int loss); // get damage after attack
    int step(Direction new_position); // change position
protected:
    std::string name;
    UNIT_TYPE type;
    basic_unit_parameters params;
    std::pair<uint, uint> position;
};

#endif //UNIT_H
