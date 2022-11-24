#include "Item.h"

namespace RPG {
    Item::Item(std::string name, int weight, ITEM_TYPE type0): name(std::move(name)), weight(weight), type(type0) {}

    ITEM_TYPE Item::get_type() const noexcept{
        return type;
    }
}