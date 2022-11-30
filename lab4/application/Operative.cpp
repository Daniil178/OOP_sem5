#include "Operative.h"

namespace RPG {

Operative::Operative(coordinate position, Weapon &basic_weapon,
                     std::string &name) :
                                         Unit(name, OPERATIVE, position),
                                         Forager(name, position),
                                         Rational(name, position),
                                         time_to_reload(basic_weapon.get_params().bas_params.reload_time){
    current_weapon = &basic_weapon;
}

int Operative::choice_weapon(Weapon* new_weapon) {
    inventory->change_item(new_weapon, current_weapon);
    return 0;
}

int Operative::health(Medicine_Kit* use_kit) {
    coordinate med_params = use_kit->use();
    if (params.current_time < (int) med_params.second) {
        return -2; //don`t have time
    }
    params.current_health += (int) med_params.first;
    if (params.current_health > params.max_health) {
        params.current_health = params.max_health;
    }
    params.current_time -= (int) med_params.second;
//    if (params.current_time == 0) {
//        return -1; //spend all of time
//    }
    return 0;
}

int Operative::reload() {
    if (current_weapon->get_params().weight == 0) {
        return -2; // don`t weapon
    }
    auto container = new Ammo_container(current_weapon->get_params().bas_params.ammo_type);
    auto cont = dynamic_cast<Ammo_container*>(inventory->get_item(dynamic_cast<Item*>(container)));
    int res = current_weapon->reload(cont);
    inventory->put_item(dynamic_cast<Item*>(cont));
    if (res > 0) {
        params.current_time -= res;
    }
    return res; // -1 - bad reload, time_reload - good
}

int Operative::attack() {
    if (current_weapon == nullptr) {
        return -1; // haven't weapon
    }
    if (current_weapon->shot() < 0) {
        return -2; // hasn't ammo's
    }

    params.current_time -= 1;
    if (GetRandomNumber(0, 100) > accuracy) {
        return 1; // missing
    }
    return 0;
}

} // RPG