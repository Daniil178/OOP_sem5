#ifndef FORAGER_H
#define FORAGER_H

#include "Unit.h"
#include "Table.h"

namespace RPG {

class Forager : virtual public Unit {
public:
    Forager(std::string name); // initialisation inventory
    int get_strength(); // get strength
    int get_num_of_items(); // get current size of inventory
    int get_weight(); // get max weight
    int take_item_to_inventory(Item item);

    int put_item_from_inventory(Item item);

protected:
    int strength = 100000; // max weight = 100 kg
    Table inventory; // table with all things
};

} // RPG

#endif //FORAGER_H
