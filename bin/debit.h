//debit.h
#ifndef DEBIT_H
#define DEBIT_H

#include "account.h"
using namespace std;

class Debit:virtual public Account{
    public:
        Debit();
        Debit(int);
        Debit(int, string, string, string, string, string, string);
        virtual void asset_display() const;     //资产查询
};

#endif