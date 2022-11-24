#ifndef AMMO_CONTAINER_H
#define AMMO_CONTAINER_H

#include "Item.h"

namespace RPG {

enum AMMO_WEIGHT {
    machine_gun = 6,
    pistol = 5,
    shotgun = 7
};

std::unordered_map<AMMO_WEIGHT, std::string> TYPE_NAME = {{machine_gun, "Machine gun ammo's"},
                                                                 {shotgun, "Shotgun ammo's"},
                                                                 {pistol, "Pistol ammo's"}};

class Ammo_container : public Item {
public:
    /**/explicit Ammo_container(AMMO_WEIGHT type); // initialisation params
    /**/bool take_ammo(int number); // take some ammo from container
    /**/bool put_ammo(int number); // put some ammo to container
    /**/int num_ammo(); // show how much ammo you have
protected:
    AMMO_WEIGHT type;
    int max_count = 100;
    int current_count;
};

} // RPG
#endif //AMMO_CONTAINER_H
