#ifndef USERINFO_H
#define USERINFO_H

#include<QString>

class userInfo{
public:             // public 方便编辑
    int id;
    QString name;
    bool isLogin; // 表示是否登录
    QString ip;
    int port;

    userInfo();
};

/*
   int id;
   QString name;
   bool islogin;//true在线
   QString ip;
   int port;

   userinfo(int id_,QString name_);
   userinfo();
*/
#endif // USERINFO_H
