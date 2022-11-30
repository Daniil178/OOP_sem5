#include <iostream>
#include <cstdio>
#include <cstring>
#include "deltoid.hpp"

namespace Prog2{

    Deltoid::Deltoid(double r0) :p(0, 0){
        if (r0 <= 0)
            throw std::invalid_argument( "received negative value" );
        r = r0;
    }
    Deltoid::Deltoid(const point &p0, double r0) :p(p0){
        if (r0 <= 0)
            throw std::invalid_argument( "received negative value" );
        r = r0;
    }
    Deltoid::Deltoid(double x0, double y0, double r0) :p(x0, y0){
        if (r0 <= 0)
            throw std::invalid_argument( "received negative value" );
        r = r0;
    }
    //setters
    void Deltoid::setR(double r0){
        if (r0 <= 0)
            throw std::invalid_argument( "received negative value" );
        r = r0;
    }
    void Deltoid::setP(const point &p0){
        p = p0;
    }
    //getters
    double Deltoid::getR() const{
        return r;
    }
    point Deltoid::getP() const{
        return p;
    }
    //tasks
    double Deltoid::area_with_tangent() const{
        return 4 * r;
    }
    double Deltoid::perimeter() const{
        return 16 * r;
    }
    double Deltoid::area() const{
        return 2 * M_PI * r * r;
    }
    point Deltoid::f(double t) const{
        point p1;
        p1.x = 2*r*cos(t) + r*cos(2*t) + p.x;
        p1.y = 2*r*sin(t) - r*sin(2*t) + p.y;
        return p1;
    }
//    char* Deltoid::formula() const{ //(x^2 + y^2)^2 + 18*(x^2 + y^2) = 8x^3 - 24y^2*x + 27
//        const char *s1 = "((x - )^2 + (y - )^2)^2 + 18*((x - )^2 + (y - )^2) = 8(x - )^3 - 24(y - )^2 * (x - ) + 27";
//        unsigned int l = strlen(s1) + 1;
//        size_t size = 20;
//        char num[20];
//        sprintf_s(num, size, "%.2f", p.x);
//        if(p.x != 0)
//            l += 4 * strlen(num);
//        sprintf_s(num, size, "%.2f", p.y);
//        if(p.y != 0)
//            l += 3 * strlen(num);
//        char *s = new char[l];
//        if(p.x == 0 and p.y == 0)
//            sprintf_s(s, l, "(x^2 + y^2)^2 + 18*(x^2 + y^2) = 8x^3 - 24y^2 * x + 27");
//        else if (p.x == 0)
//            sprintf_s(s, l, "((x - %.2f)^2 + y^2)^2 + 18*((x - %.2f)^2 + y^2) = 8(x - %.2f)^3 - 24y^2 * (x - %.2f) + 27", p.x, p.x, p.x, p.x);
//        else if (p.y == 0)
//            sprintf_s(s, l, "(x^2 + (y - %.2f)^2)^2 + 18*(x^2 + (y - %.2f)^2) = 8x^3 - 24(y - %.2f)^2 *x + 27", p.y, p.y, p.y);
//        else
//            sprintf_s(s, l, "((x - %.2f)^2 + (y - %.2f)^2)^2 + 18*((x - %.2f)^2 + (y - %.2f)^2) = 8(x - %.2f)^3 - 24(y - %.2f)^2 * (x - %.2f) + 27", p.x, p.y, p.x, p.y, p.x, p.y, p.x);
//        return s;
//    }

}