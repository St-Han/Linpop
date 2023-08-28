#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <userInfo.h>
#include <client.h>
#include <QMessageBox>

extern userInfo user;
extern QString hostip;
extern int hostport;

registerdialog::registerdialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registerdialog)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket();
}

registerdialog::~registerdialog()
{
    delete ui;
}

void registerdialog::back_to_login()
{
    this->close();
    user.isLogin = false;
    client *cli = new client();
    cli->show();
}
void registerdialog::on_backBtn_clicked() // 回到登录页面
{
    back_to_login();
}

void registerdialog::on_goToHomeBtn_clicked()
{
    QString name = ui->lineEdit_name->text();
    QString passWord = ui->lineEdit_password->text();
    QString passWord2 = ui->lineEdit_password_2->text();
    if(name.count() == 0 || passWord.count() == 0 || passWord2.count() == 0){
        QMessageBox::warning(this, "Warning!", "用户名或密码不为空", QMessageBox::Yes);
        ui->lineEdit_name->clear();
        ui->lineEdit_password->clear();
        ui->lineEdit_password_2->clear();
        ui->lineEdit_name->setFocus();
        return;
    }
    if(passWord != passWord2){
        QMessageBox::warning(this, "Warning!", "两次密码不一致", QMessageBox::Yes);
        ui->lineEdit_password->clear();
        ui->lineEdit_password_2->clear();
        ui->lineEdit_password->setFocus();
        return;
    }
    // 连接到服务器
    tcpSocket->abort();
    tcpSocket->connectToHost(hostip, hostport);
    // 连接失败，返回上一级页面
    if(!tcpSocket->waitForConnected(10000))
    {
        QMessageBox::warning(this, "Warning!", "服务器连接失败", QMessageBox::Yes);
        back_to_login();
        return;
    }

    // 连接成功，向服务器发送信息
    QString msg = QString("register##%1##%2").arg(name).arg(passWord);
    tcpSocket->write(msg.toUtf8());
    tcpSocket->flush();
    // 接收服务器反馈的信息
    connect(tcpSocket, &QTcpSocket::readyRead, [=]()
    {
        QByteArray buffer = tcpSocket->readAll();
        if(QString(buffer).section("##",0,0)==QString("register_error"))
        {
            if(QString(buffer).section("##",1,1)==QString("same_name"))
            {
                QMessageBox::warning(this, "Warning!", "昵称有重复", QMessageBox::Yes);
                ui->lineEdit_name->clear();
                ui->lineEdit_name->setFocus();
            }
        } else if(QString(buffer).section("##",0,0)==QString("register_success")){
            // 注册成功
            this->close();
            client *cli = new client();
            cli->show();
        }
    });
}
