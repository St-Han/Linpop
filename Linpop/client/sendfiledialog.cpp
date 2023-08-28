#include "sendfiledialog.h"
#include "ui_sendfiledialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <userInfo.h>

extern bool is_open_chatdialog;
extern userInfo user;
extern userInfo otherUser;
extern QString hostip;
extern int hostport;

sendfiledialog::sendfiledialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sendfiledialog)
{
    ui->setupUi(this);
    is_open_chatdialog = true;
    connect(&timer,&QTimer::timeout,[=](){
        //关闭定时器
        timer.stop();
        //发送文件
        sendData();
    });

    ui->friendName->setText(otherUser.name);

    tcpSocket = new QTcpSocket();

    int sendport = 9988;    // 开放9988端口用于接受端连接
    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any,sendport);

    connect(tcpServer,&QTcpServer::newConnection,[=](){
        tcpSocket = tcpServer->nextPendingConnection();
//        QString ip = tcpSocket->peerAddress().toString().section(":",3,3);
//        QString showMessage = ip + "已连接";
        ui->sendFileBtn->setEnabled(true);
        connect(tcpSocket,&QTcpSocket::readyRead,[=](){
            QByteArray buffer = tcpSocket->readAll();
            //qDebug()<<buffer;
            if("send_ok" == QString(buffer)){
                this->close();
            }
        });
    });
    ui->sendFileBtn->setEnabled(false);
}

sendfiledialog::~sendfiledialog()
{
    delete ui;
}
void sendfiledialog::closeEvent(QCloseEvent *event){
    tcpSocket->abort();
    tcpSocket->connectToHost(hostip, hostport);
    if(!tcpSocket->waitForConnected(10000))
    {
        this->close();
        user.isLogin = false;
    } else
    {   // 服务器连接成功
        QString loginMsg = QString("send_file_miss##%1##%2").arg(user.id).arg(otherUser.name);
        qDebug()<<loginMsg;
        tcpSocket->write(loginMsg.toUtf8());
        tcpSocket->flush();
        is_open_chatdialog = false;
    }
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpServer->disconnect();
    tcpServer->close();

}

void sendfiledialog::sendData()
{
    quint64 len = 0;
    do
    {
        //每次发送数据的大小
        char buf[1024] = {0};
        len = 0;
        //往文件里读数据
        len = file.read(buf,sizeof(buf));
        //发送数据，读多少，发多少
        len = tcpSocket->write(buf,len);
        sendSize += len;
    }
    while(len >0);
    QMessageBox::information(this,"Success:","发送完毕");
    this->close();
}

void sendfiledialog::on_chooseFileBtn_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"选择文件","../");
    // 若文件路径无效
    if(filePath.isEmpty())
    {
        QMessageBox::information(this,"Error: ",filePath+"文件路径无效");
        return;
    }
    fileName.clear();
    fileSize = 0;
    sendSize = 0;
    // 获取文件信息
    QFileInfo info(filePath);
    fileName = info.fileName();
    fileSize = info.size();

    // 指定文件的名称
    file.setFileName(filePath);
    // 以只读方式打开文件
    bool isOK = file.open(QIODevice::ReadOnly);
    if(!isOK)
    {
        QMessageBox::information(this,"Error:","只读方式打开文件失败");
        return;
    } else {
        // 提示打开文件路径
        ui->statusLabel->setText("选择文件成功："+filePath);
        ui->sendFileBtn->setEnabled(false);
    }
}

void sendfiledialog::on_sendFileBtn_clicked()
{
    //先发送文件头信息 文件名##文件大小
    QString head = QString("%1##%2").arg(fileName).arg(fileSize);
    //发送头部信息
    qint64 len = tcpSocket->write(head.toUtf8());
    //判断信息是否发送成功
    if(len > 0)
    {
        //发送文件信息，防止tcp黏包信息，定时器延时
        timer.start(20);
    }
    else
    {
        QMessageBox::information(this,"Error:","头部信息发送失败");
        file.close();
        return;
    }
}
