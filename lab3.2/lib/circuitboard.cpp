#include "circuitboard.hpp"

namespace PCB{
    contact::contact() :p(0, 0){
        type_contact = input;
        link_contact = -1;
}
    contact::contact(const point &p0, type t0) :p(p0) {
        if (t0 !=0 and t0 != 1) {
            throw std::invalid_argument("invalid type of contact");
        }
        type_contact = (type) t0;
        link_contact = -1;
    }
    contact::contact(double x0, double y0, type t0) :p(x0, y0) {
        if (t0 !=0 and t0 != 1) {
            throw std::invalid_argument("invalid type of contact");
        }
        type_contact = (type) t0;
        link_contact = -1;
    }
    //input contact
    std::istream& contact::input_contact(std::istream &in) {
        int t;
        point p0;
        in >> p0.x >> p0.y >> t;
        if (!in.good()) {
            throw std::invalid_argument("invalid point");
        }
        if (t != 0 and t != 1) {
            throw std::invalid_argument("invalid type of contact");
        }
        p.x = p0.x, p.y = p0.y;
        type_contact = (type) t;
        return in;
    }
    //Init pcb
    pcb::pcb() :n(0) {}
    pcb::pcb(const pcb &circ) {
        n = circ.n;
        for(int i = 0; i < n; ++i) {
            plat[i] = circ.plat[i];
        }
    }
    //Tasks
    void pcb::add_contact(contact c) {
        if (n < N) {
            for(int i = 0; i < n; ++i) {
                if (plat[i].p.x == c.p.x and plat[i].p.y == c.p.y) {
                    throw std::invalid_argument("Place with similar coordinates is busy");
                }
            }
            plat[n] = c;
            n += 1;
        }
        else {
            throw std::out_of_range("Error, circuit board is busy");
        }
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
                if (plat[i].type_contact) {
                    out << "output, ";
                }
                else {
                    out << "input, ";
                }
                out << "(" << plat[i].p.x << ";" << plat[i].p.y << "), ";
                out << plat[i].link_contact << ";" << std::endl;
            }
        }
        return out;
    }

    int pcb::check_correctly(int num) const { // 0 - has 0 input link; 1 - has 1 input link
        int res = 0;
        if (n == 0) {
            throw std::logic_error("Error, this board is empty");
        }
        if (num >= n or num < 0) {
            throw std::invalid_argument("Error, this contact dont`t exist");
        }
        for (int i = 0; i < n; ++i) {
            if (i != num and plat[i].link_contact == num) {
                ++res;
            }
        }
        if (res > 1) {
            throw std::logic_error("Error, this contact has > 1 input link");
        }
        return res;
    }

    void pcb::add_link(int from, int to) {
        if ((n <= to or n <= from) or (to < 0 or from < 0)) {
            throw std::invalid_argument("Error, contacts don`t exist");
        }
        if (plat[from].link_contact != -1) {
            throw std::logic_error("Error, contact 1 is already connected");
        }
        if (plat[to].type_contact == input) {
            throw std::logic_error("Error, contact 2 has input type");
        }
        if (pcb::check_correctly(to) != 0) {
            throw std::logic_error("Error, contact 2 has input connection");
        }
        if (pcb::check_correctly(from) == 0 and plat[from].type_contact == output) {
            throw std::logic_error("Error, contact 1 has output type and does not have input connection");
        }
        plat[from].link_contact = to;
    }

    int pcb::contact_dist(int from, int to) const {
        if ((n <= to or n <= from) or (to < 0 or from < 0)) {
            throw std::invalid_argument("Error, contacts don`t exist");
        }
        if (plat[to].type_contact == input) {
            throw std::logic_error("Error, contact 2 has input type");
        }
        int dist = 0, i = from;
        while (plat[i].link_contact != -1 and plat[i].link_contact != to) {
            i = plat[i].link_contact;
            ++dist;
        }
        if (plat[i].link_contact == -1) {
            return 0;
        }
        return ++dist;
    }

    pcb pcb::group_cont(type filter) const {
        PCB::pcb circ2;
        int num = 0;
        if (filter !=0 and filter != 1) {
            throw std::invalid_argument("invalid type of contact");
        }
        if (n == 0) {
            throw std::logic_error("Error, this circuit board is empty");
        }
        for (int i = 0; i < n; ++ i) {
            if (plat[i].type_contact == filter) {
                ++num;
            }
        }
        if (num != 0) {
            for (int i = 0; i < n; ++i) {
                if (plat[i].type_contact == filter) {
                    circ2.add_contact(plat[i]);
                }
            }
        }
        return circ2;
    }

    void pcb::pcb_pop() {
        if(n == 0) {
            throw std::invalid_argument("Error, pcb is empty");
        }
        for(int i = 0; i < n - 1; ++i) {
            if (plat[i].link_contact == n - 1) {
                plat[i].link_contact = -1;
            }
        }
        n--;
    }
    //Operators
    contact & pcb::operator[](size_t index) {
        if (index >= n) {
            throw std::out_of_range("Invalid index");
        }
        return plat[index];
    }

    const contact & pcb::operator[](size_t index) const {
        if (index >= n) {
            throw std::out_of_range("Invalid index");
        }
        return plat[index];
    }

    pcb & pcb::operator--() {
        (*this).pcb_pop();
        return *this;
    }

    const pcb pcb::operator--(int d){
        pcb circ(*this);
        (*this).pcb_pop();
        return circ;
    }

    std::ostream& operator<<(std::ostream &out, pcb &circ) {
        return circ.print_pcb(out);
    }

    std::istream& operator>>(std::istream &in, pcb &circ) {
        int n, n0 = circ.getSize();
        contact c;
        in >> n;
        if (n > N - circ.getSize() or n < 0) {
            throw std::invalid_argument("Invalid number of contacts");
        }
        for(int i = n0; i < n0 + n; ++i) {
            c.input_contact(in);
            circ.add_contact(c);
        }
        return in;
    }

    pcb operator !(const pcb &circ) {
        pcb res(circ);
        int n0 = res.getSize();
        int link_to, link_next, j;
        unsigned int check[N] = {};
        for(int i = 0; i < n0; ++i) {
            if (check[i] == 0 and res[i].type_contact == input) {
                link_to = i;
                link_next = res[i].link_contact;
                check[i] = 1;
                if (link_next != -1) {
                    if (res[i].type_contact == input) {
                        res[i].type_contact = (PCB::type) 1;
                        res[i].link_contact = -1;
                    }
                    while (link_next != -1) {
                        j = link_next;
                        link_next = res[j].link_contact;
                        res[j].link_contact = link_to;
                        link_to = j;
                        check[j] = 1;
                    }
                    res[j].type_contact = (PCB::type) 0;
                }
            }
        }
        return res;
    }

    pcb& pcb::operator += (const pcb& pcb1) {
        int n0 = n;
        if (pcb1.getSize() + n > N) {
            throw std::out_of_range("These pcb`s have a lot of contacts");
        }
        for(int i = 0; i < pcb1.getSize(); ++i) {
            (*this).add_contact(pcb1[i]);
            if ((*this)[n - 1].link_contact != -1) {
                (*this)[n - 1].link_contact += n0;
            }
        }
        return (*this);
    }

    pcb operator +(const pcb& pcb1, const pcb& pcb2){
        pcb res;
        if (pcb1.getSize() + pcb2.getSize() > N) {
            throw std::out_of_range("These pcb`s have a lot of contacts");
        }
        res += pcb1;
        res += pcb2;
        return res;
    }

//    std::strong_ordering operator <=> (const pcb& pcb1, const pcb& pcb2) {
//        return pcb1.getSize() <=> pcb2.getSize();
//    }
}