#ifndef MEDICINE_KIT_H
#define MEDICINE_KIT_H

#include "Item.h"

enum MED_KIT_HEALTH {
    Basic = 20,
    Army = 50,
    Scientific = 80
};

class Medicine_Kit: public Item {
public:
    Medicine_Kit(MED_KIT_HEALTH); // initialisation type and params
    [[nodiscard]] std::pair<int, int> use() const noexcept;
protected:
    MED_KIT_HEALTH type;
    int score_health;
    int time_to_use;
};

#endif //MEDICINE_KIT_H
