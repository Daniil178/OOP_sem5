#ifndef MEDICINE_KIT_H
#define MEDICINE_KIT_H

#include "Item.h"

namespace RPG {

enum MED_KIT_HEALTH {
    Basic = 20,
    Army = 50,
    Scientific = 80
};

std::unordered_map<MED_KIT_HEALTH, std::string> TYPE_NAME = {{Basic, "Basic med"},
                                                             {Army, "Army med"},
                                                             {Scientific, "Scientific med"}};

class Medicine_Kit : public Item {
public:
    /**/explicit Medicine_Kit(MED_KIT_HEALTH); // initialisation type and params
    /**/[[nodiscard]] std::pair<const int, const int> use() const noexcept;

protected:
    MED_KIT_HEALTH type;
    const int score_health;
    static const int time_to_use = 1;
};

} // RPG

#endif //MEDICINE_KIT_H
