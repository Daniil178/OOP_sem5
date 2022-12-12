#ifndef LEVEL_H
#define LEVEL_H

#include "Operative.h"

namespace RPG {

/**
 * @brief Level - has map, operatives and enemies and manage to they
 */
class Level {
public:
    /**
     * @brief default constructor of Level
     */
    Level();
    /**
     * @brief constructor of Level with size only
     * @param size0 (coordinate) - size of Level
     */
    explicit Level(coordinate size0);
    /**
     * @brief full constructor of level
     * @param size0 (coordinate) - size of level map
     * @param operatives (vector<Operative*>) - vector of operatives on level
     * @param enemies (vector<Unit*>) - vector of enemies on level
     */
    explicit Level(coordinate size0, std::vector<Operative*> operatives, std::vector<Unit *> enemies);

    /**
     * @brief check size of map
     * @return (coordinate) - size of map
     */
    coordinate get_size();
    /**
     * @brief change size and rebuild level
     * @param new_size (coordinate) - new size of map
     * @return (int) - -1 - incorrect data, \n
     * 0 - successfully changed
     */
    int change_size(coordinate new_size);
    /**
     * @brief attack of unit
     * @param who (Wild*) - who does the damage
     * @param where (Direction) - where unit do attack
     * @return (int) - result of attack: \n
     * \<0 - attacker mob can't do it, \n
     *  1 - attacker missing, \n
     *  0 - successfully shot, \n
     *  100 - kill and delete unit
     */
    int shot(Wild* who, Direction where);
    /**
     * @brief initialize basic params
     */
    void start();
    /**
     * @brief check finish flag
     * @return (int) - finish flag: \n
     * 0 - don't finish, \n
     * 1 - win, \n
     * 2 - lose
     */
    [[nodiscard]] int check_flag() const noexcept;

    /**
     * @brief map of level
     */
    Map map_;
    /**
     * @brief all operatives on level
     */
    std::vector<Operative*> operatives;
    /**
     * @brief all enemies on level
     */
    std::vector<Unit *> enemies;

    /**
     * @brief destructor - delete all Cells, operatives and enemies
     */
    ~Level();
protected:
    /**
     * @brief (coordinate) - size of map
     */
    coordinate size;
    /**
     * @brief (int) - finish flag: \n
     * 0 - don't finish, \n
     * 1 - win, \n
     * 2 - lose
     */
    int finish_flag;
};

} // RPG
#endif //LEVEL_H
