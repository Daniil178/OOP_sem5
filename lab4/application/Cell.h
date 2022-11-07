#ifndef CELL_H
#define CELL_H

#include "Item.h"
#include <vector>

enum CELL_TYPE {
    Floor = 0,
    Wall, // can't destroy and see
    Glass, // can destroy and see
    Partition, // can destroy and can't see
    Storage_point, // have items
    have_item // if anything put item, will have it
};

class Cell {
public:
    Cell(CELL_TYPE type, std::vector<Item> items); // initialisation params
    int change_type(CELL_TYPE new_type); // change type, when we destroy cell
    CELL_TYPE get_type(); // get type of cell
    Item take_item(Item item); // take item from cell
    int put_item(Item item); // put item on cell
protected:
    CELL_TYPE type;
    std::vector<Item*> items; // items which cell has
};

#endif //CELL_H
