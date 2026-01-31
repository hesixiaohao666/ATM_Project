//comp_card.cpp
#include "comp_card.h"

CompCard::CompCard(){}
CompCard::CompCard(int aid):Account(aid){
    type = 3;
}
CompCard::CompCard(int aid, string pd, string nam, string s, string addr, string tele, string cid):Account(aid, pd){
    type = 3;
    name = nam;
    sex = s;
    address = addr;
    telephone = tele;
    card_id = cid;
    balance = 0;
    login_time = 0;
    level = 0;
    cout<<"【系统】账户类型为：复合卡"<<endl;
}

void CompCard::withdrawal(double reduce){
    if(reduce<=balance+limit[level]){
        balance -= reduce;
    }
    else{
        cout<<"【错误】超出账户透支额度"<<endl;
    }
}

void CompCard::asset_display() const{
    cout<<"当前账户余额："<<setiosflags(ios::fixed)<<setprecision(2)<<balance<<"元"<<endl;
    cout<<"当前利率："<<setiosflags(ios::fixed)<<setprecision(4)<<rate[level]<<endl;
    if(balance>=0){
        cout<<"预计利息："<<setiosflags(ios::fixed)<<setprecision(2)<<balance*rate[level]<<"元"<<endl;
    }
    else{
        cout<<"预计利息："<<0<<"元"<<endl;
    }
    cout<<"当前透支额度："<<setiosflags(ios::fixed)<<setprecision(2)<<limit[level]<<"元"<<endl;
}