#include "pcb.hpp"

namespace PCB_dynamic {
    // ----------------- Contact methods and constructors ----------------- //

    contact::contact() :p(0, 0){
        type_contact = output;
        connection_to = -1;
    }
    contact::contact(const point &p0, type t0) :p(p0) {
        if (t0 != output and t0 != input) {
            throw std::invalid_argument("invalid type of contact");
        }
        type_contact = t0;
        connection_to = -1;
    }
    contact::contact(double x0, double y0, type t0) :p(x0, y0) {
        if (t0 != output and t0 != input) {
            throw std::invalid_argument("invalid type of contact");
        }
        type_contact = t0;
        connection_to = -1;
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

    // ----------------- pcb constructors ----------------- //

    // pcb init
    pcb::pcb() {
        n = 0;
        plat = new contact[quota];
        max_elems = quota;
    }

    // copy constructor
    pcb::pcb(const pcb& circ) : n(circ.n), max_elems(circ.max_elems) {
        plat = new contact[max_elems];

        try {
            std::copy(circ.plat, circ.plat + circ.n + 1, plat);
        }
        catch (std::exception& err) {
            delete[] plat;
            throw;
        }
    }

    // copy assigment operator
    pcb& pcb::operator =(const pcb& circ) {
        pcb copy(circ);
        swap(*this, copy);
        return *this;
    }

    // Move constructor
    pcb::pcb(pcb&& circ) noexcept: pcb() {
        swap(*this, circ);
    }

    // move assigment operator
    pcb& pcb::operator =(pcb&& circ) noexcept{
        swap(*this, circ);
        return *this;
    }

    // swap
    void swap(pcb& pcb1, pcb& pcb2) noexcept {
        using std::swap;

        swap(pcb1.n, pcb2.n);
        swap(pcb1.plat, pcb2.plat);
        swap(pcb1.max_elems, pcb2.max_elems);
    }

    // destructor
    pcb::~pcb() {
        delete[] plat;
    }

    // -------------- pcb tasks ----------------- //
    void pcb::add_contact(contact c) {
        if (n >= max_elems - 1) {
            max_elems += quota;
            pcb extended_pcb(*this);
            swap(*this, extended_pcb);
        }
        for(int i = 0; i < n; ++i) {
            if (plat[i].p.x == c.p.x and plat[i].p.y == c.p.y) {
                throw std::invalid_argument("Place with similar coordinates is busy");
            }
        }
        plat[n] = c;
        n += 1;
    }

    int pcb::len_() const noexcept {
        return n;
    }

    int pcb::max_len() const noexcept {
        return max_elems;
    }

    std::ostream& pcb::print_pcb(std::ostream& out) const noexcept{
        if (n == 0)
            out << "Circuit broad is empty" << std::endl;
        else {
            for (int i = 0; i < n; ++i) {
                out << i << " --> ";
                if (plat[i].type_contact) {
                    out << "input, ";
                }
                else {
                    out << "output, ";
                }
                out << "(" << plat[i].p.x << ";" << plat[i].p.y << "), ";
                out << plat[i].connection_to << ";" << std::endl;
            }
        }
        return out;
    }

    int pcb::check_correctly(int num) const { // 0 - has 0 input connection; 1 - has 1 input connection
        int res = 0;
        if (n == 0) {
            throw std::logic_error("Error, this board is empty");
        }
        if (num >= n or num < 0) {
            throw std::invalid_argument("Error, this contact dont`t exist");
        }
        for (int i = 0; i < n; ++i) {
            if (i != num and plat[i].connection_to == num) {
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
        if (plat[from].connection_to != -1) {
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
        plat[from].connection_to = to;
    }

    int pcb::contact_dist(int from, int to) const {
        if ((n <= to or n <= from) or (to < 0 or from < 0)) {
            throw std::invalid_argument("Error, contacts don`t exist");
        }
        if (plat[to].type_contact == input) {
            throw std::logic_error("Error, contact 2 has input type");
        }
        int dist = 0, i = from;
        while (plat[i].connection_to != -1 and plat[i].connection_to != to) {
            i = plat[i].connection_to;
            ++dist;
        }
        if (plat[i].connection_to == -1) {
            return 0;
        }
        return ++dist;
    }

    pcb pcb::group_cont(type filter) const {
        PCB_dynamic::pcb circ2;
        if (filter != output and filter != input) {
            throw std::invalid_argument("invalid type of contact");
        }
        if (n == 0) {
            throw std::logic_error("Error, this circuit board is empty");
        }
        for (int i = 0; i < n; ++i) {
            if (plat[i].type_contact == filter) {
                circ2.add_contact(plat[i]);
            }
        }
        return circ2;
    }

    void pcb::pcb_pop() {
        if(n == 0) {
            throw std::invalid_argument("Error, pcb is empty");
        }
        for(int i = 0; i < n - 1; ++i) {
            if (plat[i].connection_to == n - 1) {
                plat[i].connection_to = -1;
            }
        }
        n--;
        if (n < max_elems - quota * 2 - 1) {
            max_elems -= 2 * quota;
            pcb narrowed_pcb(*this);
            swap(*this, narrowed_pcb);
        }
    }

    //Operators
    contact & pcb::operator [](size_t index) {
        if (index >= n) {
            throw std::out_of_range("Invalid index");
        }
        return plat[index];
    }

    const contact & pcb::operator [](size_t index) const {
        if (index >= n) {
            throw std::out_of_range("Invalid index");
        }
        return plat[index];
    }

    pcb & pcb::operator --() {
        (*this).pcb_pop();
        return *this;
    }

    const pcb pcb::operator --(int){
        pcb circ(*this);
        (*this).pcb_pop();
        return circ;
    }

    std::ostream& operator <<(std::ostream &out, pcb &circ) {
        return circ.print_pcb(out);
    }

    std::istream& operator >>(std::istream &in, pcb &circ) {
        int n, n0 = circ.len_();
        contact c;
        in >> n;
        if (n <= 0) {
            throw std::invalid_argument("Invalid number of contacts");
        }
        for(int i = n0; i < n0 + n; ++i) {
            c.input_contact(in);
            circ.add_contact(c);
        }
        return in;
    }

    pcb operator !(pcb &circ) {
        pcb res(circ);
        int n0 = res.len_(), i;
        int link_to, link_next, j;
        auto *check = new unsigned int [n0];
        for (i = 0; i < n0; ++i) {
            check[i] = 0;
        }
        for(i = 0; i < n0; ++i) {
            if (check[i] == 0 and res[i].type_contact == input) {
                link_to = i;
                link_next = res[i].connection_to;
                check[i] = 1;
                if (link_next != -1) {
                    if (res[i].type_contact == input) {
                        res[i].type_contact = output;
                        res[i].connection_to = -1;
                    }
                    while (link_next != -1) {
                        j = link_next;
                        link_next = res[j].connection_to;
                        res[j].connection_to = link_to;
                        link_to = j;
                        check[j] = 1;
                    }
                    res[j].type_contact = input;
                }
            }
        }
        delete[] check;
        return res;
    }

    pcb& pcb::operator +=(const pcb& pcb1) {
        int n0 = n;
        for(int i = 0; i < pcb1.len_(); ++i) {
            (*this).add_contact(pcb1[i]);
            if ((*this)[n - 1].connection_to != -1) {
                (*this)[n - 1].connection_to += n0;
            }
        }
        return (*this);
    }

    pcb operator +(const pcb& pcb1, const pcb& pcb2){
        pcb res(pcb1);
        res += pcb2;
        return res;
    }

    std::strong_ordering operator <=>(const pcb& pcb1, const pcb& pcb2) {
        return pcb1.len_() <=> pcb2.len_();
    }
}