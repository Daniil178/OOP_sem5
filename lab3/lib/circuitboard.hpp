#ifndef CIRCUITBOARD_HPP
#define CIRCUITBOARD_HPP

#include <iostream>
#define N 5

namespace PCB {

struct point{
    double x, y;
    explicit point(double x0 = 0, double y0 = 0) :x(x0), y(y0){}
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
    pcb(const pcb &);
    void add_contact(contact c);
    //getters
    [[nodiscard]] int getSize() const noexcept;
    //tasks
    std::ostream& print_pcb(std::ostream &out) const noexcept;
    [[nodiscard]] int check_correctly(int num) const;
    void add_link(int from, int to);
    [[nodiscard]] pcb group_cont(type filter) const;
    [[nodiscard]] int contact_dist(int from, int to) const;
    void pcb_pop();

    pcb & operator --();
    const pcb operator --(int);

    contact &operator[](size_t index);
    const contact &operator[](size_t index) const;

    friend std::ostream& operator<<(std::ostream &out, pcb &circ);
    friend std::istream& operator>>(std::istream &in, pcb &circ);

    pcb& operator += (const pcb& pcb2);

};
pcb operator + (const pcb& pcb1, const pcb& pcb2);
pcb operator !(const pcb &circ);
std::strong_ordering operator <=> (const pcb& pcb1, const pcb& pcb2);

} //PCB

/*
    ++ Унарный (~) - смена направления связей
    ++ Бинарный (+) - сложение двух плат и запись в новую (по возможности места без замены)
    ++ Декремент/инкремент в двух вариантах - декремент (--i; i--) удаление последнего элемента на плате
    ++ [] В двух возможностях - обращение к конкретному контакту
    ++ Ввод (>>) - ввод платы
    ++ вывод (<<) - вывод платы
    ++ Модифицирующее присваивание (+=) - (добавление элемента на плату)
    ++ <=>, Если с++20 (иначе узнайте) - сравнение размеров плат
 */

#endif