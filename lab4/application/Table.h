#ifndef TABLE_H
#define TABLE_H


//#include "Weapon.h"
//#include "Ammo_container.h"
#include "Medicine_Kit.h"

namespace RPG {

class Table {
public:
    Table(); // initialisation of empty table
    int number_of_items(); // return number of current things
    int change_item(Item* new_item, Item* old_item); // change current thing
    Item* get_item(Item* item); // take item from inventory
    int put_item(Item* item); // put item to inventory
    [[nodiscard]] int get_curr_weight() const noexcept;
    int change_weight(int loss);
    std::vector<Item*>::iterator get_iter();
protected:
    int weight;
    std::vector<Item *> inventory;
};

} // RPG

#endif //TABLE_H
