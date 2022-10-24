#ifndef PCB_HPP
#define PCB_HPP

#include <iostream>
using std::swap;


namespace PCB_dynamic {
struct point {
    double x, y;
    point() :x(0), y(0) {}
    explicit point(double x0, double y0) :x(x0), y(y0){}
    int operator ==(point other) const{
        return ((*this).x == other.x and (*this).y == other.y);
    }
};

enum type {
    output, // 0
    input  // 1
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
        static const int quota = 5;
        contact *plat; //massive of contacts
        int n; //number of busy blocks
        int max_elems; // how blocks pcb can have
    public:
        pcb(); // empty constr

        // ------ Copy and swap idiom ------ //
        pcb(const pcb &); // copy constr
        pcb(pcb &&) noexcept; // move constr

        pcb& operator =(const pcb& circ);
        pcb& operator =(pcb&& circ) noexcept;

        friend void swap(pcb& pcb1, pcb& pcb2) noexcept; // swap

        // ------ destructor ------ //
        ~pcb();

        // ------ getters ------ //
        [[nodiscard]] int len_() const noexcept;
        [[nodiscard]] int max_len() const noexcept;

        // ------ methods ------ //
        void add_contact(contact c);
        std::ostream& print_pcb(std::ostream &out) const noexcept;
        [[nodiscard]] int check_correctly(int num) const; // check input connection to contact
        void add_link(int from, int to); // add new connection
        [[nodiscard]] pcb group_cont(type filter) const; // return group of contacts after filter
        [[nodiscard]] int contact_dist(int from, int to) const; // calculate distance between two contact
        void pcb_pop(); // delete last contact from pcb

        // ------ decrement ------ //
        pcb & operator --();
        const pcb operator --(int);

        // ------ get element ------ //
        contact &operator[](size_t index);
        const contact &operator[](size_t index) const;

        // ------ modified sum ------ //
        pcb& operator +=(const pcb& pcb2);
};

// ------ output ------ //
std::ostream& operator<<(std::ostream &out, pcb &circ);

// ------ input ------ //
std::istream& operator>>(std::istream &in, pcb &circ);

// ------ comparator ------ //
std::strong_ordering operator <=>(const pcb& pcb1, const pcb& pcb2);

// ------ sum ------ //
pcb operator +(const pcb& pcb1, const pcb& pcb2);

// ------ invert ------ //
pcb operator !(const pcb &circ);

} // PCB_dynamic

/*
    Унарный (!) - смена направления связей
    Бинарный (+) - сложение двух плат и запись в новую переменную
    Декремент в двух вариантах - (--i; i--) удаление последнего элемента на плате
    [] В двух возможностях - обращение к конкретному контакту
    Ввод (>>) - ввод платы
    Вывод (<<) - вывод платы
    Модифицирующее присваивание (+=) - добавление элемента на плату
    <=> - сравнение размеров плат
 */

#endif