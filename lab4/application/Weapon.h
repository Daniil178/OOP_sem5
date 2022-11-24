#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
#include "Ammo_container.h"

namespace RPG {

struct WEAPON_PARAMS {
    int damage;
    int range;
    int reload_time;
    AMMO_WEIGHT ammo_type;
    int max_ammo;
};

struct WEAPON_PARAMS_WEIGHT {
    WEAPON_PARAMS bas_params;
    int weight;
};

enum WEAPON_TYPE {
    AK_74 = 0,
    RPK_74,
    PM,
    TO3_34
};

std::unordered_map<WEAPON_TYPE, WEAPON_PARAMS_WEIGHT> weapon_type_params = {{AK_74,  {{15, 4, 2, machine_gun, 10}, 4000}},
                                                                     {RPK_74, {{20, 4, 3, machine_gun, 15}, 5000}},
                                                                     {PM,     {{10, 2, 1, pistol,      8}, 800}},
                                                                     {TO3_34, {{30, 1, 2, shotgun,     2}, 3000}}};

std::unordered_map<WEAPON_TYPE, std::string> TYPE_NAME_weapon = {{AK_74, "AK_74"},
                                                                 {RPK_74, "RPK_74"},
                                                                 {PM, "PM"},
                                                              {TO3_34, "TO3_34"}};

class Weapon : public Item {
public:
    /**/explicit Weapon(WEAPON_TYPE type, int ammo_number); // initialisation params
    /**/bool shot(); // make attack with gun
    int shot_result(); // get result of shot
    /*range*/int get_damage(); // get damage, which gun can make. return damage
    /*time_to_reload||-1*/int reload(Ammo_container& container); // update ammo in gun, return time_to_reload
    /**/[[nodiscard]] WEAPON_PARAMS_WEIGHT get_params() const noexcept;
protected:
    const WEAPON_TYPE type;
    const WEAPON_PARAMS_WEIGHT params;
    static const int shot_time = 1;
    int ammo_number;
};

} // RPG

#endif