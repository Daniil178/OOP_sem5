#include "../../Google_tests/googletest-main/googletest/include/gtest/gtest.h"
#include "deltoid.hpp"

// Тестирование конструкторов
TEST(DeltoidConstructor, DefaultConstructor){
    Prog2::Deltoid a1;
    ASSERT_EQ(0, a1.getP().x);
    ASSERT_EQ(0, a1.getP().y);
    ASSERT_EQ(1, a1.getR());
}

TEST(DeltoidConstructor, InitConstructors){
    Prog2::Deltoid a2(3);
    Prog2::point p(2, 3);
    ASSERT_EQ(3, a2.getR());
    ASSERT_EQ(0, a2.getP().x);
    ASSERT_EQ(0, a2.getP().y);

    Prog2::Deltoid a3(p, 8);
    ASSERT_EQ(2, a3.getP().x);
    ASSERT_EQ(3, a3.getP().y);
    ASSERT_EQ(8, a3.getR());

    Prog2::Deltoid a4(-4, -5, 3);
    ASSERT_EQ(-4, a4.getP().x);
    ASSERT_EQ(-5, a4.getP().y);
    ASSERT_EQ(3, a4.getR());
}

TEST(DeltoidConstructor, TestException){
    Prog2::point p;
    ASSERT_ANY_THROW(Prog2::Deltoid(2, 5, -5));
    ASSERT_ANY_THROW(Prog2::Deltoid(p, -1));
    }
    // Тестирование других методов
    TEST(DeltoidMethods, Setters){
    Prog2::Deltoid a;
    Prog2::point p1(3, 2);
    a.setP(p1);
    ASSERT_EQ(3, a.getP().x);
    ASSERT_EQ(2, a.getP().y);

    Prog2::point p2(-3, -2);
    a.setP(p2);
    ASSERT_EQ(-3, a.getP().x);
    ASSERT_EQ(-2, a.getP().y);

    a.setR(2);
    ASSERT_EQ(2, a.getR());
    ASSERT_ANY_THROW(a.setR(-1));
}

TEST(DeltoidMethods, Parameters){
    Prog2::Deltoid a1;
    const double err = 0.00001;

    ASSERT_NEAR(2 * M_PI, a1.area(), err);
    ASSERT_NEAR(16, a1.perimeter(), err);
    ASSERT_EQ(4, a1.area_with_tangent());

    ASSERT_EQ(3, a1.f(0).x);
    ASSERT_EQ(0, a1.f(0).y);

    ASSERT_NEAR(-1, a1.f(M_PI).x, err);
    ASSERT_NEAR(0, a1.f(M_PI).y, err);

    //ASSERT_STREQ("(x^2 + y^2)^2 + 18*(x^2 + y^2) = 8x^3 - 24y^2 * x + 27", a1.formula());

    Prog2::Deltoid a2(1, 3, 2);
    ASSERT_NEAR(2 * M_PI * 4, a2.area(), err);
    ASSERT_EQ(16 * 2, a2.perimeter());
    ASSERT_EQ(4 * 2, a2.area_with_tangent());

    ASSERT_NEAR(2.32892, a2.f(1).x, err);
    ASSERT_NEAR(4.54729, a2.f(1).y, err);

    ASSERT_EQ(7, a2.f(0).x);
    ASSERT_EQ(3, a2.f(0).y);

    //ASSERT_STREQ("((x - 1.00)^2 + (y - 3.00)^2)^2 + 18*((x - 1.00)^2 + (y - 3.00)^2) = 8(x - 1.00)^3 - 24(y - 3.00)^2 * (x - 1.00) + 27", a2.formula());
}

TEST(DeltoidMethods, ConstData){
    const Prog2::Deltoid d(2, 3, 100);
    const double err = 0.00001;

    ASSERT_EQ(2, d.getP().x);
    ASSERT_EQ(3, d.getP().y);
    ASSERT_EQ(100, d.getR());

    ASSERT_NEAR(M_PI * 20000, d.area(), err);
    ASSERT_EQ(1600, d.perimeter());
    ASSERT_EQ(400, d.area_with_tangent());

    ASSERT_NEAR(281.22509, d.f(50).x, err);
    ASSERT_NEAR(1.161593, d.f(50).y, err);

    ASSERT_EQ(302, d.f(0).x);
    ASSERT_EQ(3, d.f(0).y);
}

int main(int argc, char* argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}