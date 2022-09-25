#include <iostream>
#include "func.hpp"
namespace lab1{
    //tranformation function
    int transform(int a){ //invert numbers in number
        int b = 0, inv = 1;
        if(a < 0){
            a *= -1;
            inv = -1;
        }
        while(a != 0){
            b = b * 10 + a %10;
            a /=10;
        }
        return b * inv;
    }
    //input of matrix
    Matr* input(){
        const char *pr = "";
        Matr *matr = nullptr, *elem = nullptr;
        int x, y, info, n;
        n = get_int("Enter number of elements --> ", n);
        if (n < 0){ std::cout << "input Error" << std::endl; return nullptr;}
        for(int i = 0; i < n; ++i){

            y = get_int("Enter row number --> ", y); if (y < 0){std::cout << "input Error" << std::endl;  return nullptr;}
            x = get_int("Enter column number --> ", x); if (x < 0){ std::cout << "input Error" << std::endl; return nullptr;}
            std::cout << "Enter information --> ";
            if (getNum(info) < 0) // input Error
                return nullptr;
            matr = add_matr(matr, y, x, info);
        }
        return matr;
    }

    Matr *add_matr(Matr *matr, int y, int x, int info){
        Matr *elem = nullptr, *ptr = matr;
        try{
            elem = new Matr;
            elem->y = y;
            elem->next_row = nullptr;
            elem->row = nullptr;
        }
        catch (std::bad_alloc &ba){
            std::cout << "Alloc error" << ba.what() <<std::endl;
            return nullptr;
        }
        if(ptr == nullptr or y < ptr->y){
            elem->next_row = matr;
            elem->row = add_lst(elem->row, x, info);
            return elem;
        }
        else{
            while(ptr->next_row != nullptr and ptr->next_row->y < y and ptr->y != y){
                ptr = ptr->next_row;
            }
            if(ptr->next_row != nullptr and ptr->next_row->y == y){
                ptr->next_row->row = add_lst(ptr->next_row->row, x, info);
                delete elem;
            }
            else if(ptr->y == y){
                ptr->row = add_lst(ptr->row, x, info);
                delete elem;
            }
            else{
                elem->next_row = ptr->next_row;
                ptr->next_row = elem;
                elem->row = add_lst(elem->row, x, info);
            }
        }
        return matr;
    }
    //transform matrix
    Matr *create_new_Matr(Matr *A, int(*f)(int)){
        list *ptr_x;
        Matr *ptr_y = A, *B = nullptr;
        int x, y, info;
        while(ptr_y != nullptr){
            ptr_x = ptr_y -> row;
            y = ptr_y->y;
            while(ptr_x != nullptr){
                info = f(ptr_x->information);
                B = add_matr(B, y, ptr_x->x, info);
                ptr_x = ptr_x -> next_column;
            }
            ptr_y = ptr_y -> next_row;
        }
        return B;
    }
    //function of output
    void output(const char *msg, Matr *A){
        list *ptr_x;
        Matr *ptr_y = A;
        std::cout << msg << ":\n";
        while(ptr_y != nullptr){
            ptr_x = ptr_y -> row;
            std::cout << ptr_y->y << ": ";
            while(ptr_x != nullptr){
                std::cout << ptr_x->x << "-" <<ptr_x -> information << " ";
                ptr_x = ptr_x -> next_column;
            }
            std::cout << std::endl;
            ptr_y = ptr_y -> next_row;
        }
    }
    //delete list
    list *del_list(list *lst){
        list *ptr = nullptr;
        while(lst->next_column != nullptr){
            ptr = lst->next_column;
            lst->next_column = ptr->next_column;
            delete ptr;
            ptr = nullptr;
        }
        delete lst;
        return nullptr;
    }
    //delete Matrix
    Matr *erase(Matr *A){
        Matr *ptr_matr = nullptr;
        list *ptr = nullptr;
        while(A->next_row != nullptr){
            ptr_matr = A->next_row;
            A->next_row = ptr_matr->next_row;
            ptr = ptr_matr->row;
            del_list(ptr);
            delete ptr_matr;
            ptr_matr = nullptr;
        }
        ptr = A->row;
        del_list(ptr);
        delete A;
        return nullptr;
    }
    //add elem in list
    list *add_lst(list *lst, int x, int info){
        list *ptr = lst, *elem = nullptr;
        try{
            elem = new list;
            elem->x = x;
            elem->information = info;
            elem->next_column = nullptr;
        }
        catch (std::bad_alloc &ba){
            std::cout << "Alloc error" << ba.what() <<std::endl;
            return lst;
        }
        if(ptr == nullptr or x < ptr->x){
            elem->next_column = lst;
            return elem;
        }
        else{
            while(ptr->next_column != nullptr and ptr->next_column->x < x and ptr->x != x){
                ptr = ptr->next_column;
            }
            if(ptr->next_column != nullptr and ptr->next_column->x == x){
                ptr->next_column->information = info;
                std::cout << "You change information in exist block" << std::endl;
                delete elem;
            }
            else if (ptr->x == x){
                ptr->information = info;
                std::cout << "You change information in exist block" << std::endl;
                delete elem;
            }
            else{
                elem->next_column = ptr->next_column;
                ptr->next_column = elem;
            }
        }
        return lst;
    }
}