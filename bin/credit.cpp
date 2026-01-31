//crebit.cpp
#include "credit.h"

Credit::Credit(){}
Credit::Credit(int aid):Account(aid){
    type = 2;
}
Credit::Credit(int aid, string pd, string nam, string s, string addr, string tele, string cid):Account(aid, pd){
    type = 2;
    name = nam;
    sex = s;
    address = addr;
    telephone = tele;
    card_id = cid;
    balance = 0;
    login_time = 0;
    level = 0;
    cout<<"【系统】账户类型为：信用卡"<<endl;
}

void Credit::withdrawal(double reduce){
    if(reduce<=balance+limit[level]){
        balance -= reduce;
    }
    else{
        cout<<"【错误】超出账户透支额度"<<endl;
    }
}

void Credit::asset_display() const{
    cout<<"当前账户余额："<<setiosflags(ios::fixed)<<setprecision(2)<<balance<<"元"<<endl;
    cout<<"当前透支额度："<<setiosflags(ios::fixed)<<setprecision(2)<<limit[level]<<"元"<<endl;
}