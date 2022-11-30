#include "Cell.h"

namespace RPG {

    std::unordered_map<CELL_TYPE, cell_params> Cell::CELL_TYPE_PARAMS = {{Floor,         {true,  false, true}},
                                                                   {Wall,          {false, false, false}},
                                                                   {Glass,         {true,  true,  false}},
                                                                   {Partition,     {false, true,  false}},
                                                                   {Storage_point, {true,  false, true}},
                                                                   {Have_item,     {true,  false, true}}};

    Cell::Cell(): type(Floor), parameters(CELL_TYPE_PARAMS[Floor]) {}

    Cell::Cell(CELL_TYPE type0, std::vector<Item*> items):
                                                            type(type0),
                                                            all_items(std::move(items)),
                                                            parameters(CELL_TYPE_PARAMS[type0])
                                                            {}

    int Cell::change_type(CELL_TYPE new_type) {
        type = new_type;
        parameters = CELL_TYPE_PARAMS[type];
        return 0;
    }

    CELL_TYPE Cell::get_type() {
        return type;
    }

    bool Cell::can_go_through() {
        return parameters.go_through;
    }

    bool Cell::is_visible() {
        return parameters.visible;
    }

    int Cell::get_damage(int damage_num) {
        if (parameters.go_through) {
            return 1; // go_through
        }
        if (!parameters.destroy) {
            return -1; // can't destroy
        }
        this->change_type(Floor);
        return 0;
    }

    Item* Cell::take_item(Item* item) {
        auto curr_item = all_items.begin();
        while(curr_item != all_items.end()) {
            if (*curr_item == item) {
                all_items.erase(curr_item);
                if (all_items.empty()) {
                    this->change_type(Floor);
                }
                return item;
            }
        }
        return nullptr;
    }

    int Cell::put_item(Item* item) {
        if (type == Wall || type == Glass || type == Partition) {
            return -1;
        }
        else if (type == Floor) {
            this->change_type(Have_item);
        }
        all_items.push_back(item);
        return 0;
    }
}