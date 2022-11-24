#include "Medicine_Kit.h"

namespace RPG {

Medicine_Kit::Medicine_Kit(MED_KIT_HEALTH type0) :
                                                    Item(TYPE_NAME[type0], 200, MEDICINE_KIT),
                                                    type(type0),
                                                    score_health((int) type0) {}

std::pair<const int, const int> Medicine_Kit::use() const noexcept {
    return std::make_pair(score_health, time_to_use);
}

} //RPG