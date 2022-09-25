#include <iostream>
#include "deltoid.hpp"

using namespace Prog2;

int main(){
    Deltoid d(0, 0, 1);
    point p(3);
    int fl1 = 1;
    double rad;
    while(fl1) {
        std::cout << "Your deltoid is:" << std::endl;
        std::cout << "----------------------------" << std::endl;
        char *s = d.formula();
        std::cout << s << std::endl;
        delete [] s;
        std::cout << "coordinates of center: (" << d.getP().x << ", " << d.getP().y << ")" << std::endl;
        std::cout << "radius: " << d.getR() << std::endl;
        std::cout << "area_with_tangent: " << d.area_with_tangent() << std::endl;
        std::cout << "perimeter: " << d.perimeter() << std::endl;
        std::cout << "area: " << d.area() << std::endl;

        int fl2 = 1;
        while(fl2 == 1) {
            std::cout << "----------------------------" << std::endl;
            std::cout << "0 - quit\n1 - calculate x(t) and y(t)\n2 - enter new parameters" << std::endl;
            std::cout << "----------------------------" << std::endl;
            std::cout << "Your choice:" << std::endl;
            std::cin >> fl2;
            if(!std::cin.good() or (fl2 != 0 and fl2 != 1 and fl2 != 2)){
                std::cin.clear();
                std::cin.sync();
                std::cout << "False input, try again" << std::endl;
                fl2 = 1;
            }
            else{
                if (fl2 == 1) {
                    std::cin.clear();
                    std::cin.sync();
                    std::cout << "Enter t for calculate value x(t), y(t):" << std::endl;
                    double t;
                    point xy_t;
                    std::cin >> t;
                    while (!std::cin.good()) {
                        std::cin.clear();
                        std::cin.sync();
                        std::cout << "Error, enter real number:" << std::endl;
                        std::cin >> t;
                    }
                    std::cin.clear();
                    std::cin.sync();
                    try {
                        xy_t = d.f(t);
                        std::cout << "x = " << xy_t.x << ", y = " << xy_t.y << std::endl;
                    }
                    catch (std::exception &ex) {
                        std::cout << ex.what() << std::endl;
                    }
                } else if (fl2 == 2) {
                    std::cin.clear();
                    std::cin.sync();
                    std::cout << "Enter new x, y and r to continue or enter any symbol to quit:" << std::endl;
                    std::cin >> p.x >> p.y >> rad;
                    while (!std::cin.good()) {
                        std::cin.clear();
                        std::cin.sync();
                        std::cout << "Error, enter real numbers x,y and positive real number r" << std::endl;
                        std::cin >> p.x >> p.y >> rad;
                    }
                    while (rad <= 0 or !std::cin.good()) {
                        std::cin.clear();
                        std::cin.sync();
                        std::cout << "Error, radius must be number > 0\nPlease, repeat enter radius:" << std::endl;
                        std::cin >> rad;
                    }
                    std::cin.clear();
                    std::cin.sync();
                    d.setP(p);
                    try {
                        d.setR(rad);
                    }
                    catch (std::exception &ex) {
                        std::cout << ex.what() << std::endl;
                    }
                }
                else
                    fl1 = 0;
            }
        }
    }
    return 0;
}

