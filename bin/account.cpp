//account.cpp
#include "account.h"

Account::Account(){}
Account::Account(int aid){
    type = 0;
    account_id = aid;
    password = "";
    name = "";
    sex = "";
    address = "";
    telephone = "";
    card_id = "";
    balance = 0;
    login_time = 0;
    level = 0;
    cout<<"【系统】已读取账户ID："<<account_id<<endl;
}
Account::Account(int aid, string pd){
    type = 0;
    account_id = aid;
    password = pd;
    name = "";
    sex = "";
    address = "";
    telephone = "";
    card_id = "";
    balance = 0;
    login_time = 0;
    level = 0;
    cout<<"【系统】已创建账户ID："<<account_id<<endl;
}

Account::~Account(){
    ofstream account("../data/account"+to_string(account_id)+".dat", ios::out);
    account<<-1<<endl;
    account.close();
    cout<<"【系统】账户（ID："<<account_id<<"）已删除"<<endl;
}

void Account::set_password(string pd){
    password = pd;
}

void Account::set_name(string nam){
    name = nam;
}

void Account::set_sex(string s){
    sex = s;
}

void Account::set_address(string addr){
    address = addr;
}

void Account::set_telephone(string tele){
    telephone = tele;
}

void Account::set_card_id(string cid){
    card_id = cid;
}

void Account::set_level(int l){
    level = l;
}

bool Account::password_check(string pd) const{
    if(pd==password){
        return true;
    }
    else{
        return false;
    }
}

void Account::login_time_add(){
    login_time++;
    login_times++;
}

void Account::deposit(double add){
    balance += add;
}

void Account::withdrawal(double reduce){
    if(reduce<=balance){
        balance -= reduce;
    }
    else{
        cout<<"【错误】账户余额不足"<<endl;
    }
}

void Account::information_dispaly() const{
    cout<<"账号ID："<<account_id<<endl;
    cout<<"姓名："<<name<<endl;
    cout<<"性别："<<sex<<endl;
    cout<<"地址："<<address<<endl;
    cout<<"电话号码："<<telephone<<endl;
    cout<<"身份证号："<<card_id<<endl;
    cout<<"账户等级："<<level<<endl;
    cout<<"登录次数："<<login_time<<endl;
}

void Account::asset_display() const{}

void Account::read_data(){
    ifstream account("../data/account"+to_string(account_id)+".dat", ios::in);
    if (!account.is_open()){
        return;
    }
    account>>type;
    account>>account_id;
    account>>password;
    account>>name;
    account>>sex;
    account>>address;
    account>>telephone;
    account>>card_id;
    account>>balance;
    account>>login_time;
    account>>level;
    account.close();
}

void Account::save_data(){
    ofstream account("../data/account"+to_string(account_id)+".dat", ios::out);
    account<<type<<endl;
    account<<account_id<<endl;
    account<<password<<endl;
    account<<name<<endl;
    account<<sex<<endl;
    account<<address<<endl;
    account<<telephone<<endl;
    account<<card_id<<endl;
    account<<balance<<endl;
    account<<login_time<<endl;
    account<<level<<endl;
    account.close();
}