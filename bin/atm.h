//atm.h
#ifndef ATM_H
#define ATM_H

#include "debit.h"
#include "credit.h"
#include "comp_card.h"
using namespace std;

class ATM{
    public:
        ATM();
        ~ATM();
        void run();                         //运行系统
        void administrator_menu();          //管理员菜单
        void member_menu();                 //用户菜单
        void login();                       //账号登录
        void initialize();                  //初始化
        void display() const;               //查询
        void change_account_id();           //切换客户
        void create_account();              //开户
        void delete_account();              //销户
        void deposit();                     //存款
        void withdrawal();                  //取款
        void change_information();          //修改信息
        void change_password();             //修改密码
        void data_display();                //查询全局数据
        void set_rate();                    //设置全局利率
        void set_limit();                   //设置全局透支额度
        bool check_function();              //确认操作
        bool check_account(int) const;      //检查账户合法性
    private:
        bool administrator_mode;            //管理员模式
        Account *accounts[10000];           //账户指针数组
        int current_aid;                    //当前账户
        int next_aid;                       //下个未创建账户
};

#endif