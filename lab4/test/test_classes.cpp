#include "../../Google_tests/googletest-main/googletest/include/gtest/gtest.h"

#include "Level.h"

using namespace RPG;

static int accuracy0 = 90;

TEST(Test_item, all_methods) {
    Item item("lala", 200, WEAPON);
    Item* med = new Medicine_Kit(Basic);

    EXPECT_EQ(200, item.get_weight());
    EXPECT_EQ(WEAPON, item.get_type());

    EXPECT_EQ(MEDICINE_KIT, med->get_type());
    EXPECT_EQ(200, med->get_weight());

    auto med1 = dynamic_cast<Medicine_Kit*>(med);
    EXPECT_EQ(std::make_pair(20, 1), med1->use());

    delete med1;
}

TEST(Test_med_kit, use) {
    Medicine_Kit bas(Basic), arm(Army), scien(Scientific);
    EXPECT_EQ(std::make_pair(20, 1), bas.use());
    EXPECT_EQ(std::make_pair(50, 1), arm.use());
    EXPECT_EQ(std::make_pair(80, 1), scien.use());

    EXPECT_EQ(200, bas.get_weight());
    EXPECT_EQ(Army, arm.get_type());
}

TEST(Test_ammo_container, all_methods) {
    Ammo_container pist(pistol);
    EXPECT_EQ(0, pist.num_ammo());
    EXPECT_EQ(false, pist.take_ammo(20));
    EXPECT_EQ(true, pist.put_ammo(40));
    EXPECT_EQ(40, pist.num_ammo());
    EXPECT_EQ(200, pist.get_weight());
    EXPECT_EQ(false, pist.put_ammo(100));
    pist.take_ammo(20);
    EXPECT_EQ(400, pist.get_weight());
    EXPECT_EQ(pistol, pist.get_type());
}

TEST(Test_weapon, all_methods) {
    Ammo_container cont(machine_gun), cont1(shotgun);
    Weapon pist(PM, 0), mg(RPK_74, 10), sht(TO3_34, 1), gun(AK_74, 5);
    EXPECT_EQ(PM, pist.get_type());
    EXPECT_EQ(RPK_74, mg.get_type());
    EXPECT_EQ(TO3_34, sht.get_type());
    EXPECT_EQ(AK_74, gun.get_type());
    EXPECT_EQ(800, pist.get_params().weight);
    EXPECT_EQ(5000, mg.get_params().weight);

    EXPECT_EQ(20, mg.get_damage());
    EXPECT_EQ(1, mg.time_to_shot());
    EXPECT_EQ(true, mg.shot_result());

    EXPECT_EQ(-1, pist.shot());
    EXPECT_EQ(4, mg.shot());
    EXPECT_EQ(9, mg.get_ammo_num());

    cont.put_ammo(9);
    EXPECT_EQ(3, mg.reload(&cont));
    EXPECT_EQ(15, mg.get_ammo_num());
    EXPECT_EQ(2, gun.reload(&cont));
    EXPECT_EQ(8, gun.get_ammo_num());
    for(int i = 0; i < 3; ++i) {
        gun.shot();
    }
    EXPECT_EQ(-1, gun.reload(&cont));
}

TEST(Test_cell, floor_all_methods) {
    Cell basicCell;
    Item *med = new Medicine_Kit(Army);

    EXPECT_EQ(Floor, basicCell.get_type());
    EXPECT_EQ(true, basicCell.is_visible());
    EXPECT_EQ(true, basicCell.can_go_through());
    EXPECT_EQ(1, basicCell.get_damage(5));
    EXPECT_EQ(nullptr, basicCell.take_item(med));
    EXPECT_EQ(0, basicCell.put_item(med));
    EXPECT_EQ(Have_item, basicCell.get_type());
    EXPECT_EQ(med, basicCell.take_item(med));
    EXPECT_EQ(Floor, basicCell.get_type());

    delete dynamic_cast<Medicine_Kit*>(med);
}


TEST(Test_cell, wall_all_methods) {
    Cell wall_(Wall);
    Item *med = new Medicine_Kit(Army);

    EXPECT_EQ(Wall, wall_.get_type());
    EXPECT_EQ(false, wall_.is_visible());
    EXPECT_EQ(false, wall_.can_go_through());
    EXPECT_EQ(-1, wall_.get_damage(5));
    EXPECT_EQ(nullptr, wall_.take_item(med));
    EXPECT_EQ(-1, wall_.put_item(med));

    delete dynamic_cast<Medicine_Kit*>(med);
}

TEST(Test_cell, partition_all_methods) {
    Cell part(Partition);
    Item* med = new Medicine_Kit(Army);

    EXPECT_EQ(Partition, part.get_type());
    EXPECT_EQ(false, part.is_visible());
    EXPECT_EQ(false, part.can_go_through());
    EXPECT_EQ(-1, part.put_item(med));

    EXPECT_EQ(0, part.get_damage(5));
    EXPECT_EQ(Floor, part.get_type());

    delete dynamic_cast<Medicine_Kit*>(med);
}

TEST(Test_unit, all_methods) {
    Unit wild("wild", WILD, std::make_pair(0, 0));
    Cell wall(Wall), basicCell;
//    Map map_ = {{std::make_pair(0, 0), basicCell}, {std::make_pair(0, 1), basicCell}, {std::make_pair(1, 0), wall}};
    Map map_;
    map_[std::make_pair(0, 0)] = &basicCell;
    map_[std::make_pair(0, 1)] = &basicCell;
    map_[std::make_pair(1, 0)] = &wall;

    EXPECT_EQ(WILD, wild.get_type());
    EXPECT_EQ(std::make_pair(0, 0), wild.get_position());
    EXPECT_EQ(100, wild.get_params().current_health);
    EXPECT_EQ(1, wild.get_params().time_to_step);
    EXPECT_EQ(10, wild.get_params().max_time);
    EXPECT_EQ(3, wild.get_params().view_radius);
    EXPECT_EQ(100, wild.get_params().max_health);
    EXPECT_EQ(10, wild.get_params().current_time);

    EXPECT_EQ(0, wild.get_damage(50));
    EXPECT_EQ(50, wild.get_params().current_health);
    EXPECT_EQ(100, wild.get_damage(50));
    EXPECT_EQ(0, wild.get_params().current_health);

    EXPECT_EQ(-1, wild.step(Down, map_));
    EXPECT_EQ(0, wild.step(Right, map_));
    EXPECT_EQ(std::make_pair(0, 1), wild.get_position());

    for(int i = 0; i < 4; ++i) {
        EXPECT_EQ(0, wild.step(Left, map_));
        EXPECT_EQ(0, wild.step(Right, map_));
    }
    EXPECT_EQ(0, wild.step(Left, map_));
    EXPECT_EQ(1, wild.step(Right, map_));
}

TEST(Test_wild, all_methods) {
    Wild wild("wild", std::make_pair(0, 0));
    Cell wall(Wall), basicCell;
//    Map map_ = {{std::make_pair(0, 0), basicCell}, {std::make_pair(0, 1), basicCell}, {std::make_pair(1, 0), wall}};
    Map map_;
    map_[std::make_pair(0, 0)] = &basicCell;
    map_[std::make_pair(0, 1)] = &basicCell;
    map_[std::make_pair(1, 0)] = &wall;

    EXPECT_EQ(WILD, wild.get_type());
    EXPECT_EQ(25, wild.get_num_damage());
    EXPECT_EQ(1, wild.get_range());
    EXPECT_EQ(accuracy0, wild.get_accuracy());

    EXPECT_EQ(10, wild.get_params().max_time);
    wild.attack();
    EXPECT_EQ(9, wild.get_params().current_time);

    EXPECT_EQ(-1, wild.step(Down, map_));
    EXPECT_EQ(0, wild.step(Right, map_));
    EXPECT_EQ(std::make_pair(0, 1), wild.get_position());
    for(int i = 0; i < 8; ++i) {
        wild.attack();
    }
    EXPECT_EQ(-3, wild.attack());
}

TEST(Test_rational, all_methods) {
    Rational rat("rational", std::make_pair(0, 0));
    auto pm = new Weapon(PM, 5), pm1 = new Weapon(PM, 0);
    std::vector<Item*> items2 = {dynamic_cast<Item*>(pm), dynamic_cast<Item*>(pm1)};
    Cell* wall = new Cell(Wall);
    Cell* have_item = new Cell(Have_item, items2);
    Cell* basicCell = new Cell();
//    Map map_ = {{std::make_pair(0, 0), have_item}, {std::make_pair(0, 1), basicCell}, {std::make_pair(1, 0), wall}};
    Map map_;
    map_[std::make_pair(0, 0)] = have_item;
    map_[std::make_pair(0, 1)] = basicCell;
    map_[std::make_pair(1, 0)] = wall;

    EXPECT_EQ(RATIONAL, rat.get_type());
    EXPECT_EQ(0, rat.get_num_damage());
    EXPECT_EQ(0, rat.get_range());
    EXPECT_EQ(accuracy0, rat.get_accuracy());

    EXPECT_EQ(nullptr, rat.get_current_weapon());
    EXPECT_EQ(-1, rat.attack());

    EXPECT_EQ(0, rat.take_weapon(map_));
    EXPECT_EQ(pm, rat.get_current_weapon());
    EXPECT_EQ(0, rat.attack());
    EXPECT_EQ(9, rat.get_params().current_time);
    EXPECT_EQ(4, rat.get_current_weapon()->get_ammo_num());
    EXPECT_EQ(0, rat.put_current_weapon(map_));

    EXPECT_EQ(nullptr, rat.get_current_weapon());
    EXPECT_EQ(0, rat.take_weapon(map_));
    EXPECT_EQ(-2, rat.attack());

    delete have_item;
    delete basicCell;
    delete wall;
}

TEST(Test_table, all_methods) {
    Table inventory;
    auto pm = new Weapon(PM, 5);
    auto arm = new Medicine_Kit(Army);
    auto ammo_pm = new Ammo_container(pistol);
    Medicine_Kit prob(Army);
    Weapon pm1(PM, 0);

    EXPECT_EQ(0, inventory.number_of_items());
    EXPECT_EQ(0, inventory.get_curr_weight());
    EXPECT_EQ(nullptr, inventory.change_item(pm, arm));
    EXPECT_EQ(nullptr, inventory.get_item(pm));

    EXPECT_EQ(0, inventory.put_item(pm));
    EXPECT_EQ(1, inventory.number_of_items());
    EXPECT_EQ(800, inventory.get_curr_weight());

    EXPECT_EQ(0, inventory.change_weight(800));
    inventory.change_weight(-800);

    EXPECT_EQ(pm, inventory.change_item(arm, &pm1));
    EXPECT_EQ(0, inventory.put_item(pm));
    EXPECT_EQ(2, inventory.number_of_items());
    EXPECT_EQ(1000, inventory.get_curr_weight());

    EXPECT_EQ(arm, inventory.change_item(ammo_pm, arm));
    EXPECT_EQ(800, inventory.get_curr_weight());
    ammo_pm->put_ammo(90);
    EXPECT_EQ(0, inventory.update_params());
    EXPECT_EQ(1250, inventory.get_curr_weight());

    EXPECT_EQ(nullptr, inventory.get_item(&prob));
    EXPECT_EQ(pm, inventory.get_item(&pm1));
    EXPECT_EQ(1, inventory.number_of_items());

    delete pm;
    delete arm;
}

TEST(Test_forager, all_methods) {
    Forager enemy("forager", std::make_pair(0, 0));
    auto pm = new Weapon(PM, 5);
    auto arm = new Medicine_Kit(Army);
    auto ammo_pm = new Ammo_container(pistol);

    std::vector<Item*> items2 = {dynamic_cast<Item*>(pm), dynamic_cast<Item*>(arm), dynamic_cast<Item*>(ammo_pm)};
    Cell* wall = new Cell(Wall);
    Cell* have_item = new Cell(Have_item, items2);
    Cell* basicCell = new Cell();
//    Map map_ = {{std::make_pair(0, 1), have_item}, {std::make_pair(0, 0), basicCell}, {std::make_pair(1, 0), wall}};
    Map map_;
    map_[std::make_pair(0, 1)] = have_item;
    map_[std::make_pair(0, 0)] = basicCell;
    map_[std::make_pair(1, 0)] = wall;

    EXPECT_EQ(FORAGER, enemy.get_type());

    EXPECT_EQ(100000, enemy.get_strength());
    EXPECT_EQ(0, enemy.get_num_of_items());
    EXPECT_EQ(0, enemy.get_weight());

    EXPECT_EQ(100, enemy.get_params().current_health);
    EXPECT_EQ(0, enemy.get_damage(10));
    EXPECT_EQ(90, enemy.get_params().current_health);

    EXPECT_EQ(10, enemy.get_params().current_time);
    EXPECT_EQ(0, enemy.step(Right, map_));
    EXPECT_EQ(0, enemy.take_item_to_inventory(pm, map_));
    EXPECT_EQ(0, enemy.take_item_to_inventory(ammo_pm, map_));
    EXPECT_EQ(0, enemy.take_item_to_inventory(arm, map_));
    EXPECT_EQ(Floor, map_[std::make_pair(0, 1)]->get_type());

    EXPECT_EQ(3, enemy.get_num_of_items());
    EXPECT_EQ(1000, enemy.get_weight());

    EXPECT_EQ(0, enemy.put_item_from_inventory(arm, map_));
    EXPECT_EQ(Have_item, map_[std::make_pair(0, 1)]->get_type());
    EXPECT_EQ(2, enemy.get_num_of_items());
    EXPECT_EQ(800, enemy.get_weight());

    delete have_item;
    delete basicCell;
    delete wall;
}

TEST(Test_operative, all_methods) {
    auto pm = new Weapon(PM, 5);
    auto ak = new Weapon(AK_74, 8);
    Operative enemy(std::make_pair(0, 0), ak, "operative1");
    auto arm = new Medicine_Kit(Army);
    auto ammo_pm = new Ammo_container(pistol);
    auto ammo_pm1 = Ammo_container(pistol);
    auto ammo_ak = new Ammo_container(machine_gun);
    ammo_pm->put_ammo(90);
    ammo_ak->put_ammo(40);

    std::vector<Item*> items2 = {dynamic_cast<Item*>(pm), dynamic_cast<Item*>(arm),
                                         dynamic_cast<Item*>(ammo_pm), dynamic_cast<Item*>(ammo_ak)};
    Cell* wall = new Cell(Wall);
    Cell* have_item = new Cell(Have_item, items2);
    Cell* basicCell = new Cell();
//    Map map_ = {{std::make_pair(0, 1), have_item}, {std::make_pair(0, 0), basicCell}, {std::make_pair(1, 0), wall}};
    Map map_;
    map_[std::make_pair(0, 1)] = have_item;
    map_[std::make_pair(0, 0)] = basicCell;
    map_[std::make_pair(1, 0)] = wall;

    EXPECT_EQ(OPERATIVE, enemy.get_type());

    EXPECT_EQ(100000, enemy.get_strength());
    EXPECT_EQ(0, enemy.get_num_of_items());
    EXPECT_EQ(0, enemy.get_weight());

    EXPECT_EQ(100, enemy.get_params().current_health);
    EXPECT_EQ(0, enemy.get_damage(10));
    EXPECT_EQ(90, enemy.get_params().current_health);

    EXPECT_EQ(-1, enemy.choice_weapon(pm));

    EXPECT_EQ(10, enemy.get_params().current_time);
    EXPECT_EQ(0, enemy.step(Right, map_));
    EXPECT_EQ(0, enemy.take_item_to_inventory(pm, map_));
    EXPECT_EQ(0, enemy.take_item_to_inventory(ammo_ak, map_));
    EXPECT_EQ(0, enemy.take_item_to_inventory(&ammo_pm1, map_));
    EXPECT_EQ(0, enemy.take_item_to_inventory(arm, map_));
    EXPECT_EQ(Floor, map_[std::make_pair(0, 1)]->get_type());

    EXPECT_EQ(4, enemy.get_num_of_items());
    EXPECT_EQ(1690, enemy.get_weight());

    EXPECT_EQ(0, enemy.heal(arm));
    EXPECT_EQ(100, enemy.get_params().current_health);

    EXPECT_EQ(0, enemy.attack());
    EXPECT_EQ(7, enemy.get_current_weapon()->get_ammo_num());

    EXPECT_EQ(2, enemy.reload());
    EXPECT_EQ(10, enemy.get_current_weapon()->get_ammo_num());
    EXPECT_EQ(1472, enemy.get_weight());
    EXPECT_EQ(4, enemy.get_range());
    EXPECT_EQ(15, enemy.get_num_damage());

    EXPECT_EQ(0, enemy.choice_weapon(pm));
    EXPECT_EQ(pm, enemy.get_current_weapon());
    EXPECT_EQ(2, enemy.get_range());
    EXPECT_EQ(10, enemy.get_num_damage());

    EXPECT_EQ(0, enemy.put_item_from_inventory(ammo_ak, map_));
    EXPECT_EQ(Have_item, map_[std::make_pair(0, 1)]->get_type());
    EXPECT_EQ(2, enemy.get_num_of_items());
    EXPECT_EQ(4450, enemy.get_weight());

    delete have_item;
    delete basicCell;
    delete wall;
}

TEST(Test_level, all_basic_methods) {
    Level level(std::make_pair(1, 1));
    auto pm = new Weapon(PM);
    auto oper = new Operative(std::make_pair(0, 0), pm, "oper");

    EXPECT_EQ(std::make_pair(1, 1), level.get_size());
    EXPECT_EQ(0, level.enemies.size());
    EXPECT_EQ(0, level.operatives.size());
    EXPECT_EQ(0, level.map_.size());

    level.operatives.push_back(oper);
    EXPECT_EQ(1, level.operatives.size());

    level.map_[std::make_pair(0,0)] = new Cell();
    level.map_[std::make_pair(1,0)] = new Cell(Wall);
    EXPECT_EQ(2, level.map_.size());

    EXPECT_EQ(-1, level.change_size(std::make_pair(-1, -1)));
    EXPECT_EQ(std::make_pair(1, 1), level.get_size());
    EXPECT_EQ(0, level.change_size(std::make_pair(5, 5)));
    EXPECT_EQ(std::make_pair(5, 5), level.get_size());

    EXPECT_EQ(OPERATIVE, dynamic_cast<Wild*>(oper)->get_type());
    EXPECT_EQ(0, level.check_flag());
}

TEST(Test_level, method_shoot_step) {
    std::vector<Operative *> operatives = {new Operative(std::make_pair(2, 2), new Weapon(PM, 1), "operative")};
    std::vector<Unit *> enemies = {new Wild("wild", std::make_pair(0, 0)), new Rational("rational", std::make_pair(0, 2))};
    std::vector<Item*> items = {dynamic_cast<Item*>(new Weapon(RPK_74, 10))};
    Level level(std::make_pair(3, 3), operatives, enemies);
    level.map_[std::make_pair(0, 0)] = new Cell(Floor);
    level.map_[std::make_pair(1, 0)] = new Cell(Partition);
    level.map_[std::make_pair(2, 2)] = new Cell(Floor);
    level.map_[std::make_pair(0, 1)] = new Cell(Floor);
    level.map_[std::make_pair(1, 1)] = new Cell(Wall);
    level.map_[std::make_pair(1, 2)] = new Cell(Floor);
    level.map_[std::make_pair(2, 0)] = new Cell(Floor);
    level.map_[std::make_pair(2, 1)] = new Cell(Floor);
    level.map_[std::make_pair(0, 2)] = new Cell(Have_item, items);
    Weapon rpk(RPK_74);
    EXPECT_EQ(0, dynamic_cast<Rational*>(level.enemies[1])->take_weapon(level.map_));

    EXPECT_EQ(100, level.operatives[0]->get_params().current_health);
    EXPECT_EQ(0, level.shoot(dynamic_cast<Wild*>(level.enemies[1]), Down));
    EXPECT_EQ(80, level.operatives[0]->get_params().current_health);

    EXPECT_EQ(0, level.operatives[0]->step(Left, level.map_));
    EXPECT_EQ(0, level.shoot(dynamic_cast<Wild*>(level.operatives[0]), Up));
    EXPECT_EQ(Wall, level.map_[std::make_pair(1, 1)]->get_type());

    EXPECT_EQ(0, level.shoot(dynamic_cast<Wild*>(level.enemies[0]), Down));
    EXPECT_EQ(Floor, level.map_[std::make_pair(1, 0)]->get_type());
    EXPECT_EQ(0, level.enemies[0]->step(Down, level.map_));
    EXPECT_EQ(0, level.operatives[0]->step(Left, level.map_));
    EXPECT_EQ(-1, level.step_by_unit(dynamic_cast<Unit*>(level.enemies[0]), Down));

    EXPECT_EQ(0, level.shoot(dynamic_cast<Wild*>(level.enemies[0]), Down));
    EXPECT_EQ(0, level.shoot(dynamic_cast<Wild*>(level.enemies[0]), Down));
    EXPECT_EQ(0, level.shoot(dynamic_cast<Wild*>(level.enemies[0]), Down));
    EXPECT_EQ(5, level.operatives[0]->get_params().current_health);
    EXPECT_EQ(100, level.shoot(dynamic_cast<Wild*>(level.enemies[0]), Down));

    EXPECT_EQ(2, level.check_flag());
}

TEST(Test_level, config_method) {
    Level level;
    std::string path = "lab4/src/maps/level3.txt";
    level.start(path);

    EXPECT_EQ(std::make_pair(5, 5), level.get_size());

    EXPECT_EQ(Wall, level.map_[std::make_pair(0, 0)]->get_type());
    EXPECT_EQ(Floor, level.map_[std::make_pair(1, 1)]->get_type());
    EXPECT_EQ(Floor, level.map_[std::make_pair(1, 2)]->get_type());
    EXPECT_EQ(Storage_point, level.map_[std::make_pair(1, 3)]->get_type());
    EXPECT_EQ(Partition, level.map_[std::make_pair(2, 1)]->get_type());
    EXPECT_EQ(Wall, level.map_[std::make_pair(2, 2)]->get_type());
    EXPECT_EQ(Floor, level.map_[std::make_pair(2, 3)]->get_type());
    EXPECT_EQ(Floor, level.map_[std::make_pair(3, 1)]->get_type());
    EXPECT_EQ(Floor, level.map_[std::make_pair(3, 2)]->get_type());
    EXPECT_EQ(Floor, level.map_[std::make_pair(3, 3)]->get_type());

    EXPECT_EQ(1, level.operatives.size());
    EXPECT_EQ(2, level.enemies.size());

    EXPECT_EQ(100, level.operatives[0]->get_params().current_health);
    EXPECT_EQ(0, level.shoot(dynamic_cast<Wild*>(level.enemies[1]), Down));
    EXPECT_EQ(75, level.operatives[0]->get_params().current_health);

    EXPECT_EQ(0, level.operatives[0]->step(Left, level.map_));
    EXPECT_EQ(0, level.shoot(dynamic_cast<Wild*>(level.operatives[0]), Up));
    EXPECT_EQ(Wall, level.map_[std::make_pair(2, 2)]->get_type());

    EXPECT_EQ(0, level.shoot(dynamic_cast<Wild*>(level.enemies[0]), Down));
    EXPECT_EQ(Floor, level.map_[std::make_pair(2, 1)]->get_type());
    EXPECT_EQ(0, level.enemies[0]->step(Down, level.map_));
    EXPECT_EQ(0, level.operatives[0]->step(Left, level.map_));

    EXPECT_EQ(0, level.shoot(dynamic_cast<Wild*>(level.enemies[0]), Down));
    EXPECT_EQ(0, level.shoot(dynamic_cast<Wild*>(level.enemies[0]), Down));
    EXPECT_EQ(25, level.operatives[0]->get_params().current_health);
    EXPECT_EQ(100, level.shoot(dynamic_cast<Wild*>(level.enemies[0]), Down));

    EXPECT_EQ(2, level.check_flag());
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


