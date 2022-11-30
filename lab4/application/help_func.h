#ifndef OOP_SEM5_HELP_FUNC_H
#define OOP_SEM5_HELP_FUNC_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

namespace RPG {

using coordinate = std::pair<int, int>;

static bool operator==(const coordinate &frst, const coordinate &scnd) {
    return ((frst.first == scnd.first) && (frst.second == scnd.second));
}

//static coordinate operator+(const coordinate& frst, const coordinate& scnd) {
//    coordinate new_pos = std::make_pair(0, 0);
//    new_pos.first = frst.first + scnd.second;
//    new_pos.second = frst.second + scnd.second;
//    return std::make_pair(frst.first + scnd.second, frst.second + scnd.second);
//}

struct mhash {
    std::size_t operator()(std::pair <int, int> const &coor) const noexcept {
        std::size_t h1 = std::hash < int > {}(coor.first);
        std::size_t h2 = std::hash < int > {}(coor.second);
        return h1 ^ (h2 << 1);
    }
};


// Функция генерирования случайного целочисленного числа в указанных пределах.
// Диапазон чисел: [min, max]
static int GetRandomNumber(int min, int max)
{
    srand(time(nullptr));
    int num = min + rand() % (max - min + 1);
    return num;
}

} // RPG

#endif //OOP_SEM5_HELP_FUNC_H
