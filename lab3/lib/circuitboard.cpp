#include "circuitboard.hpp"

namespace PCB{
    contact::contact(type t0) :p(0, 0){
        if (t0 !=0 and t0 != 1)
            throw std::invalid_argument("invalid type of contact");
        type_contact = t0;
        link_contact = -1;
    }
    contact::contact(const point &p0, type t0) :p(p0) {
        if (t0 !=0 and t0 != 1)
            throw std::invalid_argument("invalid type of contact");
        type_contact = (type) t0;
        link_contact = -1;
    }
    contact::contact(double x0, double y0, type t0) :p(x0, y0) {
        if (t0 !=0 and t0 != 1)
            throw std::invalid_argument("invalid type of contact");
        type_contact = (type) t0;
        link_contact = -1;
    }
    std::istream& contact::input_contact(std::istream &in) {
        in.exceptions(std::istream::failbit | std::istream::badbit | std::istream::eofbit);
        int t;
        in >> p.x >> p.y;
        in >> t;
        if (t != 0 and t != 1) {
            in.setstate(std::ios::failbit);
        }
        type_contact = (type) t;
        return in;
    }
    pcb::pcb(int n0) :n(n0) {}
    void pcb::add_contact(contact &c) {
        if (n < N) {
            plat[n] = c;
            n += 1;
        }
        else
            throw std::out_of_range("Error, circuit board is busy");
    }
    int pcb::getSize() const noexcept {
        return n;
    }
    std::ostream& pcb::print_pcb(std::ostream& out) const noexcept{
        if (n == 0)
            out << "Circuit broad is empty" << std::endl;
        else {
            for (int i = 0; i < n; ++i) {
                out << i << " --> ";
                if (plat[i].type_contact)
                    out << "output, ";
                else
                    out << "input, ";
                out << "(" << plat[i].p.x << ";" << plat[i].p.y << "), ";
                out << plat[i].link_contact << ";" << std::endl;
            }
        }
        return out;
    }
    int pcb::check_correctly(int num) const { // 0 - has 0 input link; 1 - has 1 input link
        int res = 0;
        if (n == 0)
            throw std::logic_error("Error, this board is empty");
        if (num >= n)
            throw std::invalid_argument("Error, this contact dont`t exist");
        for (int i = 0; i < n; ++i) {
            if (i != num and plat[i].link_contact == num)
                ++res;
        }
        if (res > 1)
            throw std::logic_error("Error, this contact has > 1 input link");
        return res;
    }
    void pcb::add_link(int from, int to) {
        if ((n <= to or n <= from) or (to < 0 or from < 0))
            throw std::invalid_argument("Error, contacts don`t exist");
        else if (plat[from].link_contact != -1)
            throw std::logic_error("Error, contact 1 is already connected");
        else if (plat[to].type_contact == input)
            throw std::logic_error("Error, contact 2 has input type");
        else if (pcb::check_correctly(to) != 0)
            throw std::logic_error("Error, contact 2 has input connection");
        else {
            plat[from].link_contact = to;
        }
    }
    int pcb::contact_dist(int from, int to) const {
        if ((n <= to or n <= from) or (to < 0 or from < 0))
            throw std::invalid_argument("Error, contacts don`t exist");
        else if (plat[to].type_contact == input)
            throw std::logic_error("Error, contact 2 has input type");
        int dist = 0, i = from;
        while (plat[i].link_contact != -1 or plat[i].link_contact != to) {
            i = plat[i].link_contact;
            ++ dist;
        }
        if (plat[i].link_contact != -1)
            return 0;
        else {
            return dist;
        }
    }
    const contact* pcb::group_cont(type filter) const {
        contact *res = nullptr;
        int num = 0;
        if (n == 0)
            throw std::logic_error("Error, this circuit board is empty");
        else {
            for (int i = 0; i < n; ++ i)
                num += (plat[i].type_contact == filter);
            if (num != 0) {
                res = new contact[num];
                num = 0;
                for (int i = 0; i < n; ++i)
                    if (plat[i].type_contact == filter) {
                        res[num] = plat[i];
                        ++num;
                    }
            }
        }
        return res;
    }
}