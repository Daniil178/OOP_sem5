#include <iostream>
#include "deltoid.hpp"

using namespace Prog2;

int main(){
    Deltoid d(0, 0, 1);
    point p(3);
    int fl1 = 1;
    double rad;
    while(fl1) {
        std::cout << "Your deltoid is:\n" << std::endl;
        char *s = d.formula();
        std::cout << s << std::endl;
        delete [] s;
        std::cout << "\n----------------------------" << std::endl;
        std::cout << "coordinates of center: (" << d.getP().x << ", " << d.getP().y << ")" << std::endl;
        std::cout << "radius: " << d.getR() << std::endl;
        std::cout << "area_with_tangent: " << d.area_with_tangent() << std::endl;
        std::cout << "perimeter: " << d.perimeter() << std::endl;
        std::cout << "area: " << d.area() << std::endl;
        std::cout << "----------------------------" << std::endl;
        int fl2 = 1;
        while(fl2) {
            std::cout << "Enter t for calculate value x(t), y(t) or enter any symbol to quit:" << std::endl;
            double t;
            point xy_t;
            std::cin >> t;
            fl2 = std::cin.good();
            if (!fl2){
                std::cin.clear();
                std::cin.sync();
                continue;
            }
            try{
                xy_t = d.f(t);
                std::cout << "x = " << xy_t.x << ", y = " << xy_t.y << std::endl;
            }
            catch(std::exception &ex){
                std::cout << ex.what() << std::endl;
            }
        }
        std::cin.clear();
        std::cout << "Enter new x, y and r to continue or enter any symbol to quit:" << std::endl;
        std::cin >> p.x >> p.y >> rad;
        if(std::cin.good()){
            while(rad <= 0 or !std::cin.good()){
                std::cout << "Error, radius must be number > 0\nPlease, repeat enter radius:" << std::endl;
                std::cin.clear();
                std::cin.sync();
                std::cin >> rad;
            }
            d.setP(p);
            try {
                d.setR(rad);
            }
            catch (std::exception &ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else {
            fl1 = 0;
            std::cin.clear();
            std::cin.sync();
        }
    }
    return 0;
}

