#ifndef MEDICINE_KIT_H
#define MEDICINE_KIT_H

//#include "Item.h"
#include "Ammo_container.h"

namespace RPG {

enum MED_KIT_HEALTH {
    Basic = 20,
    Army = 50,
    Scientific = 80
};



class Medicine_Kit : virtual public Item {
public:
    /**/explicit Medicine_Kit(MED_KIT_HEALTH); // initialisation type and params
    ///
    /// @brief  just return needed params and after you must delete it
    /// \return pair of params: (score_health, time_to_use)
    /**/[[nodiscard]] std::pair<int, int> use() const noexcept;
    /**/[[nodiscard]] MED_KIT_HEALTH get_type();

protected:
    MED_KIT_HEALTH type;
    const int score_health;
    const int time_to_use = 1;
};

} // RPG

#endif //MEDICINE_KIT_H
