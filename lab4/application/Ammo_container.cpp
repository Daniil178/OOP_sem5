# include "Ammo_container.h"

namespace RPG {

std::unordered_map<AMMO_WEIGHT, std::string> TYPE_NAME_ammo = {{machine_gun, "Machine gun ammo's"},
                                                               {shotgun, "Shotgun ammo's"},
                                                               {pistol, "Pistol ammo's"},
                                                               {empty, "empty"}};


Ammo_container::Ammo_container(AMMO_WEIGHT type0) : // initialisation params
                                                    Item(TYPE_NAME_ammo[type0], 0, AMMO_CONTAINER),
                                                    type(type0),
                                                    current_count(0)
                                                    {}

bool Ammo_container::take_ammo(int number) { // take some ammo from container
    if (number > current_count) {
        return false;
    }
    current_count -= number;
    weight -= number * ((int) type);

    return true;
}
bool Ammo_container::put_ammo(int number) { // put some ammo to container

    if (current_count + number > max_count) {
        return false;
    }
    current_count += number;
    weight += number * ((int) type);

    return true;
}

int Ammo_container::num_ammo() {
    return current_count;
}

AMMO_WEIGHT Ammo_container::get_type() {
    return type;
}

} // RPG