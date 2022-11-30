#ifndef WEAPON_H
#define WEAPON_H

//#include "Ammo_container.h"
#include "Table.h"

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
    TO3_34,
    Empty
};




class Weapon : public Item {
public:
    /**/ Weapon();
    /**/explicit Weapon(WEAPON_TYPE type, int ammo_number); // initialisation params
    /**/ WEAPON_TYPE get_type();
    /*range or -1*/int shot(); // make attack with gun
    /*Have I ammo?*/bool shot_result(); // get result of shot
    /*damage*/int get_damage(); // get damage, which gun can make. return damage
    /*time_to_reload||-1*/int reload(Ammo_container* container); // update ammo in gun, return time_to_reload
    /*struct with params*/[[nodiscard]] WEAPON_PARAMS_WEIGHT get_params() const noexcept;
    /**/ [[nodiscard]] int time_to_shot() const noexcept;
    /**/ [[nodiscard]] int get_ammo_num() const noexcept;
    static std::unordered_map<WEAPON_TYPE, WEAPON_PARAMS_WEIGHT> weapon_type_params;
    static std::unordered_map<WEAPON_TYPE, std::string> TYPE_NAME_weapon;
protected:
    const WEAPON_TYPE type;
    const WEAPON_PARAMS_WEIGHT params;
    static const int shot_time = 1;
    int ammo_number;
};

} // RPG

#endif