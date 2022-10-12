#ifndef CIRCUITBOARD_HPP
#define CIRCUITBOARD_HPP

#include <iostream>
#define N 5 // max len

namespace PCB {

struct point{
    double x, y;
    point() : x(0), y(0) {}
    point(double x0, double y0) :x(x0), y(y0){}
};
// class for type of contact
enum type{
    input, // 0
    output // 1
};

struct contact{
    type type_contact;
    point p;
    int link_contact;
    contact(); // Init without params
    explicit contact(const point &p0, type t0 = input); // Init with particularly params
    contact(double x0, double y0, type t0); // Init with params
    std::istream& input_contact(std::istream &in);
};

class pcb{
private:
    contact plat[N]; //massive of contacts
    int n; //number of busy blocks
public:
    pcb();
    pcb(const pcb &);
    void add_contact(contact c);
    //getters
    [[nodiscard]] int getSize() const noexcept;
    //tasks
    std::ostream& print_pcb(std::ostream &out) const noexcept;
    [[nodiscard]] int check_correctly(int num) const; // check input connection to contact
    void add_link(int from, int to); // add new connection
    [[nodiscard]] pcb group_cont(type filter) const; // return group of contacts after filter
    [[nodiscard]] int contact_dist(int from, int to) const; // calculate distance between two contact
    void pcb_pop(); // delete last contact from pcb
    //decrement
    pcb & operator --();
    const pcb operator --(int);
    //get element
    contact &operator[](size_t index);
    const contact &operator[](size_t index) const;
    //input, output
    friend std::ostream& operator<<(std::ostream &out, pcb &circ);
    friend std::istream& operator>>(std::istream &in, pcb &circ);
    //modified sum
    pcb& operator += (const pcb& pcb2);
    //comparator
    friend std::strong_ordering operator <=>(const pcb& pcb1, const pcb& pcb2);
};
pcb operator +(const pcb& pcb1, const pcb& pcb2);
pcb operator !(const pcb &circ);
} //PCB

/*
    ++ Унарный (!) - смена направления связей
    ++ Бинарный (+) - сложение двух плат и запись в новую
    ++ Декремент в двух вариантах - (--i; i--) удаление последнего элемента на плате
    ++ [] В двух возможностях - обращение к конкретному контакту
    ++ Ввод (>>) - ввод платы
    ++ вывод (<<) - вывод платы
    ++ Модифицирующее присваивание (+=) - добавление элемента на плату
    ++ <=> - сравнение размеров плат
 */

#endif