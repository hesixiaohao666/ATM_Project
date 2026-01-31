//atm.cpp
#include <iostream>
#include <fstream>
#include "atm.h"

/*全局数据初始化*/
double Account::rate[3] = {0};
double Account::limit[3] = {0};
int Account::login_times = 0;

ATM::ATM(){
    /*配置初始化*/
    cout<<"【系统】正在初始化配置数据"<<endl;
    administrator_mode = false;
    accounts[10000] = {nullptr};
    current_aid = 0;
    next_aid = 1;
    /*读取配置数据*/
    ifstream configuration("../data/configuration.dat", ios::in);
    if(configuration.is_open()){
        cout<<"【系统】正在读取配置数据"<<endl;
        configuration>>next_aid;
        configuration>>Account::rate[0];
        configuration>>Account::rate[1];
        configuration>>Account::rate[2];
        configuration>>Account::limit[0];
        configuration>>Account::limit[1];
        configuration>>Account::limit[2];
        configuration>>Account::login_times;
        configuration.close();
    }
    else{
        initialize();
        return;
    }
    /*读取用户数据*/
    cout<<"【系统】正在读取用户数据"<<endl;
    for(int account_id = 0; account_id<next_aid; account_id++){
        ifstream account("../data/account"+to_string(account_id)+".dat", ios::in);
        if(!account.is_open()){
            accounts[account_id] = nullptr;
            continue;
        }
        int type;
        account>>type;
        account.close();
        if(type==-1){
            accounts[account_id] = nullptr;
            continue;
        }
        if(type==0){
            Account *accountptr = new Account(account_id);
            accounts[account_id] = accountptr;
        }
        else if(type==1){
            Account *accountptr = new Debit(account_id);
            accounts[account_id] = accountptr;
        }
        else if(type==2){
            Account *accountptr = new Credit(account_id);
            accounts[account_id] = accountptr;
        }
        else if(type==3){
            Account *accountptr = new CompCard(account_id);
            accounts[account_id] = accountptr;
        }
        accounts[account_id]->read_data();
    }
}

ATM::~ATM(){
    /*保存配置数据*/
    cout<<"【系统】正在保存配置数据"<<endl;
    ofstream configuration("../data/configuration.dat", ios::out);
    configuration<<next_aid<<endl;
    configuration<<Account::rate[0]<<endl;
    configuration<<Account::rate[1]<<endl;
    configuration<<Account::rate[2]<<endl;
    configuration<<Account::limit[0]<<endl;
    configuration<<Account::limit[1]<<endl;
    configuration<<Account::limit[2]<<endl;
    configuration<<Account::login_times<<endl;;
    configuration.close();
    /*保存用户数据*/
    cout<<"【系统】正在保存用户数据"<<endl;
    for(int account_id = 0; account_id<next_aid; account_id++){
        if(accounts[account_id]!=nullptr){
            accounts[account_id]->save_data();
        }
    }
}

void ATM::run(){
    /*登录页面*/
    while(true){
        int function;
        cout<<endl<<endl<<endl;
        cout<<"===== ATM个人银行账户管理系统 ====="<<endl;
        cout<<"[1]登录"<<endl;
        cout<<"[2]注册"<<endl;
        cout<<"[0]退出系统"<<endl;
        cout<<"【操作】请输入功能代号：";
        cin>>function;
        if(function==0){
            /*退出系统*/
            break;
        }
        else if(function==1){
            /*登录功能*/
            login();
            continue;
        }
        else if(function==2){
            /*注册功能*/
            create_account();
            continue;
        }
        else{
            cout<<"【错误】功能代号不存在，请重试"<<endl;
        }
    }
}

void ATM::administrator_menu(){
    while(true){
        int function;
        cout<<endl<<endl<<endl;
        cout<<"==== 管理员菜单 ===="<<endl;
        cout<<" 当前客户ID："<<current_aid<<endl;
        cout<<" -- 业务办理 -- "<<endl;
        cout<<"[1]切换客户"<<endl;
        cout<<"[2]开户"<<endl;
        cout<<"[3]销户"<<endl;
        cout<<"[4]存款"<<endl;
        cout<<"[5]取款"<<endl;
        cout<<"[6]查询信息"<<endl;
        cout<<"[7]修改信息"<<endl;
        cout<<" -- 管理员设置 -- "<<endl;
        cout<<"[8]修改密码"<<endl;
        cout<<"[9]查询全局数据"<<endl;
        cout<<"[10]设置全局利率"<<endl;
        cout<<"[11]设置全局透支额度"<<endl;
        cout<<"[0]退出管理员登录"<<endl;
        cout<<"请输入功能代号：";
        cin>>function;
        if(function==0){
            current_aid = 0;
            administrator_mode = false;
            break;
        }
        else if(function==1){
            change_account_id();
            continue;
        }
        else if(function==2){
            /*开户功能*/
            create_account();
            continue;
        }
        else if(function==3){
            /*销户功能*/
            delete_account();
            continue;
        }
        else if(function==4){
            /*存款功能*/
            deposit();
            continue;
        }
        else if(function==5){
            /*取款功能*/
            withdrawal();
            continue;
        }
        else if(function==6){
            /*查询信息功能*/
            display();
            continue;
        }
        else if(function==7){
            /*修改信息功能*/
            change_information();
            continue;
        }
        else if(function==8){
            /*修改密码功能*/
            change_password();
            continue;
        }
        else if(function==9){
            /*查询全局数据功能*/
            data_display();
        }
        else if(function==10){
            /*设置全局利率功能*/
            set_rate();
            continue;
        }
        else if(function==11){
            /*设置全局透支额度功能*/
            set_limit();
            continue;
        }
        else{
            cout<<"【错误】功能代号不存在，请重试"<<endl;
        }
    }
}

void ATM::member_menu(){
    while(true){
        int function;
        cout<<endl<<endl<<endl;
        cout<<"==== 用户菜单 ===="<<endl;
        cout<<" 当前用户ID："<<current_aid<<endl;
        cout<<"[1]查询"<<endl;
        cout<<"[2]存款"<<endl;
        cout<<"[3]取款"<<endl;
        cout<<"[4]修改密码"<<endl;
        cout<<"[5]修改信息"<<endl;
        cout<<"[6]销户"<<endl;
        cout<<"[0]退出登录"<<endl;
        cout<<"请输入功能代号：";
        cin>>function;
        if(function==0){
            current_aid = 0;
            break;
        }
        else if(function==1){
            /*查询功能*/
            display();
            continue;
        }
        else if(function==2){
            /*存款功能*/
            deposit();
            continue;
        }
        else if(function==3){
            /*取款功能*/
            withdrawal();
            continue;
        }
        else if(function==4){
            /*修改密码功能*/
            change_password();
            continue;
        }
        else if(function==5){
            /*修改信息功能*/
            change_information();
            continue;
        }
        else if(function==6){
            /*注销账户功能*/
            delete_account();
            break;
        }
        else{
            cout<<"【错误】功能代号不存在，请重试"<<endl;
        }
    }
}

void ATM::login(){
    /*登录验证*/
    int account_id;
    string password;
    cout<<endl<<endl<<endl;
    cout<<"=== 登录 ==="<<endl;
    cout<<"【操作】请输入账号：";
    cin>>account_id;
    if(account_id<0||account_id>=next_aid||accounts[account_id]==nullptr){
        cout<<"【错误】用户不存在"<<endl;
        return;
    }
    cout<<"【操作】请输入密码：";
    cin>>password;
    if(!accounts[account_id]->password_check(password)){
        cout<<"【错误】密码错误"<<endl;
        return;
    }
    /*登录成功*/
    current_aid = account_id;
    if(current_aid==0){
        administrator_mode = true;
        cout<<"【系统】登录成功，当前账户ID：0（管理员）"<<endl;
        administrator_menu();
    }
    else{
        administrator_mode = false;
        cout<<"【系统】登录成功，当前账户ID："<<current_aid<<endl;
        accounts[current_aid]->login_time_add();
        member_menu();
    }
}

void ATM::initialize(){
    /*管理员初始化*/
    string password;
    cout<<"【操作】请设置管理员账户密码：";
    cin>>password;
    Account *accountptr = new Account(0, password);
    accounts[0] = accountptr;
}

void ATM::display() const{
    if(!check_account(current_aid)){
        return;
    }
    else{
        cout<<endl<<endl<<endl;
        cout<<"=== 用户信息 ==="<<endl;
        accounts[current_aid]->information_dispaly();
        accounts[current_aid]->asset_display();
    }
}

void ATM::change_account_id(){
    int account_id;
    cout<<endl<<endl<<endl;
    cout<<"=== 切换客户 ==="<<endl;
    cout<<"【操作】请输入目标账户ID：";
    cin>>account_id;
    if(check_account(account_id)){
        current_aid = account_id;
        cout<<"【系统】已切换至用户ID："<<current_aid<<endl;
    }
}

void ATM::create_account(){
    /*选择账户类型*/
    int type;
    cout<<endl<<endl<<endl;
    cout<<"=== 开户 ==="<<endl;
    cout<<"[1]储蓄卡帐户"<<endl;
    cout<<"[2]信用卡帐户"<<endl;
    cout<<"[3]复合卡账户"<<endl;
    cout<<"[0]返回"<<endl;
    cout<<"【操作】请输入创建账户类型：";
    cin>>type;
    if(type==0){
        return;
    }
    else if(type!=1&&type!=2&&type!=3){
        cout<<"【错误】类型不存在"<<endl;
        return;
    }
    /*开户功能*/
    cout<<"【系统】正在开通账户"<<endl;
    int account_id = next_aid;
    cout<<"【系统】账号ID："<<account_id<<endl;
    string password;
    cout<<"【操作】请设置密码：";
    cin>>password;
    string name;
    cout<<"【操作】请输入姓名：";
    cin>>name;
    string sex;
    cout<<"【操作】请输入性别：";
    cin>>sex;
    string address;
    cout<<"【操作】请输入地址：";
    cin>>address;
    string telephone;
    cout<<"【操作】请输入电话号码：";
    cin>>telephone;
    string card_id;
    cout<<"【操作】请输入身份证号：";
    cin>>card_id;
    if(type==1){
        Account *accountptr = new Debit(account_id, password, name, sex, address, telephone, card_id);
        accounts[account_id] = accountptr;
    }
    else if(type==2){
        Account *accountptr = new Credit(account_id, password, name, sex, address, telephone, card_id);
        accounts[account_id] = accountptr;
    }
    else if(type==3){
        Account *accountptr = new CompCard(account_id, password, name, sex, address, telephone, card_id);
        accounts[account_id] = accountptr;
    }
    accounts[account_id]->asset_display();
    next_aid++;
}

void ATM::delete_account(){
    if(current_aid!=0){
        cout<<endl<<endl<<endl;
        cout<<"=== 销户 ==="<<endl;
        cout<<" 注销用户ID："<<current_aid<<endl;
        if(check_function()){
            cout<<"【系统】正在注销账户"<<endl;
            delete accounts[current_aid];
            accounts[current_aid] = nullptr;
            current_aid = 0;
        }
    }
    else{
        cout<<"【错误】无权限"<<endl;
    }
}

void ATM::deposit(){
    if(current_aid!=0){
        double add;
        cout<<endl<<endl<<endl;
        cout<<"=== 存款 ==="<<endl;
        cout<<"【操作】请输入存款金额：";
        cin>>add;
        if(check_function()){
            accounts[current_aid]->deposit(add);
            accounts[current_aid]->asset_display();
        }
    }
    else{
        cout<<"【错误】无权限"<<endl;
    }
}

void ATM::withdrawal(){
    if(current_aid!=0){
        double reduce;
        cout<<endl<<endl<<endl;
        cout<<"=== 取款 ==="<<endl;
        cout<<"【操作】请输入取款金额：";
        cin>>reduce;
        if(check_function()){
            accounts[current_aid]->withdrawal(reduce);
            accounts[current_aid]->asset_display();
        }
    }
    else{
        cout<<"【错误】无权限"<<endl;
    }
}

void ATM::change_information(){
    if(current_aid!=0){
        if(administrator_mode){
            int function;
            cout<<endl<<endl<<endl;
            cout<<"=== 修改信息 ==="<<endl;
            cout<<" 当前客户ID："<<current_aid<<endl;
            cout<<"[1]修改姓名"<<endl;
            cout<<"[2]修改性别"<<endl;
            cout<<"[3]修改地址"<<endl;
            cout<<"[4]修改电话号码"<<endl;
            cout<<"[5]修改身份证号"<<endl;
            cout<<"[6]修改账户等级"<<endl;
            cout<<"[7]修改密码"<<endl;
            cout<<"[0]返回菜单"<<endl;
            cout<<"请输入功能代号：";
            cin>>function;
            if(function==0){
                /*返回菜单功能*/
                return;
            }
            else if(function==1){
                /*修改姓名*/
                string name;
                cout<<"【操作】请输入姓名：";
                cin>>name;
                accounts[current_aid]->set_name(name);
                cout<<"【系统】姓名已修改"<<endl;
                return;
            }
            else if(function==2){
                /*修改性别*/
                string sex;
                cout<<"【操作】请输入性别：";
                cin>>sex;
                accounts[current_aid]->set_sex(sex);
                cout<<"【系统】性别已修改"<<endl;
                return;
            }
            else if(function==3){
                /*修改地址*/
                string address;
                cout<<"【操作】请输入地址：";
                cin>>address;
                accounts[current_aid]->set_address(address);
                cout<<"【系统】地址已修改"<<endl;
                return;
            }
            else if(function==4){
                /*修改电话号码*/
                string telephone;
                cout<<"【操作】请输入电话号码：";
                cin>>telephone;
                accounts[current_aid]->set_telephone(telephone);
                cout<<"【系统】电话号码已修改"<<endl;
                return;
            }
            else if(function==5){
                /*修改身份证号*/
                string card_id;
                cout<<"【操作】请输入身份证号：";
                cin>>card_id;
                accounts[current_aid]->set_card_id(card_id);
                cout<<"【系统】身份证号已修改"<<endl;
                return;
            }
            else if(function==6){
                /*修改账户等级*/
                int level; 
                cout<<"【操作】请输入账户等级：";
                cin>>level;
                accounts[current_aid]->set_level(level);
                cout<<"【系统】账户等级已修改"<<endl;
                return;
            }
            else if(function==7){
                /*修改密码*/
                string password;
                cout<<"【操作】请设置密码：";
                cin>>password;
                accounts[current_aid]->set_password(password);
                cout<<"【系统】密码已修改"<<endl;
                return;
            }
            else{
                cout<<"【错误】功能代号不存在，请重试"<<endl;
                return;
            }
        }
        else{
            int function;
            cout<<endl<<endl<<endl;
            cout<<"=== 修改信息 ==="<<endl;
            cout<<" 当前账户ID："<<current_aid<<endl;
            cout<<"[1]修改姓名"<<endl;
            cout<<"[2]修改性别"<<endl;
            cout<<"[3]修改地址"<<endl;
            cout<<"[4]修改电话号码"<<endl;
            cout<<"[5]修改身份证号"<<endl;
            cout<<"[0]返回菜单"<<endl;
            cout<<"请输入功能代号：";
            cin>>function;
            if(function==0){
                /*返回菜单功能*/
                return;
            }
            else if(function==1){
                /*修改姓名*/
                string name;
                cout<<"【操作】请输入姓名：";
                cin>>name;
                accounts[current_aid]->set_name(name);
                cout<<"【系统】姓名已修改"<<endl;
                return;
            }
            else if(function==2){
                /*修改性别*/
                string sex;
                cout<<"【操作】请输入性别：";
                cin>>sex;
                accounts[current_aid]->set_sex(sex);
                cout<<"【系统】性别已修改"<<endl;
                return;
            }
            else if(function==3){
                /*修改地址*/
                string address;
                cout<<"【操作】请输入地址：";
                cin>>address;
                accounts[current_aid]->set_address(address);
                cout<<"【系统】地址已修改"<<endl;
                return;
            }
            else if(function==4){
                /*修改电话号码*/
                string telephone;
                cout<<"【操作】请输入电话号码：";
                cin>>telephone;
                accounts[current_aid]->set_telephone(telephone);
                cout<<"【系统】电话号码已修改"<<endl;
                return;
            }
            else if(function==5){
                /*修改身份证号*/
                string card_id;
                cout<<"【操作】请输入身份证号：";
                cin>>card_id;
                accounts[current_aid]->set_card_id(card_id);
                cout<<"【系统】身份证号已修改"<<endl;
                return;
            }
            else{
                cout<<"【错误】功能代号不存在，请重试"<<endl;
                return;
            }
        }
    }
    else{
        cout<<"【错误】无权限"<<endl;
    }
}

void ATM::change_password(){
    if(administrator_mode){
        cout<<endl<<endl<<endl;
        cout<<"=== 修改密码 ==="<<endl;
        /*密码验证*/
        string old_password;
        cout<<"【操作】请输入原密码：";
        cin>>old_password;
        if(!accounts[0]->password_check(old_password)){
            cout<<"【错误】密码错误"<<endl;
            return;
        }
        /*密码修改*/
        string new_password;
        cout<<"【操作】请输入新密码：";
        cin>>new_password;
        accounts[0]->set_password(new_password);
        cout<<"【操作】密码修改成功"<<endl;
    }
    else{
        cout<<endl<<endl<<endl;
        cout<<"=== 修改密码 ==="<<endl;
        /*密码验证*/
        string old_password;
        cout<<"【操作】请输入原密码：";
        cin>>old_password;
        if(!accounts[current_aid]->password_check(old_password)){
            cout<<"【错误】密码错误"<<endl;
            return;
        }
        /*密码修改*/
        string new_password;
        cout<<"【操作】请输入新密码：";
        cin>>new_password;
        accounts[current_aid]->set_password(new_password);
        cout<<"【操作】密码修改成功"<<endl;
    }
}

void ATM::data_display(){
    cout<<endl<<endl<<endl;
    cout<<"=== 全局数据 ==="<<endl;
    cout<<"全局活跃度："<<Account::login_times<<endl;
    cout<<"全局利率："<<Account::rate[0]<<", "<<Account::rate[1]<<", "<<Account::rate[2]<<endl;
    cout<<"全局透支额度："<<Account::limit[0]<<", "<<Account::limit[1]<<", "<<Account::limit[2]<<endl;
}

void ATM::set_rate(){
    int level;
    cout<<endl<<endl<<endl;
    cout<<"=== 设置全局利率 ==="<<endl;
    cout<<"【操作】请输入账户等级：";
    cin>>level;
    if(level<0||level>=3){
        cout<<"【错误】超出等级范围"<<endl;
        return;
    }
    double rate;
    cout<<"【操作】请输入该等级的的全局利率：";
    cin>>rate;
    if(rate<0){
        cout<<"【错误】利率不合法"<<endl;
        return;
    }
    if(check_function()){
        Account::rate[level] = rate;
        cout<<"【操作】全局利率修改成功"<<endl;
    }
}

void ATM::set_limit(){
    int level;
    cout<<endl<<endl<<endl;
    cout<<"=== 设置全局透支额度 ==="<<endl;
    cout<<"【操作】请输入账户等级：";
    cin>>level;
    if(level<0||level>=3){
        cout<<"【错误】超出等级范围"<<endl;
        return;
    }
    double limit;
    cout<<"【操作】请输入该等级的的全局透支额度：";
    cin>>limit;
    if(limit<0){
        cout<<"【错误】透支额度不合法"<<endl;
        return;
    }
    if(check_function()){
        Account::limit[level] = limit;
        cout<<"【操作】全局透支额度修改成功"<<endl;
    }
}

bool ATM::check_function(){
    while(true){
        int check;
        cout<<"[1]确认"<<endl;
        cout<<"[0]返回"<<endl;
        cout<<"【操作】请输入功能代号：";
        cin>>check;
        if(check==0){
            return false;
        }
        else if(check==1){
            return true;
        }
        else{
            cout<<"【错误】功能代号不存在，请重试"<<endl;
            continue;
        }
    }
}

bool ATM::check_account(int account_id) const{
    if(account_id<0||account_id>=next_aid||accounts[account_id]==nullptr){
        cout<<"【错误】用户不存在"<<endl;
        return false;
    }
    if(account_id==0){
        cout<<"【错误】无权限"<<endl;
        return false;
    }
    return true;
}