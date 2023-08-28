#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <userInfo.h>
#include <home.h>
#include <client.h>
#include <QMessageBox>

extern userInfo user;
extern userInfo otherUser;
extern bool is_open_chatdialog;
extern QString hostip;
extern int hostport;

chatdialog::chatdialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chatdialog)
{
    ui->setupUi(this);
    ui->friendName->setText(otherUser.name);
    is_open_chatdialog = true;
    tcpSocket = new QTcpSocket();
    timer = new QTimer();

    qDebug()<<otherUser.id<<otherUser.name;
    connect(timer,SIGNAL(timeout()),this,SLOT(getchathistory()));
    timer->start(500);
}

void chatdialog::closeEvent(QCloseEvent *event){
    is_open_chatdialog = false;
    timer->stop();
}
chatdialog::~chatdialog()
{
    is_open_chatdialog = false;
    timer->stop();
    delete ui;
}

void chatdialog::on_backBtn_clicked()
{
    is_open_chatdialog = false;
    this->close();
    timer->stop();
}


void chatdialog::getchathistory(){
    // 连接到服务器
    tcpSocket->abort();
    tcpSocket->connectToHost(hostip, hostport);
    if(!tcpSocket->waitForConnected(10000))
    {
        QMessageBox::warning(this, "Warning!", "服务器连接失败", QMessageBox::Yes);
        this->close();
        return;
    }

    QString msg = QString("chat_history##%1##%2").arg(user.id).arg(otherUser.id);
    tcpSocket->write(msg.toUtf8());
    tcpSocket->flush();
    connect(tcpSocket,&QTcpSocket::readyRead,[=](){
        QByteArray buffer = tcpSocket->readAll();
        if(QString(buffer).section("##",0,0)==QString("chat_history_error")){
            ui->textBrowser->setText("无消息记录");
        } else if(QString(buffer).section("##",0,0)==QString("chat_history_ok")){
            QString chatStr = "";
            int num = QString(buffer).section("##",1,1).toInt();
            for(int i=0; i<num; ++i){
                QDateTime time = QDateTime::fromString( QString(buffer).section("##",i*3+2,i*3+2),"yyyy-MM-dd hh:mm:ss.zzz"); // 年份、月份、日期、小时、分钟、秒和毫秒
                qDebug()<<time.toString();
                QString timeStr = time.toString("MM-dd hh:mm:ss"); // 显示的时候换一下格式(月份、日期、小时、分钟和秒)
                qDebug()<<timeStr;

                QString idStr = (QString(buffer).section("##", i*3+3, i*3+3).toInt()==user.id) ? "我" : otherUser.name;
                chatStr = idStr + "：" + QString(buffer).section("##", i*3+4, i*3+4) + "（" + timeStr + "）\n" + chatStr;
            }
            ui->textBrowser->setText(chatStr);
        }
    });
}

void chatdialog::on_sendMsgBtn_clicked()
{
    QString message = ui->lineEdit->text();
    if(message == ""){
        QMessageBox::warning(this, "Warning!", "不能发送空消息", QMessageBox::Yes);
        return;
    }
    // 连接到服务器
    tcpSocket->abort();
    tcpSocket->connectToHost(hostip, hostport);
    if(!tcpSocket->waitForConnected(10000))
    {
        QMessageBox::warning(this, "Warning!", "服务器连接失败", QMessageBox::Yes);
        this->close();
        user.isLogin = false;
        client *cli = new client();
        cli->show();
        return;
    }

    QString now = QDateTime::currentDateTime().currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    // 时间，发送id，接受id，内容
    QString msg = QString("chat_send##%1##%2##%3##%4").arg(now).arg(user.id).arg(otherUser.id).arg(message);
    tcpSocket->write(msg.toUtf8());
    tcpSocket->flush();
    ui->lineEdit->clear();  // 清空编辑框
}
