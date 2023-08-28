#include"home.h"
#include "ui_home.h"
#include <userInfo.h>
#include <client.h>
#include <chatdialog.h>
#include <sendfiledialog.h>
#include <receivefiledialog.h>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>

extern userInfo user;
userInfo otherUser; // 聊天/传文件对象
QList <QString> friendList;
QList <QString> friendIpList;
QList <QString> friendStatusList;   //'1'表示在线
QList <QString> friendSendMsgList;
QList <QString> friendSendFileList;

QString hostip = "10.196.157.1";   // 服务器ip和端口
int hostport = 8888;

bool is_open_chatdialog; // 标记是否打开聊天窗口
int onlineNum = -1;
int listNum = -1;
int sendMsgNum = -1;
int sendFileNum = -1;

home::home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::home)
{
    ui->setupUi(this);
    ui->userName->setText(user.name);

    timer = new QTimer();   // 定时器，每500ms更新列表
    timer->start(500);
    connect(timer,SIGNAL(timeout()),this,SLOT(createFriendList()));

    tcpSocket = new QTcpSocket();
}

void home::createFriendList()
{
    qDebug()<<"createList";
    // 如果打开了聊天窗口，就禁用该页面按钮
    if(is_open_chatdialog){
        ui->goToChatBtn->setEnabled(false);
        ui->sendFileBtn->setEnabled(false);
        ui->receiveFileBtn->setEnabled(false);
    } else {
        ui->goToChatBtn->setEnabled(true);
        ui->sendFileBtn->setEnabled(true);
        ui->receiveFileBtn->setEnabled(true);
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
    QString msg = QString("getfriendlist##%1").arg(user.id);
    tcpSocket->write(msg.toUtf8());
    tcpSocket->flush();
    // 接收服务器反馈的信息
    connect(tcpSocket, &QTcpSocket::readyRead, [=]()
    {
        QByteArray buffer = tcpSocket->readAll();
        QString homeBack = QString(buffer).section("##",0,0);
        if(homeBack == "getfriendlist_error")   // 无法获取朋友列表
        {
            if(listNum != 0){
                listNum = 0;
                ui->friendList->clear();
                ui->friendList->insertItem(0, tr("您没有朋友"));
            }
            ui->goToChatBtn->setEnabled(false);
            ui->sendFileBtn->setEnabled(false);
            ui->receiveFileBtn->setEnabled(false);
            ui->removeFriendBtn->setEnabled(false); // 禁用移除好友按钮
        } else if(homeBack == "getfriendlist_ok"){
            // 获取好友列表成功，获取传递过来的信息
            qDebug()<<QString(buffer);
            int newListNum = QString(buffer).section("##",1,1).toInt();
            int newOnlineNum = QString(buffer).section("##",2,2).toInt();
            int newSendMsgNum = QString(buffer).section("##",3,3).toInt();
            int newSendFileNum = QString(buffer).section("##",4,4).toInt();
            qDebug()<<"现在的"<<listNum<<onlineNum<<sendMsgNum<<sendFileNum;
            qDebug()<<newListNum<<newOnlineNum<<newSendMsgNum<<newSendFileNum;

            if(listNum == -1 || onlineNum == -1 || sendMsgNum == -1 || sendFileNum == -1 ||
            listNum != newListNum || onlineNum != newOnlineNum || sendMsgNum != newSendMsgNum || sendFileNum != newSendFileNum) // 若需要更新列表
            {
                qDebug()<<"更新列表";
                listNum = newListNum;
                onlineNum = newOnlineNum;
                sendMsgNum = newSendMsgNum;
                sendFileNum = newSendFileNum;

                ui->friendList->clear();    // 清除原有列表，再重新构建
                friendList.clear();
                friendIpList.clear();
                friendStatusList.clear();
                friendSendMsgList.clear();
                friendSendFileList.clear();

                for(int i=0; i<newListNum; ++i){ // 依次处理各个好友的状态
                    // 处理从服务器得到的好友信息
                    QString friendName = QString(buffer).section("##", 5+i*5, 5+i*5);
                    QString friendStatus = QString(buffer).section("##", 6+i*5, 6+i*5);
                    QString friendIp = QString(buffer).section("##", 7+i*5, 7+i*5);
                    QString friendSendMsg = QString(buffer).section("##", 8+i*5, 8+i*5);
                    QString friendSendFile = QString(buffer).section("##", 9+i*5, 9+i*5);
                    friendList.append(friendName);
                    friendStatusList.append(friendStatus);
                    friendIpList.append(friendIp);
                    friendSendMsgList.append(friendSendMsg);
                    friendSendFileList.append(friendSendFile);

                    QString friendInfo = "";
                    if(friendStatus == '1')
                        friendInfo.append("在线");
                    else
                        friendInfo.append("不在线");
                    if(friendSendMsg == '1') friendInfo.append("，有新消息");
                    if(friendSendFile == '1') friendInfo.append("，想给您发文件");

                    ui->friendList->insertItem(i, tr( (friendName + "("+friendInfo+")").toUtf8() ) ); //tr():对这个字符串进行本地化处理，并返回翻译后的结果
                }

                // 设置按钮状态
                ui->removeFriendBtn->setEnabled(true);
                if(!is_open_chatdialog)
                {
                    ui->goToChatBtn->setEnabled(true);
                    ui->sendFileBtn->setEnabled(true);
                    ui->receiveFileBtn->setEnabled(true);
                }
            }
        }
    });
}

// 重写关闭事件 关闭时向服务器发出下线信息并弹出下线提示
void home::closeEvent(QCloseEvent *event)
{
    timer->stop();
    // 连接到服务器
    tcpSocket->abort();
    tcpSocket->connectToHost(hostip, hostport);
    if(!tcpSocket->waitForConnected(10000))
    {
        this->close();
        user.isLogin = false;
        return;
    }
    QString msg = QString("logout##%1").arg(user.id);
    tcpSocket->write(msg.toUtf8());
    tcpSocket->flush();
    QMessageBox::warning(this, "Success", "下线成功", QMessageBox::Yes);
}
home::~home()
{
    timer->stop();
    delete ui;
}

void home::back_to_login()
{
    this->close();
    user.isLogin = false;
    client *cli = new client();
    cli->show();
}
void home::on_backBtn_clicked()         // 返回按钮，退出登录，返回上一级页面
{
    back_to_login();
}
void home::on_refreshBtn_clicked()      // 刷新列表
{
    listNum = -1;
    onlineNum = -1;
    sendMsgNum = -1;
    sendFileNum = -1;
}

void home::on_goToChatBtn_clicked()     // 聊天按钮
{
    int cur = ui->friendList->currentRow();
    if(cur == -1){
        QMessageBox::warning(this, "Warning!", "您未选择联系人", QMessageBox::Yes);
        return;
    }

    // 连接到服务器
    tcpSocket = new QTcpSocket();
    tcpSocket->abort();
    tcpSocket->connectToHost(hostip, hostport);
    if(!tcpSocket->waitForConnected(10000))
    {
        QMessageBox::warning(this, "Warning!", "服务器连接失败", QMessageBox::Yes);
        back_to_login();
        return;
    }
    // 连接成功，向服务器发送信息
    QString friendName = friendList.at(cur);
    QString msg = QString("wantsendmessage##%1##%2").arg(user.id).arg(friendName);
    tcpSocket->write(msg.toUtf8());
    tcpSocket->flush();
    qDebug()<<"want send msg write ok";
    // 接收服务器反馈的信息
    connect(tcpSocket, &QTcpSocket::readyRead, [=](){
        QByteArray buffer = tcpSocket->readAll();
        qDebug()<<QString(buffer);
        if( QString(buffer).section("##",0,0) == QString("wantsendmessage_ok"))
        {   // 查有此人，可以发消息
            qDebug()<<"want send msg ok";
            otherUser.id = QString(buffer).section("##",1,1).toInt();
            otherUser.name = friendName;
            // 开启新的聊天页面并禁用聊天按钮
            ui->goToChatBtn->setEnabled(false);
            chatdialog *cht = new chatdialog();
            cht->show();
        }
    });
}

void home::on_addFriendBtn_clicked()    // 添加好友按钮
{
    bool ok;    // 弹出输入好友昵称的窗口
    QString addFriendName = QInputDialog::getText(this, tr("添加好友"), tr("输入对方昵称"), QLineEdit::Normal, 0, &ok);
    if(ok && !addFriendName.isEmpty()){
        qDebug()<<"add friend";
        if(addFriendName == user.name){
            QMessageBox::warning(this, "Warning!", "不能添加自己", QMessageBox::Yes);
            return;
        }
        // 连接到服务器
        tcpSocket->abort();
        tcpSocket->connectToHost(hostip, hostport);
        if(!tcpSocket->waitForConnected(10000))
        {
            QMessageBox::warning(this, "Warning!", "服务器连接失败", QMessageBox::Yes);
            back_to_login();
            return;
        }
        // 连接成功，向服务器发送信息
        QString msg = QString("add_friend##%1##%2").arg(user.id).arg(addFriendName);
        tcpSocket->write(msg.toUtf8());
        tcpSocket->flush();
        // 接收服务器反馈的信息
        connect(tcpSocket, &QTcpSocket::readyRead, [=]()
        {
            QByteArray buffer = tcpSocket->readAll();
            if( QString(buffer).section("##",0,0) == QString("add_friend_error")){
                QMessageBox::warning(this, "Warning!", "查无此人", QMessageBox::Yes);
            } else if( QString(buffer).section("##",0,0) == QString("add_friend_ok") ){
                qDebug()<<"add friend success";
                onlineNum = -1; // 加好友
            }
        });
    }
}

void home::on_removeFriendBtn_clicked() // 删除好友按钮
{
    int cur = ui->friendList->currentRow();
    if(cur == -1){
        QMessageBox::warning(this, "Warning!", "您未选择联系人", QMessageBox::Yes);
        return;
    }

    QString friendName = friendList.at(cur);
    // 弹出提示框 若点击“确定”
    if (QMessageBox::question(this, "提示", "确定要删除好友：" + friendName + "？", QMessageBox::Yes | QMessageBox::Cancel) == QMessageBox::Yes) {
        // 连接到服务器
        tcpSocket->abort();
        tcpSocket->connectToHost(hostip, hostport);
        if(!tcpSocket->waitForConnected(10000))
        {
            QMessageBox::warning(this, "Warning!", "服务器连接失败", QMessageBox::Yes);
            back_to_login();
            return;
        }
        // 连接成功，向服务器发送信息
        QString msg = QString("delete_friend##%1##%2").arg(user.id).arg(friendName);
        tcpSocket->write(msg.toUtf8());
        tcpSocket->flush();
        // 接收服务器反馈的信息
        connect(tcpSocket, &QTcpSocket::readyRead, [=]()
        {
            QByteArray buffer = tcpSocket->readAll();
            if( QString(buffer).section("##",0,0) == QString("delete_friend_ok"))
                createFriendList(); // 删除成功，重建列表
        });
    }
}


void home::on_sendFileBtn_clicked()     // 发送文件按钮
{
    int cur = ui->friendList->currentRow();
    if(cur == -1){
        QMessageBox::warning(this, "Warning!", "您未选择联系人", QMessageBox::Yes);
        return;
    }

    if(friendStatusList.at(cur) != "1")
        QMessageBox::warning(this, "Warning!", "好友不在线,无法发送文件", QMessageBox::Yes);
    else{
        QString friendName = friendList.at(cur);
        otherUser.name = friendName;
        otherUser.ip = friendIpList.at(cur);

        // 连接到服务器
        tcpSocket->abort();
        tcpSocket->connectToHost(hostip, hostport);
        if(!tcpSocket->waitForConnected(10000))
        {
            QMessageBox::warning(this, "Warning!", "服务器连接失败", QMessageBox::Yes);
            back_to_login();
            return;
        }
        QString msg = QString("want_send_file##%1##%2").arg(user.id).arg(friendName);
        tcpSocket->write(msg.toUtf8());
        tcpSocket->flush();

        sendfiledialog *sf = new sendfiledialog(); // 打开发送文件界面
        sf->show();
    }
}

void home::on_receiveFileBtn_clicked()      // 接收文件按钮
{
    int cur = ui->friendList->currentRow();
    if(cur == -1){
        QMessageBox::warning(this, "Warning!", "您未选择联系人", QMessageBox::Yes);
        return;
    }

    if(friendSendFileList.at(cur) != "1")
        QMessageBox::warning(this, "Warning!", "该好友未发送文件", QMessageBox::Yes);
    else{
        QString friendName = friendList.at(cur);
        otherUser.name = friendName;
        otherUser.ip = friendIpList.at(cur);

        receivefiledialog *rf = new receivefiledialog();  // 打开接收文件界面
        rf->show();
    }
}
