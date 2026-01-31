//comp_card.h
#ifndef COMP_CARD_H
#define COMP_CARD_H

#include "debit.h"
#include "credit.h"
using namespace std;

class CompCard:virtual public Debit, virtual public Credit{
    public:
        CompCard();
        CompCard(int);
        CompCard(int, string, string, string, string, string, string);
        virtual void withdrawal(double);        //取款
        virtual void asset_display() const;     //资产查询
};

#endif