#ifndef ITEM_H
#define ITEM_H

#include <string>

enum ITEM_TYPE {
    Medicine_kit = 0,
    ammo_container,
    weapon
};

class Item {
public:
    //Item();
    ITEM_TYPE get_type();
    //Item(int id, std::string name, int weight);
protected:
    ITEM_TYPE type;
    int id; // unique id
    std::string name; // name of thing
    int weight; // weight of item
};

#endif //ITEM_H
