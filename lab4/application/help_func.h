#ifndef OOP_SEM5_HELP_FUNC_H
#define OOP_SEM5_HELP_FUNC_H

#include <iostream>
//#include <fstream>
//#include <unordered_map>
#include "my_unordered_map.hpp"
#include <string>
#include <vector>
//#include <cstdlib>
//#include <ctime>
#include <random>

namespace RPG {

using coordinate = std::pair<int, int>;

static bool operator==(const coordinate &frst, const coordinate &scnd) {
    return ((frst.first == scnd.first) && (frst.second == scnd.second));
}


static coordinate& operator+=(coordinate& frst, coordinate& scnd) {
    frst.first = frst.first + scnd.first;
    frst.second = frst.second + scnd.second;
    return frst;
}

static coordinate operator+(coordinate& frst, coordinate& scnd) {
    coordinate new_pos = std::make_pair(0, 0);
    new_pos += frst;
    new_pos += scnd;
    return new_pos;
}

struct mhash {
    std::size_t operator()(std::pair <int, int> const &coor) const noexcept {
        std::size_t h1 = std::hash < int > {}(coor.first);
        std::size_t h2 = std::hash < int > {}(coor.second);
        return h1 ^ (h2 << 1);
    }
};


/**
 * @brief Функция генерирования случайного целочисленного числа в указанных пределах.
 *  Диапазон чисел: [min, max]
 */
static int GetRandomNumber(int min, int max)
{
    //srand(time(nullptr));
    std::random_device rd;
    std::mt19937 mersenne(rd());
    int num = (ulong) min + mersenne() % (max - min + 1);
    return num;
}

} // RPG

#endif //OOP_SEM5_HELP_FUNC_H
