#include "../../Google_tests/googletest-main/googletest/include/gtest/gtest.h"
#include "circuitboard.hpp"

TEST(ContactConstructor, Default) {
    PCB::contact c;
    EXPECT_EQ(0, c.p.x);
    EXPECT_EQ(0, c.p.y);
    EXPECT_EQ(0, c.type_contact);
}

TEST(ContactConstructor, Init) {
    PCB::contact c(1, 2, (PCB::type) 1);
    PCB::point p(4, 8);
    EXPECT_EQ(1, c.p.x);
    EXPECT_EQ(2, c.p.y);
    EXPECT_EQ(1, c.type_contact);

    c = PCB::contact(p, (PCB::type) 1);
    EXPECT_EQ(4, c.p.x);
    EXPECT_EQ(8, c.p.y);
    EXPECT_EQ(1, c.type_contact);
}

TEST(ContactConstructor, TestException) {
    PCB::point p;
    EXPECT_THROW(PCB::contact(p, (PCB::type) 3), std::invalid_argument);
    EXPECT_THROW(PCB::contact(-1, 2, (PCB::type) -1), std::invalid_argument);
}

TEST(IO, Input) {
    std::istringstream istr_1("1 1\n0\n");
    PCB::contact c, c2, c3;
    c.input_contact(istr_1);
    EXPECT_EQ(1, c.p.x);
    EXPECT_EQ(1, c.p.y);
    EXPECT_EQ(0, c.type_contact);

    std::istringstream istr_2("1 1\n4\n");
    EXPECT_ANY_THROW(c2.input_contact(istr_2));

    std::istringstream istr_3("1 a\n0\n");
    EXPECT_ANY_THROW(c3.input_contact(istr_3));
}

TEST(PCBConstructos, Init) {
    PCB::pcb circ;
    EXPECT_EQ(0, circ.getSize());
}

TEST(Operations, add_and_print) {
    PCB::pcb circ;
    PCB::contact c, c5, c1(1, 1, (PCB::type) 1), c2(2, 3, (PCB::type) 0), c3(10, 11, (PCB::type) 1);
    std::ostringstream ostr_0, ostr_1, ostr_2, ostr_3;

    circ.print_pcb(ostr_0);
    EXPECT_EQ(0, circ.getSize());
    EXPECT_EQ(ostr_0.str(), "Circuit broad is empty\n");

    circ.add_contact(c);
    circ.print_pcb(ostr_1);
    EXPECT_EQ(1, circ.getSize());
    EXPECT_EQ(ostr_1.str(), "0 --> input, (0;0), -1;\n");

    EXPECT_THROW(circ.add_contact(c5), std::invalid_argument);

    circ.add_contact(c1);
    circ.print_pcb(ostr_2);
    EXPECT_EQ(2, circ.getSize());
    EXPECT_EQ(ostr_2.str(), "0 --> input, (0;0), -1;\n1 --> output, (1;1), -1;\n");

    circ.add_contact(c2);
    EXPECT_THROW(circ.add_contact(c3), std::out_of_range);
}

TEST(Operations, Checkcorrectly) {
    PCB::pcb circ;
    PCB::contact c, c1(1, 1, (PCB::type) 1);
    int t;
    EXPECT_THROW(t = circ.check_correctly(1), std::logic_error);

    circ.add_contact(c);
    circ.add_contact(c1);
    EXPECT_EQ(0, circ.check_correctly(0));
    EXPECT_EQ(0, circ.check_correctly(1));
    EXPECT_THROW(t = circ.check_correctly(3), std::invalid_argument);

    circ.add_link(0, 1);
    EXPECT_EQ(1, circ.check_correctly(1));
    EXPECT_EQ(0, circ.check_correctly(0));
}

TEST(Operations, add_link) {
    PCB::pcb circ;
    PCB::contact c, c1(1, 1, (PCB::type) 1), c2(2, 3, (PCB::type) 1);
    circ.add_contact(c);
    circ.add_contact(c1);

    circ.add_link(0, 1);
    EXPECT_EQ(1, circ.check_correctly(1));

    EXPECT_THROW(circ.add_link(2, 0), std::invalid_argument);
    EXPECT_THROW(circ.add_link(0, -1), std::invalid_argument);
    EXPECT_THROW(circ.add_link(1, 0), std::logic_error);
    EXPECT_THROW(circ.add_link(0, 1), std::logic_error);

    circ.add_contact(c2);
    EXPECT_THROW(circ.add_link(2, 1), std::logic_error);

    circ.add_link(1, 2);
    EXPECT_EQ(1, circ.check_correctly(2));
}

TEST(Operations, contact_distance) {
    PCB::pcb circ;
    PCB::contact c, c1(1, 1, (PCB::type) 1), c2(2, 3, (PCB::type) 1);
    circ.add_contact(c), circ.add_contact(c1), circ.add_contact(c2);
    circ.add_link(0, 2), circ.add_link(2, 1);
    int t;

    EXPECT_THROW(t = circ.contact_dist(-1, 2), std::invalid_argument);
    EXPECT_THROW(t = circ.contact_dist(0, 5), std::invalid_argument);
    EXPECT_THROW(t = circ.contact_dist(1, 0), std::logic_error);

    EXPECT_EQ(1, circ.contact_dist(0, 2));
    EXPECT_EQ(2, circ.contact_dist(0, 1));
    EXPECT_EQ(0, circ.contact_dist(1, 2));
}

TEST(Operations, group_contacts) {
    PCB::pcb circ;
    PCB::contact c, c1(1, 1, (PCB::type) 1), c2(2, 3, (PCB::type) 1);
    PCB::pcb tst;

    EXPECT_THROW(tst = circ.group_cont((PCB::type) 0), std::logic_error);

    circ.add_contact(c);
    tst = circ.group_cont((PCB::type) 1);
    EXPECT_EQ(0, tst.getSize());

    circ.add_contact(c1), circ.add_contact(c2);
    tst = circ.group_cont((PCB::type) 0);
    EXPECT_EQ(1, tst.getSize());
    tst = circ.group_cont((PCB::type) 1);
    EXPECT_EQ(2, tst.getSize());

    EXPECT_THROW(tst = circ.group_cont((PCB::type) 2), std::invalid_argument);
    EXPECT_THROW(tst = circ.group_cont((PCB::type) -1), std::invalid_argument);

}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}