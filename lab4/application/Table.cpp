# include "Table.h"

namespace RPG {

Table::Table(): weight(0) {}

int Table::number_of_items() {
    return (int) inventory.size();
}

int Table::change_item(Item* new_item, Item* old_item) {
    auto curr_item = inventory.begin();
    while(curr_item != inventory.end()) {
        if (*curr_item == old_item) {
            *curr_item = new_item;
            weight += -old_item->get_weight() + new_item->get_weight();
            //inventory.erase(curr_item);
            return 0;
        }
    }
    return -1; // not have old
}

Item* Table::get_item(Item* item) {
    auto curr_item = inventory.begin();
    while(curr_item != inventory.end()) {
        if (*curr_item == item) {
            inventory.erase(curr_item);
            weight -= item->get_weight();
            return item;
        }
    }
    return nullptr; // not have old
}

int Table::put_item(Item* item) {
    inventory.push_back(item);
    weight += item->get_weight();
    return 0;
}

int Table::get_curr_weight() const noexcept {
    return weight;
}

int Table::change_weight(int loss) {
    if (loss > weight) {
        return -1; // wtf ?!
    }
    weight -= loss;
    return 0;
}

std::vector<Item*>::iterator Table::get_iter() {
    return inventory.begin();
}

} // RPG
