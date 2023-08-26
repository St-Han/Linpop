#include "client.h"
#include "ui_client.h"
#include <QMessageBox>

extern userInfo user;
QString hostip; // extern
int hostport;   // extern

client::client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::client)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket();
}

client::~client()
{
    delete tcpSocket;
    delete ui;
}

void client::on_btn_goToRegister_clicked()
{
    this->close();
//    registerdialog *reg = new registerdialog();
//    reg->show();
}

void client::on_btn_goToHome_clicked()
{
    bool checkLogin = check_login();
    if(checkLogin){
        this->close();
//        home *hom = new home();
//        hom->show();
    }
}

bool client::check_login(){
    QString loginName = ui->lineEdit_loginName->text();
    QString passWord = ui->lineEdit_password->text();
    if(loginName.count() == 0 || passWord.count() == 0){
        QMessageBox::warning(this, "Warning!", "用户名或密码不为空", QMessageBox::Yes);
        return false;
    }

    tcpSocket->abort();//断开已有的连接
    tcpSocket->connectToHost(hostip, hostport); // 连接服务器
    if(!tcpSocket->waitForConnected(30000)){
        QMessageBox::warning(this, "Warning!", "服务器连接失败", QMessageBox::Yes);
        return false;
    }
    // 服务器连接成功
    QString loginMsg = QString("login##%1##%2").arg(loginName).arg(passWord); //.arg():单个逐个替换
    // 把登录信息发给服务器 以##分隔标识信息
    tcpSocket->write(loginMsg.toUtf8());
    tcpSocket->flush(); // 清理缓存
    // 接收服务器反馈的信息
    connect(tcpSocket, &QTcpSocket::readyRead, [=]()
    {
        QByteArray buffer = tcpSocket->readAll();
        QString loginBack = QString(buffer).section("##",0,0);
        //section分割 QChar sep, int start, int end = -1, SectionFlags flags = SectionDefault
        if(loginBack == "login_error"){
            QString loginError = QString(buffer).section("##",1,1);
            if(loginError == "no_user"){
                QMessageBox::warning(this, "Warning!", "用户不存在", QMessageBox::Yes);
                // 用户不存在 清除输入框
                ui->lineEdit_loginName->clear();
                ui->lineEdit_password->clear();
                ui->lineEdit_loginName->setFocus();
            }else if(loginError == "wrong_password"){
                QMessageBox::warning(this, "Warning!", "密码错误", QMessageBox::Yes);
                // 密码错误 清除密码
                ui->lineEdit_password->clear();
                ui->lineEdit_password->setFocus();
            }
            return false;
        }else if(loginBack == "login_success"){
            // 登录成功 记录用户信息
            user.id = QString(buffer).section("##",1,1).toInt();
            user.name = ui->lineEdit_loginName->text();
            user.isLogin = true;
            return true;
        }
    });
    return false;
}
/*
        QString ip = tcpSocket->peerAddress().toString().section(":",3,3);
        int port = tcpSocket->peerPort();
        QString str = QString("[%1:%2]").arg(ip).arg(port);
        qDebug() << str ;
*/
