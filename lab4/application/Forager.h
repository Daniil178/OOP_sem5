#ifndef FORAGER_H
#define FORAGER_H

//#include "Unit.h"
//#include "Table.h"
#include "Rational.h"

namespace RPG {

class Forager : virtual public Unit {
public:
    Forager(std::string name, coordinate pos); // initialisation inventory
    [[nodiscard]] int get_strength() const noexcept; // get strength
    [[nodiscard]] int get_num_of_items() const noexcept; // get current size of inventory
    [[nodiscard]] int get_weight() const noexcept; // get max weight
    //[[nodiscard]] Table* see_inventory() const noexcept;
    int take_item_to_inventory(Item* item, Map& map_);
    int put_item_from_inventory(Item* item, Map& map_);

protected:
    const int strength = 100000; // max weight = 100 kg
    Table* inventory; // table with all things
};

} // RPG

#endif //FORAGER_H
