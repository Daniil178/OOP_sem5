#include "Weapon.h"

namespace RPG {
    Weapon::Weapon(WEAPON_TYPE type0, int ammo_number):
                                                                Item
                                                                    (TYPE_NAME_weapon[type0],
                                                                     weapon_type_params[type0].weight,
                                                                     WEAPON
                                                                     ),
                                                                params(weapon_type_params[type0]),
                                                                ammo_number(ammo_number),
                                                                type(type0)
                                                                {}

    bool Weapon::shot() {
        // questions for shot...
        if (ammo_number == 0) {
            return false;
        }
        ammo_number -= 1;

        return true;
    }

    // how to get result...
    int Weapon::shot_result() {
        return params.bas_params.range;
    }


    int Weapon::get_damage() {
        return params.bas_params.damage;
    }

    int Weapon::reload(Ammo_container& container) {
        // take ammo's from container
        //if (don't have ammo) { return -1;}
        int get_ammo = params.bas_params.max_ammo - ammo_number;
        int curr_ammo = container.num_ammo();
        if (curr_ammo < get_ammo && curr_ammo > 0) {
            get_ammo = curr_ammo;
        }
        else if (curr_ammo <= 0) {
            return -1;
        }
        container.take_ammo(get_ammo);
        ammo_number += get_ammo;

        return params.bas_params.reload_time;
    }

    WEAPON_PARAMS_WEIGHT Weapon::get_params() const noexcept {
        return params;
    }

} // RPG