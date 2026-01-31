//account.h
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Account{
    public:
        Account();
        Account(int);
        Account(int, string);
        virtual ~Account();
        void set_password(string);                  //设置密码
        void set_name(string);                      //设置姓名
        void set_sex(string);                       //设置性别
        void set_address(string);                   //设置地址
        void set_telephone(string);                 //设置电话号码
        void set_card_id(string);                   //设置身份证号
        void set_level(int);                        //设置账户等级
        bool password_check(string) const;          //密码验证
        void login_time_add();                      //登录次数增加
        void deposit(double);                       //存款
        virtual void withdrawal(double);            //取款
        void information_dispaly() const;           //信息查询
        virtual void asset_display() const;         //资产查询
        void read_data();                           //读取数据
        void save_data();                           //保存数据
        static double rate[3];                      //全局利率
        static double limit[3];                     //全局透支额度
        static int login_times;                     //全局登录次数
    protected:
        int type;                   //账户类型
        int account_id;             //账号
        string name;                //姓名
        string sex;                 //性别
        string address;             //地址
        string telephone;        //电话号码
        string card_id;          //身份证号
        double balance;             //账户余额
        int login_time;             //登录次数
        int level;                  //账户等级
    private:
        string password;            //密码
};

#endif