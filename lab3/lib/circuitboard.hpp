#ifndef CIRCUITBOARD_HPP
#define CIRCUITBOARD_HPP

#include <iostream>
#define N 3

namespace PCB{
    struct point{
        double x, y;
        point(double x0 = 0, double y0 = 0) :x(x0), y(y0){}
    };
    enum type{
        input,
        output
    };
    struct contact{
        type type_contact;
        point p;
        int link_contact;
    public:
        contact();
        explicit contact(const point &p0, type t0 = input);
        contact(double x0, double y0, type t0);
        std::istream& input_contact(std::istream &in);

    };
    class pcb{
    private:
        contact plat[N]; //massive of contacts
        int n; //number of busy blocks
    public:
        pcb();
        void add_contact(contact c);
        //getters
        [[nodiscard]] int getSize() const noexcept;
        //tasks
        std::ostream& print_pcb(std::ostream &out) const noexcept;
        [[nodiscard]] int check_correctly(int num) const;
        void add_link(int from, int to);
        [[nodiscard]] pcb group_cont(type filter) const;
        [[nodiscard]] int contact_dist(int from, int to) const;
    };
}

#endif