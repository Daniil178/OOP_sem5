#include <iostream>
#include "func.hpp"
using namespace lab1;

int main(){
    Matr *a = nullptr, *b = nullptr;
    int x, info, n;
    a = input();
    if(a != nullptr){
        output("First Matrix", a);
        b = create_new_Matr(a, transform);
        if(b != nullptr){
            output("Transform Matrix", b);
            erase(b);
        }
        erase(a);
    }
    return 0;
}