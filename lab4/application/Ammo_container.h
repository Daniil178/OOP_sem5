#ifndef AMMO_CONTAINER_H
#define AMMO_CONTAINER_H

#include "Item.h"

enum AMMO_WEIGHT {
    machine_gun = 150,
    pistol = 50,
    shotgun = 70
};

class Ammo_container: public Item {
public:
    Ammo_container(AMMO_WEIGHT type); // initialisation params
    int take_ammo(int number); // take some ammo from container
    int put_ammo(int number); // put some ammo to container
protected:
    AMMO_WEIGHT type;
    int max_count = 100;
    int current_count;
};

#endif //AMMO_CONTAINER_H
