#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
#include "Ammo_container.h"
#include <map>

struct WEAPON_PARAMS {
    int damage;
    int range;
    int reload_time;
    AMMO_WEIGHT ammo_type;
    int max_ammo;
};

enum WEAPON_TYPE {
    AK_74 = 0,
    RPK_74,
    PM,
    TO3_34
};

std::map<WEAPON_TYPE, WEAPON_PARAMS> weapon_type_params = {{AK_74, {15, 4, 2, machine_gun, 30}},
                                                           {RPK_74, {20, 4, 3, machine_gun, 45}},
                                                           {PM, {10, 2, 1, pistol, 8}},
                                                           {TO3_34, {30, 1, 2, shotgun, 2}}};

class Weapon: public Item {
public:
    Weapon(WEAPON_TYPE type, int ammo_number); // initialisation params
    int shot(); // make attack with gun
    int shot_result(); // get result of shot
    int get_damage(); // get damage, which gun can make
    int reload(); // update ammo in gun
protected:
    WEAPON_TYPE type;
    WEAPON_PARAMS basic_params;
    int shot_time = 1;
    int ammo_number;
};



#endif