#ifndef DELTOID_HPP
#define DELTOID_HPP
#include <cmath>

namespace Prog2{
    struct point{
        double x, y;
        explicit point(double x0 = 0, double y0 = 0) :x(x0), y(y0){}
    };
    class Deltoid{
    private:
        point p;
        double r;
    public:
        explicit Deltoid(double r0 = 1);
        explicit Deltoid(const point &p0, double r0 = 1);
        Deltoid(double x0, double y0, double r0);
        //setters
        void setR(double r0);
        void setP(const point &p0);
        //getters
        [[nodiscard]] double  getR() const ;
        [[nodiscard]] point getP() const;
        //tasks
        [[nodiscard]] double area_with_tangent() const;
        [[nodiscard]] double perimeter() const;
        [[nodiscard]] double area() const;
        [[nodiscard]] point f(double t) const;
        //[[nodiscard]] char *formula() const;
    };
}

#endif