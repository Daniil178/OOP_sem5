#include "Forager.h"

namespace RPG {

Forager::Forager(std::string name, RPG::coordinate pos):
                                                        Unit(std::move(name),
                                                              FORAGER,
                                                              pos),
                                                        inventory(nullptr)
                                                        {}

int Forager::get_strength() const noexcept{
    return strength;
}

int Forager::get_weight() const noexcept{
    return inventory->get_curr_weight();
}

int Forager::get_num_of_items() const noexcept{
    return inventory->number_of_items();
}

int Forager::take_item_to_inventory(Item *item, Map& map_) {
    if (strength - inventory->get_curr_weight() < item->get_weight()) {
        return -1; // tired
    }
    if (map_[position].take_item(item) == nullptr) {
        return -2; // not object
    }
    inventory->change_weight(-item->get_weight());
    inventory->put_item(item);
    return 0;
}

int Forager::put_item_from_inventory(Item *item, Map& map_) {
    if (inventory->get_item(item) == nullptr) {
        return -1; // not object
    }
    inventory->change_weight(item->get_weight());
    map_[position].put_item(item);
    return 0;
}

//Table* Forager::see_inventory() const noexcept {
//    auto curr_item = inventory->get_iter();
//}

} // RPG