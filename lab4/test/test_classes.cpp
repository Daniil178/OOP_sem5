#include "../../Google_tests/googletest-main/googletest/include/gtest/gtest.h"

#include "Game.h"

using namespace RPG;

TEST(Test_item, all_methods) {
    Item item("lala", 200, WEAPON);
    Item* med = new Medicine_Kit(Basic);

    EXPECT_EQ(200, item.get_weight());
    EXPECT_EQ(WEAPON, item.get_type());

    EXPECT_EQ(MEDICINE_KIT, med->get_type());
    EXPECT_EQ(200, med->get_weight());

    auto med1 = dynamic_cast<Medicine_Kit*>(med);
    EXPECT_EQ(std::make_pair(20, 1), med1->use());
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
    EXPECT_EQ(100, pist.get_weight());
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
    Cell noth;
    Item *med = new Medicine_Kit(Army);

    EXPECT_EQ(Floor, noth.get_type());
    EXPECT_EQ(true, noth.is_visible());
    EXPECT_EQ(true, noth.can_go_through());
    EXPECT_EQ(1, noth.get_damage(5));
    EXPECT_EQ(nullptr, noth.take_item(med));
    EXPECT_EQ(0, noth.put_item(med));
    EXPECT_EQ(Have_item, noth.get_type());
    EXPECT_EQ(med, noth.take_item(med));
    EXPECT_EQ(Floor, noth.get_type());
}


TEST(Test_cell, wall_all_methods) {
    std::vector<Item *> items1;
    Cell wall_(Wall, items1);
    Item *med = new Medicine_Kit(Army);

    EXPECT_EQ(Wall, wall_.get_type());
    EXPECT_EQ(false, wall_.is_visible());
    EXPECT_EQ(false, wall_.can_go_through());
    EXPECT_EQ(-1, wall_.get_damage(5));
    EXPECT_EQ(nullptr, wall_.take_item(med));
    EXPECT_EQ(-1, wall_.put_item(med));
}

TEST(Test_cell, partition_all_methods) {
    std::vector<Item*> items1;
    Cell part(Partition, items1);
    Item* med = new Medicine_Kit(Army);

    EXPECT_EQ(Partition, part.get_type());
    EXPECT_EQ(false, part.is_visible());
    EXPECT_EQ(false, part.can_go_through());
    EXPECT_EQ(-1, part.put_item(med));

    EXPECT_EQ(0, part.get_damage(5));
    EXPECT_EQ(Floor, part.get_type());
}

TEST(Test_unit, all_methods) {
    Unit wild("wild", WILD, std::make_pair(0, 0));
    std::vector<Item*> items1;
    Cell wall(Wall, items1), defaul;
    Map map_ = {{std::make_pair(0, 0), defaul}, {std::make_pair(0, 1), defaul}, {std::make_pair(1, 0), wall}};
    EXPECT_EQ(WILD, wild.get_type());
    EXPECT_EQ(std::make_pair(0, 0), wild.get_position());
    EXPECT_EQ(100, wild.get_params().current_health);
    EXPECT_EQ(1, wild.get_params().time_to_step);
    EXPECT_EQ(10, wild.get_params().max_time);
    EXPECT_EQ(3, wild.get_params().view_radius);
    EXPECT_EQ(100, wild.get_params().max_health);
    EXPECT_EQ(10, wild.get_params().current_time);

    EXPECT_EQ(1, wild.get_damage(50));
    EXPECT_EQ(50, wild.get_params().current_health);
    EXPECT_EQ(0, wild.get_damage(50));
    EXPECT_EQ(0, wild.get_params().current_health);

    EXPECT_EQ(-1, wild.step(Right, map_));
    EXPECT_EQ(0, wild.step(Down, map_));
    EXPECT_EQ(std::make_pair(0, 1), wild.get_position());
}

TEST(Test_wild, all_methods) {
    Wild wild("wild", std::make_pair(0, 0));
    std::vector<Item*> items1;
    Cell wall(Wall, items1), defaul;
    Map map_ = {{std::make_pair(0, 0), defaul}, {std::make_pair(0, 1), defaul}, {std::make_pair(1, 0), wall}};

    EXPECT_EQ(WILD, wild.get_type());
    EXPECT_EQ(25, wild.get_num_damage());
    EXPECT_EQ(1, wild.get_range());
    EXPECT_EQ(90, wild.get_accuracy());

    EXPECT_EQ(10, wild.get_params().max_time);
    wild.attack();
    EXPECT_EQ(9, wild.get_params().current_time);

    EXPECT_EQ(-1, wild.step(Right, map_));
    EXPECT_EQ(0, wild.step(Down, map_));
    EXPECT_EQ(std::make_pair(0, 1), wild.get_position());
}

TEST(Test_rational, all_methods) {
    Rational rat("rational", std::make_pair(0, 0));
    auto pm = new Weapon(PM, 5), pm1 = new Weapon(PM, 0);
    std::vector<Item*> items1, items2 = {dynamic_cast<Item*>(pm), dynamic_cast<Item*>(pm1)};
    Cell wall(Wall, items1), have_item(Have_item, items2), defaul;
    Map map_ = {{std::make_pair(0, 0), have_item}, {std::make_pair(0, 1), defaul}, {std::make_pair(1, 0), wall}};

    EXPECT_EQ(RATIONAL, rat.get_type());
    EXPECT_EQ(0, rat.get_num_damage());
    EXPECT_EQ(0, rat.get_range());
    EXPECT_EQ(90, rat.get_accuracy());

    EXPECT_EQ(nullptr, rat.get_current_weapon());
    EXPECT_EQ(-1, rat.attack());

    EXPECT_EQ(0, rat.take_item(pm, map_));
    EXPECT_EQ(pm, rat.get_current_weapon());
    EXPECT_EQ(0, rat.attack());
    EXPECT_EQ(9, rat.get_params().current_time);
    EXPECT_EQ(4, rat.get_current_weapon()->get_ammo_num());
    EXPECT_EQ(0, rat.put_item(rat.get_current_weapon(), map_));

    EXPECT_EQ(nullptr, rat.get_current_weapon());
    EXPECT_EQ(0, rat.take_item(pm1, map_));
    EXPECT_EQ(-2, rat.attack());
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


