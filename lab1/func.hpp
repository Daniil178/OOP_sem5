#ifndef FUNC_HPP
#define FUNC_HPP

namespace lab1{
    struct list{
        int x; //column number
        int information; //information
        list *next_column; //ptr to next element
    };
    struct Matr{ //struct of Matrix
        int y; //row number
        list *row; //list with information in row
        Matr *next_row; //ptr to next row
    };
    template <class T>
    int getNum(T &a){ //get int number
        std::cin >> a;
        if (!std::cin.good())
            return -1;
        return 1;
    }
    inline int get_int(const char *msg, int &n){
        const char *pr = "";
        do{
            std::cout << pr << std::endl;
            std::cout << msg;
            pr = "You are wrong, repeat please!";
            if (getNum(n) < 0) // input Error
                return -1;
        } while (n < 1);
        return n;
    }
    //prototype of functions
    int transform(int a);
    Matr* input();
    Matr *add_matr(Matr *matr, int y, int x, int info);
    void output(const char *msg, Matr *A);
    Matr *erase(Matr *A);
    Matr *create_new_Matr(Matr *A, int(*f)(int));
    list *add_lst(list *lst, int x, int info);
}
#endif