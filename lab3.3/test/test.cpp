#include "../../Google_tests/googletest-main/googletest/include/gtest/gtest.h"
#include "pcb.hpp"

using namespace PCB_dynamic;

TEST(ContactConstructor, Default) {
    contact c;
    EXPECT_EQ(0, c.p.x);
    EXPECT_EQ(0, c.p.y);
    EXPECT_EQ(0, c.type_contact);
}

TEST(ContactConstructor, Init) {
    contact c(1, 2, (type) 1);
    point p(4, 8);
    EXPECT_EQ(1, c.p.x);
    EXPECT_EQ(2, c.p.y);
    EXPECT_EQ(1, c.type_contact);

    c = contact(p, (type) 1);
    EXPECT_EQ(4, c.p.x);
    EXPECT_EQ(8, c.p.y);
    EXPECT_EQ(1, c.type_contact);
}

TEST(ContactConstructor, TestException) {
    point p;
    EXPECT_THROW(contact(p, (type) 3), std::invalid_argument);
    EXPECT_THROW(contact(-1, 2, (type) -1), std::invalid_argument);
}

TEST(IO, Input) {
    std::istringstream istr_1("1 1\n0\n");
    contact c, c2, c3;
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
    pcb circ1;
    contact c, c1(1, 1, (type) 1);
    EXPECT_EQ(0, circ1.len_());
    circ1.add_contact(c), circ1.add_contact(c1);
    pcb circ2(circ1);
    EXPECT_EQ(2, circ2.len_());
}

    // -------- copy and swap idiom -------- //

TEST(CopyAndSwap, CopyConstructor) {
    pcb pcb1, pcb2;
    pcb1.add_contact(contact (1, 1, input));
    pcb2.add_contact(contact (1, 1, input));

    pcb pcb3(pcb1);

    EXPECT_TRUE(pcb2.len_() == pcb3.len_());
    EXPECT_TRUE(pcb1.len_() == pcb2.len_());
}

TEST(CopyAndSwap, CopyAssignment) {
    pcb pcb1, pcb2, pcb3;
    pcb1.add_contact(contact (1, 1, input));
    pcb2.add_contact(contact (1, 1, input));

    pcb3 = pcb1;

    EXPECT_TRUE(pcb3.len_() == pcb2.len_());
    EXPECT_TRUE(pcb1.len_() == pcb2.len_());
}

TEST(CopyAndSwap, MoveConstructor) {
    pcb pcb1;
    pcb1.add_contact(contact (1, 1, output));
    pcb old_pcb1 = pcb1;

    pcb pcb2(std::move(pcb1));

    EXPECT_TRUE(pcb2.len_() == old_pcb1.len_());
    EXPECT_TRUE(pcb1.len_() == pcb().len_());

}

TEST(CopyAndSwap, MoveAssignment) {
    pcb pcb1;
    pcb1.add_contact(contact (1, 1, output));

    pcb pcb2;
    pcb2.add_contact(contact (2, 2, output));
    pcb2.add_contact(contact (7, 9, input));

    pcb old_pcb1 = pcb1;
    pcb old_pcb2 = pcb2;

    pcb2 = std::move(pcb1);

    EXPECT_TRUE(pcb2.len_() == old_pcb1.len_());
    EXPECT_TRUE(pcb1.len_() == old_pcb2.len_());

}

    // -------- old operations -------- //

TEST(Operations, add_and_print) {
    pcb circ;
    contact c(0, 0, input), c6(0, 0, input), c1(1, 1, (type) 0), c2(2, 3, (type) 1), c3(10, 11, (type) 0);
    contact c4(100, 100, (type) 0);
    std::ostringstream ostr_0, ostr_1, ostr_2, ostr_3;

    circ.print_pcb(ostr_0);
    EXPECT_EQ(0, circ.len_());
    EXPECT_EQ(ostr_0.str(), "Circuit broad is empty\n");

    circ.add_contact(c);
    circ.print_pcb(ostr_1);
    EXPECT_EQ(1, circ.len_());
    EXPECT_EQ(ostr_1.str(), "0 --> input, (0;0), -1;\n");

    EXPECT_THROW(circ.add_contact(c6), std::invalid_argument);

    circ.add_contact(c1);
    circ.print_pcb(ostr_2);
    EXPECT_EQ(2, circ.len_());
    EXPECT_EQ(ostr_2.str(), "0 --> input, (0;0), -1;\n1 --> output, (1;1), -1;\n");

    circ.add_contact(c2), circ.add_contact(c3), circ.add_contact(c4);
}

TEST(Operations, Checkcorrectly) {
    pcb circ;
    contact c(0, 0, input), c1(1, 1, (type) 0);
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
    pcb circ;
    contact c(0, 0, input), c1(1, 1, (type) 0), c2(2, 3, (type) 0), c3(9, 9, (type) 0);
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
    pcb circ;
    contact c(0, 0, input), c1(1, 1, (type) 0), c2(2, 3, (type) 0);
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
    pcb circ;
    contact c, c1(1, 1, (type) 1), c2(2, 3, (type) 1);
    pcb tst;

    EXPECT_THROW(tst = circ.group_cont((type) 0), std::logic_error);

    circ.add_contact(c);
    tst = circ.group_cont((type) 1);
    EXPECT_EQ(0, tst.len_());

    circ.add_contact(c1), circ.add_contact(c2);
    tst = circ.group_cont((type) 0);
    EXPECT_EQ(1, tst.len_());
    tst = circ.group_cont((type) 1);
    EXPECT_EQ(2, tst.len_());

    EXPECT_THROW(tst = circ.group_cont((type) 2), std::invalid_argument);
    EXPECT_THROW(tst = circ.group_cont((type) -1), std::invalid_argument);

}

TEST(Operations, pop) {
    pcb circ;
    contact c, c1(1, 1, (type) 1), c2(2, 3, (type) 1);
    circ.add_contact(c);
    circ.add_contact(c1), circ.add_contact(c2);

    EXPECT_EQ(3, circ.len_());
    circ.pcb_pop();
    EXPECT_EQ(2, circ.len_());
    circ.pcb_pop();
    EXPECT_EQ(1, circ.len_());
    circ.pcb_pop();
    EXPECT_THROW(circ.pcb_pop(), std::invalid_argument);
}

TEST(Operators, element) {
    pcb circ;
    contact c, c1(1, 1, input), c2(2, 3, input), c3(10, 11, input);
    circ.add_contact(c);
    circ.add_contact(c1), circ.add_contact(c2);
    EXPECT_EQ(output, circ[0].type_contact);
    EXPECT_EQ(2, circ[2].p.x);

    EXPECT_THROW(circ[3], std::out_of_range);
    EXPECT_THROW(circ[-1], std::out_of_range);
    circ[2] = c3;

    EXPECT_EQ(10, circ[2].p.x);
}

TEST(Operators, decrement) {
    pcb circ;
    contact c, c1(1, 1, (type) 1), c2(2, 3, (type) 1);
    circ.add_contact(c);
    circ.add_contact(c1), circ.add_contact(c2);

    EXPECT_EQ(3, circ.len_());
    int n0 = (circ--).len_();
    EXPECT_EQ(3, n0);
    EXPECT_EQ(2, circ.len_());
    EXPECT_EQ(1, (--circ).len_());
    circ--;
    EXPECT_THROW(--circ, std::invalid_argument);
}

TEST(Operators, input_output) {
    pcb circ;
    std::ostringstream ostr_0, ostr_1;
    std::istringstream istr_1("3\n1 1 1\n2 3 1\n10 11 0\n");

    ostr_0 << circ;
    EXPECT_EQ(ostr_0.str(), "Circuit broad is empty\n");
    istr_1 >> circ;
    EXPECT_EQ(3, circ.len_());

    ostr_1 << circ;
    EXPECT_EQ(ostr_1.str(), "0 --> input, (1;1), -1;\n1 --> input, (2;3), -1;\n2 --> output, (10;11), -1;\n");

    std::istringstream istr_2("1\n1 1 1\n");
    EXPECT_THROW(istr_2 >> circ, std::invalid_argument);

    std::istringstream istr_3("2\n2 3 1\n1 1 1\n");
    EXPECT_THROW(istr_3 >> circ, std::invalid_argument);
}

TEST(Operators, invert) {
    pcb circ, inv_circ, inv_circ1;
    contact c(0, 0, (type) 1), c1(1, 1, (type) 0), c2(2, 3, (type) 0);
    circ.add_contact(c1);
    circ.add_contact(c), circ.add_contact(c2);
    circ.add_link(1, 2), circ.add_link(2, 0);
    std::ostringstream ostr_before, ostr_after, ostr_before1, ostr_after1;

    ostr_before << circ;
    EXPECT_EQ(ostr_before.str(), "0 --> output, (1;1), -1;\n1 --> input, (0;0), 2;\n2 --> output, (2;3), 0;\n");

    inv_circ = !circ;
    ostr_after << inv_circ;
    EXPECT_EQ(ostr_after.str(), "0 --> input, (1;1), 2;\n1 --> output, (0;0), -1;\n2 --> output, (2;3), 1;\n");

    contact c3(3, 4, (type) 1), c4(4, 5, (type) 0);
    inv_circ.add_contact(c3), inv_circ.add_contact(c4);
    inv_circ.add_link(3, 4);

    ostr_before1 << inv_circ;
    EXPECT_EQ(ostr_before1.str(), "0 --> input, (1;1), 2;\n1 --> output, (0;0), -1;\n2 --> output, (2;3), 1;\n3 --> input, (3;4), 4;\n4 --> output, (4;5), -1;\n");

    inv_circ1 = !inv_circ;
    ostr_after1 << inv_circ1;
    EXPECT_EQ(ostr_after1.str(), "0 --> output, (1;1), -1;\n1 --> input, (0;0), 2;\n2 --> output, (2;3), 0;\n3 --> output, (3;4), -1;\n4 --> input, (4;5), 3;\n");
}

TEST(Operators, modified_sum) {
    pcb circ, circ2;
    contact c(0, 0, input), c1(1, 1, (type) 0), c2(2, 3, (type) 0);
    circ.add_contact(c), circ.add_contact(c1), circ.add_contact(c2);
    circ.add_link(0, 2), circ.add_link(2, 1);
    contact c3(3, 4, (type) 1), c4(4, 5, (type) 0);
    circ2.add_contact(c3), circ2.add_contact(c4);
    circ2.add_link(0, 1);

    EXPECT_EQ(3, circ.len_());
    EXPECT_EQ(2, circ2.len_());
    std::ostringstream ostr_before, ostr_after, ostr_before1;

    ostr_before << circ;
    EXPECT_EQ(ostr_before.str(), "0 --> input, (0;0), 2;\n1 --> output, (1;1), -1;\n2 --> output, (2;3), 1;\n");
    ostr_before1 << circ2;
    EXPECT_EQ(ostr_before1.str(), "0 --> input, (3;4), 1;\n1 --> output, (4;5), -1;\n");
    circ += circ2;
    EXPECT_EQ(5, circ.len_());
    ostr_after << circ;
    EXPECT_EQ(ostr_after.str(), "0 --> input, (0;0), 2;\n1 --> output, (1;1), -1;\n2 --> output, (2;3), 1;\n3 --> input, (3;4), 4;\n4 --> output, (4;5), -1;\n");
}

TEST(Operators, sum) {
    pcb circ, circ2, res;
    contact c(0, 0, input), c1(1, 1, (type) 0), c2(2, 3, (type) 0);
    circ.add_contact(c), circ.add_contact(c1), circ.add_contact(c2);
    circ.add_link(0, 2), circ.add_link(2, 1);
    contact c3(3, 4, (type) 1), c4(4, 5, (type) 0);
    circ2.add_contact(c3), circ2.add_contact(c4);
    circ2.add_link(0, 1);

    EXPECT_EQ(3, circ.len_());
    EXPECT_EQ(2, circ2.len_());
    std::ostringstream ostr_before, ostr_after, ostr_before1;

    ostr_before << circ;
    EXPECT_EQ(ostr_before.str(), "0 --> input, (0;0), 2;\n1 --> output, (1;1), -1;\n2 --> output, (2;3), 1;\n");
    ostr_before1 << circ2;
    EXPECT_EQ(ostr_before1.str(), "0 --> input, (3;4), 1;\n1 --> output, (4;5), -1;\n");
    EXPECT_EQ(0, res.len_());
    res = circ + circ2;
    EXPECT_EQ(5, res.len_());
    ostr_after << res;
    EXPECT_EQ(ostr_after.str(), "0 --> input, (0;0), 2;\n1 --> output, (1;1), -1;\n2 --> output, (2;3), 1;\n3 --> input, (3;4), 4;\n4 --> output, (4;5), -1;\n");
}

TEST(Operators, comparator) {
    pcb circ, circ2;
    contact c, c1(1, 1, (type) 1), c2(2, 3, (type) 1);

    EXPECT_EQ( 0 <=> 0, circ <=> circ2);
    circ.add_contact(c), circ.add_contact(c1), circ.add_contact(c2);
    contact c3(3, 4, (type) 0), c4(4, 5, (type) 1);
    circ2.add_contact(c3), circ2.add_contact(c4);

    EXPECT_EQ(3 <=> 2, circ <=> circ2);
    EXPECT_EQ(3 > 2, circ > circ2);
    EXPECT_EQ(3 <= 2, circ <= circ2);
}

TEST(DynamicMemory, big_pcb) {
    pcb pcb1;
    for (int i = 0; i < 1000; ++i) {
        pcb1.add_contact(contact (i, i, (type) (i % 2)));
    }

    EXPECT_EQ(1000, pcb1.len_());

    for (int i = 0; i < 6; ++i) {
        --pcb1;
    }

    EXPECT_EQ(994, pcb1.len_());
    EXPECT_EQ(1005, pcb1.max_len());
    EXPECT_EQ(995, (--pcb1).max_len());

    for (int i = 0; i < 993; ++i) {
        --pcb1;
    }
    EXPECT_THROW(--pcb1, std::invalid_argument);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}