#include "Medicine_Kit.h"

namespace RPG {

std::unordered_map<MED_KIT_HEALTH, std::string> TYPE_NAME_med = {{Basic, "Basic med"},
                                                                 {Army, "Army med"},
                                                                 {Scientific, "Scientific med"}};

Medicine_Kit::Medicine_Kit(MED_KIT_HEALTH type0) :
                                                    Item(TYPE_NAME_med[type0], 200, MEDICINE_KIT),
                                                    type(type0),
                                                    score_health((int) type0) {}

std::pair<int, int> Medicine_Kit::use() const noexcept {
    return std::make_pair(score_health, time_to_use);
}

MED_KIT_HEALTH Medicine_Kit::get_type(){
    return type;
}

} //RPG