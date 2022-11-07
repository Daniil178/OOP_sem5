#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include "Item.h"

class Table {
public:
    Table(); // initialisation of empty table
    int number_of_items(); // return number of current things
    int change_item(Item new_item, Item old_item); // change current thing
    Item get_item(Item item); // take item from inventory
    int put_item(Item item); // put item to inventory
protected:
    std::vector<Item> inventory;
};

#endif //TABLE_H
