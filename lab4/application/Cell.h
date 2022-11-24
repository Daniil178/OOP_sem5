#ifndef CELL_H
#define CELL_H

#include "Item.h"
#include <unordered_map>
#include <vector>

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

std::unordered_map<CELL_TYPE, cell_params> CELL_TYPE_PARAMS = {{Floor,         {true,  false, true}},
                                                               {Wall,          {false, false, false}},
                                                               {Glass,         {true,  true,  false}},
                                                               {Partition,     {false, true,  false}},
                                                               {Storage_point, {true,  false, true}},
                                                               {Have_item,     {true,  false, true}}};


class Cell : RPG_Object {
public:
    Cell(CELL_TYPE type, std::vector<Item *> items); // initialisation params
    int change_type(CELL_TYPE new_type); // change type, when we destroy cell
    CELL_TYPE get_type(); // get type of cell
    Item take_item(Item item); // take item from cell
    int put_item(Item item); // put item on cell
    bool is_visible();

    int get_damage(int) override;

    bool can_go_through();

protected:
    CELL_TYPE type;
    std::vector<Item *> items; // items which cell has
    cell_params parameters;
};

}//RPG
#endif //CELL_H
