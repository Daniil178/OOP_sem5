#ifndef DELTOID_HPP
#define DELTOID_HPP
#include <cmath>

namespace Prog2{
    struct point{
        double x, y;
        point(double x0 = 0, double y0 = 0) :x(x0), y(y0){}
    };
    class Deltoid{
    private:
        point p;
        double r;
    public:
        Deltoid(double r0 = 1);
        Deltoid(const point &p0, double r0 = 1);
        Deltoid(double x0, double y0, double r0);
        //setters
        void setR(double r0);
        void setP(const point &p0);
        //getters
        double getR() const;
        point getP() const;
        //tasks
        double area_with_tangent() const;
        double perimeter() const;
        double area() const;
        point f(double t) const;
        char *formula() const;
    };
}

#endif