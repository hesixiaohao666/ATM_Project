//debit.cpp
#include <iostream>
#include "debit.h"

Debit::Debit(){}
Debit::Debit(int aid):Account(aid){
    type = 1;
}
Debit::Debit(int aid, string pd, string nam, string s, string addr, string tele, string cid):Account(aid, pd){
    type = 1;
    name = nam;
    sex = s;
    address = addr;
    telephone = tele;
    card_id = cid;
    balance = 0;
    login_time = 0;
    level = 0;
    cout<<"【系统】账户类型为：储蓄卡"<<endl;
}

void Debit::asset_display() const{
    cout<<"当前账户余额："<<setiosflags(ios::fixed)<<setprecision(2)<<balance<<"元"<<endl;
    cout<<"当前利率："<<setiosflags(ios::fixed)<<setprecision(4)<<rate[level]<<endl;
    cout<<"预计利息："<<setiosflags(ios::fixed)<<setprecision(2)<<balance*rate[level]<<"元"<<endl;
}