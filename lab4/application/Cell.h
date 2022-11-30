#ifndef CELL_H
#define CELL_H

#include "Weapon.h"

namespace RPG {

enum CELL_TYPE {
    Floor = 0,
    Wall,          // can't destroy and see
    Glass,         // can destroy and see
    Partition,     // can destroy and can't see
    Storage_point, // have items
    Have_item      // if anything put item, will have it
};

struct cell_params {
    bool visible;
    bool destroy;
    bool go_through;
};


class Cell : RPG_Object {
public:
    Cell();
    explicit Cell(CELL_TYPE type, std::vector<Item*> items); // initialisation params

    CELL_TYPE get_type(); // get type of cell
    Item* take_item(Item* item); // take item from cell
    int put_item(Item* item); // put item on cell
    bool is_visible();
    int get_damage(int) override;
    bool can_go_through();
    static std::unordered_map<CELL_TYPE, cell_params> CELL_TYPE_PARAMS;

protected:
    CELL_TYPE type;
    std::vector<Item *> all_items; // items which cell has
    cell_params parameters;
    int change_type(CELL_TYPE new_type); // change type, when we destroy cell
};


using Map = std::unordered_map<coordinate, Cell, mhash>;

}//RPG
#endif //CELL_H
