#ifndef ITEM_H
#define ITEM_H

#include "RPG_Object.h"
#include <string>

enum ITEM_TYPE {
    Medicine_kit = 0,
    ammo_container,
    weapon
};

class Item{
public:
    //Item();
    ITEM_TYPE get_type();
    //Item(int id, std::string name, int weight);
protected:
    ITEM_TYPE type;
    std::string name;
    int id; // unique id
    int weight; // weight of item
};

#endif //ITEM_H
