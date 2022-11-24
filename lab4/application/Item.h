#ifndef ITEM_H
#define ITEM_H

#include "RPG_Object.h"
#include <string>
#include <unordered_map>

namespace RPG {

enum ITEM_TYPE {
    MEDICINE_KIT = 0,
    AMMO_CONTAINER,
    WEAPON
};

class Item {
public:
    //Item();
    /**/[[nodiscard]] ITEM_TYPE get_type() const noexcept;
    /**/Item(std::string name, int weight, ITEM_TYPE type0);
protected:
    const ITEM_TYPE type;
    const std::string name;
    //int id; // unique id
    int weight; // weight of item
};

} //RPG

#endif //ITEM_H
