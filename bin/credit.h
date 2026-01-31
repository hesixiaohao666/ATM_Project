//credit.h
#ifndef CREDIT_H
#define CREDIT_H

#include "account.h"
using namespace std;

class Credit:virtual public Account{
    public:
        Credit();
        Credit(int);
        Credit(int, string, string, string, string, string, string);
        virtual void withdrawal(double);        //取款
        virtual void asset_display() const;     //资产查询
};

#endif