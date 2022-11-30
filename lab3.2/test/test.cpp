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
    PCB::pcb circ1;
    PCB::contact c, c1(1, 1, (PCB::type) 1);
    EXPECT_EQ(0, circ1.getSize());
    circ1.add_contact(c), circ1.add_contact(c1);
    PCB::pcb circ2(circ1);
    EXPECT_EQ(2, circ2.getSize());
}

TEST(Operations, add_and_print) {
    PCB::pcb circ;
    PCB::contact c, c6, c1(1, 1, (PCB::type) 1), c2(2, 3, (PCB::type) 0), c3(10, 11, (PCB::type) 1);
    PCB::contact c4(100, 100, (PCB::type) 1), c5(-1, -1, (PCB::type) 0);
    std::ostringstream ostr_0, ostr_1, ostr_2, ostr_3;

    circ.print_pcb(ostr_0);
    EXPECT_EQ(0, circ.getSize());
    EXPECT_EQ(ostr_0.str(), "Circuit broad is empty\n");

    circ.add_contact(c);
    circ.print_pcb(ostr_1);
    EXPECT_EQ(1, circ.getSize());
    EXPECT_EQ(ostr_1.str(), "0 --> input, (0;0), -1;\n");

    EXPECT_THROW(circ.add_contact(c6), std::invalid_argument);

    circ.add_contact(c1);
    circ.print_pcb(ostr_2);
    EXPECT_EQ(2, circ.getSize());
    EXPECT_EQ(ostr_2.str(), "0 --> input, (0;0), -1;\n1 --> output, (1;1), -1;\n");

    circ.add_contact(c2), circ.add_contact(c3), circ.add_contact(c4);
    EXPECT_THROW(circ.add_contact(c5), std::out_of_range);
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
    PCB::contact c, c1(1, 1, (PCB::type) 1), c2(2, 3, (PCB::type) 1), c3(9, 9, (PCB::type) 1);
    circ.add_contact(c);
    circ.add_contact(c1);

    circ.add_link(0, 1);
    EXPECT_EQ(1, circ.check_correctly(1));

    EXPECT_THROW(circ.add_link(2, 0), std::invalid_argument);
    EXPECT_THROW(circ.add_link(0, -1), std::invalid_argument);
    EXPECT_THROW(circ.add_link(1, 0), std::logic_error);
    EXPECT_THROW(circ.add_link(0, 1), std::logic_error);

    circ.add_contact(c2);
    circ.add_contact(c3);
    EXPECT_THROW(circ.add_link(2, 3), std::logic_error);
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

TEST(Operations, pop) {
    PCB::pcb circ;
    PCB::contact c, c1(1, 1, (PCB::type) 1), c2(2, 3, (PCB::type) 1);
    circ.add_contact(c);
    circ.add_contact(c1), circ.add_contact(c2);

    EXPECT_EQ(3, circ.getSize());
    circ.pcb_pop();
    EXPECT_EQ(2, circ.getSize());
    circ.pcb_pop();
    EXPECT_EQ(1, circ.getSize());
    circ.pcb_pop();
    EXPECT_THROW(circ.pcb_pop(), std::invalid_argument);
}

TEST(Operators, element) {
    PCB::pcb circ;
    PCB::contact c, c1(1, 1, (PCB::type) 1), c2(2, 3, (PCB::type) 1), c3(10, 11, (PCB::type) 1);
    circ.add_contact(c);
    circ.add_contact(c1), circ.add_contact(c2);
    EXPECT_EQ(0, circ[0].type_contact);
    EXPECT_EQ(2, circ[2].p.x);

    EXPECT_THROW(circ[3], std::out_of_range);
    EXPECT_THROW(circ[-1], std::out_of_range);
    circ[2] = c3;

    EXPECT_EQ(10, circ[2].p.x);
}

TEST(Operators, decrement) {
    PCB::pcb circ;
    PCB::contact c, c1(1, 1, (PCB::type) 1), c2(2, 3, (PCB::type) 1);
    circ.add_contact(c);
    circ.add_contact(c1), circ.add_contact(c2);

    EXPECT_EQ(3, circ.getSize());
    int n0 = (circ--).getSize();
    EXPECT_EQ(3, n0);
    EXPECT_EQ(2, circ.getSize());
    EXPECT_EQ(1, (--circ).getSize());
    circ--;
    EXPECT_THROW(--circ, std::invalid_argument);
}

TEST(Operators, input_output) {
    PCB::pcb circ;
    std::ostringstream ostr_0, ostr_1;
    std::istringstream istr_1("3\n1 1 0\n2 3 0\n10 11 1\n");

    ostr_0 << circ;
    EXPECT_EQ(ostr_0.str(), "Circuit broad is empty\n");
    istr_1 >> circ;
    EXPECT_EQ(3, circ.getSize());

    ostr_1 << circ;
    EXPECT_EQ(ostr_1.str(), "0 --> input, (1;1), -1;\n1 --> input, (2;3), -1;\n2 --> output, (10;11), -1;\n");

    std::istringstream istr_2("1\n1 1 0\n");
    EXPECT_THROW(istr_2 >> circ, std::invalid_argument);

    std::istringstream istr_3("2\n1 1 0\n2 3 0\n");
    EXPECT_THROW(istr_3 >> circ, std::invalid_argument);
}

TEST(Operators, invert) {
    PCB::pcb circ;
    PCB::contact c, c1(1, 1, (PCB::type) 1), c2(2, 3, (PCB::type) 1);
    circ.add_contact(c1);
    circ.add_contact(c), circ.add_contact(c2);
    circ.add_link(1, 2), circ.add_link(2, 0);
    std::ostringstream ostr_before, ostr_after, ostr_before1, ostr_after1;

    ostr_before << circ;
    EXPECT_EQ(ostr_before.str(), "0 --> output, (1;1), -1;\n1 --> input, (0;0), 2;\n2 --> output, (2;3), 0;\n");

    circ = !circ;
    ostr_after << circ;
    EXPECT_EQ(ostr_after.str(), "0 --> input, (1;1), 2;\n1 --> output, (0;0), -1;\n2 --> output, (2;3), 1;\n");

    PCB::contact c3(3, 4, (PCB::type) 0), c4(4, 5, (PCB::type) 1);
    circ.add_contact(c3), circ.add_contact(c4);
    circ.add_link(3, 4);

    ostr_before1 << circ;
    EXPECT_EQ(ostr_before1.str(), "0 --> input, (1;1), 2;\n1 --> output, (0;0), -1;\n2 --> output, (2;3), 1;\n3 --> input, (3;4), 4;\n4 --> output, (4;5), -1;\n");

    circ = !circ;
    ostr_after1 << circ;
    EXPECT_EQ(ostr_after1.str(), "0 --> output, (1;1), -1;\n1 --> input, (0;0), 2;\n2 --> output, (2;3), 0;\n3 --> output, (3;4), -1;\n4 --> input, (4;5), 3;\n");
}

TEST(Operators, modified_sum) {
    PCB::pcb circ, circ2;
    PCB::contact c, c1(1, 1, (PCB::type) 1), c2(2, 3, (PCB::type) 1);
    circ.add_contact(c), circ.add_contact(c1), circ.add_contact(c2);
    circ.add_link(0, 2), circ.add_link(2, 1);
    PCB::contact c3(3, 4, (PCB::type) 0), c4(4, 5, (PCB::type) 1);
    circ2.add_contact(c3), circ2.add_contact(c4);
    circ2.add_link(0, 1);

    EXPECT_EQ(3, circ.getSize());
    EXPECT_EQ(2, circ2.getSize());
    std::ostringstream ostr_before, ostr_after, ostr_before1;

    ostr_before << circ;
    EXPECT_EQ(ostr_before.str(), "0 --> input, (0;0), 2;\n1 --> output, (1;1), -1;\n2 --> output, (2;3), 1;\n");
    ostr_before1 << circ2;
    EXPECT_EQ(ostr_before1.str(), "0 --> input, (3;4), 1;\n1 --> output, (4;5), -1;\n");
    circ += circ2;
    EXPECT_EQ(5, circ.getSize());
    ostr_after << circ;
    EXPECT_EQ(ostr_after.str(), "0 --> input, (0;0), 2;\n1 --> output, (1;1), -1;\n2 --> output, (2;3), 1;\n3 --> input, (3;4), 4;\n4 --> output, (4;5), -1;\n");

    EXPECT_THROW(circ += circ2, std::out_of_range);
}

TEST(Operators, sum) {
    PCB::pcb circ, circ2, res;
    PCB::contact c, c1(1, 1, (PCB::type) 1), c2(2, 3, (PCB::type) 1);
    circ.add_contact(c), circ.add_contact(c1), circ.add_contact(c2);
    circ.add_link(0, 2), circ.add_link(2, 1);
    PCB::contact c3(3, 4, (PCB::type) 0), c4(4, 5, (PCB::type) 1);
    circ2.add_contact(c3), circ2.add_contact(c4);
    circ2.add_link(0, 1);

    EXPECT_EQ(3, circ.getSize());
    EXPECT_EQ(2, circ2.getSize());
    std::ostringstream ostr_before, ostr_after, ostr_before1;

    ostr_before << circ;
    EXPECT_EQ(ostr_before.str(), "0 --> input, (0;0), 2;\n1 --> output, (1;1), -1;\n2 --> output, (2;3), 1;\n");
    ostr_before1 << circ2;
    EXPECT_EQ(ostr_before1.str(), "0 --> input, (3;4), 1;\n1 --> output, (4;5), -1;\n");
    EXPECT_EQ(0, res.getSize());
    res = circ + circ2;
    EXPECT_EQ(5, res.getSize());
    ostr_after << res;
    EXPECT_EQ(ostr_after.str(), "0 --> input, (0;0), 2;\n1 --> output, (1;1), -1;\n2 --> output, (2;3), 1;\n3 --> input, (3;4), 4;\n4 --> output, (4;5), -1;\n");

    EXPECT_THROW(res = res + circ2, std::out_of_range);
}

//TEST(Operators, comparator) {
//    PCB::pcb circ, circ2;
//    PCB::contact c, c1(1, 1, (PCB::type) 1), c2(2, 3, (PCB::type) 1);
//
//    EXPECT_EQ( 0 <=> 0, circ <=> circ2);
//    circ.add_contact(c), circ.add_contact(c1), circ.add_contact(c2);
//    PCB::contact c3(3, 4, (PCB::type) 0), c4(4, 5, (PCB::type) 1);
//    circ2.add_contact(c3), circ2.add_contact(c4);
//
//    EXPECT_EQ(3 <=> 2, circ <=> circ2);
//    EXPECT_EQ(3 > 2, circ > circ2);
//    EXPECT_EQ(3 <= 2, circ <= circ2);
//}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}