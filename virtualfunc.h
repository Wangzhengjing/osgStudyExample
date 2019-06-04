#ifndef VIRTUALFUNC_H
#define VIRTUALFUNC_H

#include <iostream>

class virtualFunc
{
public:
    virtualFunc();
};

class base1{
public:
    base1(){
        action();
    }

    virtual void f1(){
        std::cout << "this is base1 f1"<<std::endl;
    }

    inline void action()
    {
        f1();
    }

//    virtual void f2() = 0;
};

class derive : public base1
{
public:
    virtual void f1 (){
        std::cout << "this is derive f1"<<std::endl;
    }

//    virtual void f2 (){
//          std::cout << "this is derive f2"<<std::endl;
//    }
};

#endif // VIRTUALFUNC_H
