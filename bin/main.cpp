//main.cpp
#include <iostream>
#include "atm.h"

int main(){
    ATM *atmptr = new ATM;
    atmptr->run();
    delete atmptr;
    return 0;
}