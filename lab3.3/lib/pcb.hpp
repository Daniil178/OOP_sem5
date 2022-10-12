#ifndef PCB_HPP
#define PCB_HPP

#include <iostream>
#define Quantium 5

namespace PCB {
struct point {
    double x, y;
    point() :x(0), y(0) {}
    explicit point(double x0, double y0) :x(x0), y(y0){}
};

enum type {
    output,
    input
};

struct contact {
    type type_contact; // 0 - output, 1 - input
    point p;
    int connection_to;
    contact();
    explicit contact(const point &p0, type t0 = output);
    contact(double x0, double y0, type t0);
    std::istream& input_contact(std::istream &in);
};

class pcb {
private:
    contact *plat; //massive of contacts
    int n; //number of busy blocks
};

}//PCB
#endif