#include "server.h"
#include "ui_server.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>

int currentsize;

QString ip;
int port;

server::server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::server)
{
    ui->setupUi(this);
    // 设置UI界面

    tcpServer = new QTcpServer();
    // 创建QTcpServer对象用于处理客户端的连接请求

    ui->listWidget->clear();
    // 清空listWidget
    ui->listWidget->insertItem(0, tr("当前无在线用户"));
    // 在listWidget中插入一条显示文本，表示当前没有在线用户

    for(int i = 0; i < M; i++)
    {
        tcpSocket[i] = new QTcpSocket();
        // 使用循环创建M个QTcpSocket对象
    }

    tcpServer->listen(QHostAddress::Any, 8888);
    // 开始监听来自任意IP地址的8888端口的连接请求

    // 初始化数据库
    db = QSqlDatabase::addDatabase("QSQLITE");
    // 初始化QSqlDatabase对象，数据库驱动设置为SQLite

    // 判断是否创建了用户表
    db.setDatabaseName("./people.db");
    // 设置数据库名称为"./people.db"
    db.open();
    // 打开数据库连接

    QSqlQuery sqlquery;
    sqlquery.exec("CREATE TABLE if not exists people (id INTEGER NOT NULL UNIQUE, name TEXT NOT NULL UNIQUE, password TEXT NOT NULL, ip TEXT, islogin INTEGER NOT NULL, PRIMARY KEY(id AUTOINCREMENT))");
    // 执行SQL语句创建名为"people"的表，包括id、name、password、ip和islogin字段，id字段为主键

    db.close();
    // 关闭数据库连接

    connect(tcpServer,&QTcpServer::newConnection,[=]()
    {
        tcpSocket[0] = tcpServer->nextPendingConnection();
        currentsize++;
        ip = tcpSocket[0]->peerAddress().toString().section(":",3,3);
        port = tcpSocket[0]->peerPort();
        // 预留currentsize以用作多用户同时连接所用
        QString str = QString("[%1:%2]").arg(ip).arg(port);
        qDebug() << str ;

        connect(tcpSocket[0],&QTcpSocket::readyRead,[=]()
        {
            //读取缓冲区数据
            QByteArray buffer = tcpSocket[0]->readAll();
            QString action = QString(buffer).section("##",0,0);

            if("login" == action)               // 登录
                login(buffer);
            else if("register" == action)       // 注册
                registerUser(buffer);
            else if("wantsendmessage" == action)// 想发信息，检查发消息对象是否存在
                wantSendMsg(buffer);
            else if("chat_history" == action)   // 聊天记录
                chatHistory(buffer);
            else if("chat_send" == action)      // 发送信息
                chatSend(buffer);
            else if("logout" == action)         // 用户下线
                logout(buffer);
            else if("getfriendlist" == action)  // 获取好友列表
                getFriendList(buffer);
            else if ("add_friend" == action)    // 添加好友
                addFriend(buffer);
            else if ("delete_friend" == action) // 删除好友
                deleteFriend(buffer);
            else if ("want_send_file" == action)// home传过来的信息，提示好友将要发送文件
                wantSendFile(buffer);
            else if ("send_file_ok" == action)  // 接收文件方准备好了
                sendFileOk(buffer);
            else if ("send_file_miss" == action)// 发送文件方窗口关闭
                sendFileMiss(buffer);
        });
    });
}

server::~server()
{
    tcpServer->close();
    // 关闭服务器的TCP连接
    tcpServer->deleteLater();
    // 在稍后的事件循环中删除服务器的TCP连接对象
    delete ui;
    // 删除界面对象
}

void server::login(QByteArray buffer)   // 登录
{
    db.setDatabaseName("./people.db");
    db.open();
    QSqlQuery sqlquery;
    sqlquery.prepare("select * from people where name = :name");
    sqlquery.bindValue(":name",QString(buffer).section("##",1,1));
    sqlquery.exec();
    if(!sqlquery.next())
    {   // 未查找到该用户
        tcpSocket[0]->write(QString("login_error##no_user").toUtf8());
        tcpSocket[0]->flush();
        db.close();
        return;
    }
    // 用户存在
    int id = sqlquery.value(0).toInt();
    QString pwd = sqlquery.value(2).toString();
    if(pwd != QString(buffer).section("##",2,2))
    {   // 密码错误
        tcpSocket[0]->write(QString("login_error##wrong_password").toUtf8());
        tcpSocket[0]->flush();
        db.close();
        return;
    }
    // 登录成功
    tcpSocket[0]->write(QString("login_success##%1").arg(id).toUtf8());
    sqlquery.prepare("update people set ip=:ip, islogin=1 where name = :name");
    sqlquery.bindValue(":ip",ip);
    sqlquery.bindValue(":name",QString(buffer).section("##",1,1));
    sqlquery.exec();
    tcpSocket[0]->flush();

    // 更新服务器界面
    ui->listWidget->clear();
    sqlquery.prepare("select * from people where islogin = 1");
    sqlquery.exec();
    if(sqlquery.next())
    {
        QString userid = sqlquery.value(0).toString();
        QString username = sqlquery.value(1).toString();
        QString userip = sqlquery.value(3).toString();
        //qDebug()<<userid;
        ui->listWidget->insertItem(0,"用户ID："+userid+",用户昵称:"+username+",用户IP:"+userip);
        int i = 1;
        while (sqlquery.next())
        {
            QString userid = sqlquery.value(0).toString();
            QString username = sqlquery.value(1).toString();
            QString userip = sqlquery.value(3).toString();
            ui->listWidget->insertItem(i,"用户ID："+userid+",用户昵称:"+username+",用户IP:"+userip);
            i++;
        }
    }
    else
    {
        ui->listWidget->clear();
        ui->listWidget->insertItem(0,tr("当前无在线用户"));
    }
}

void server::registerUser(QByteArray buffer){   // 注册
    db.setDatabaseName("./people.db");
    db.open();
    QSqlQuery sqlquery;
    // 注册用户的时候需要进行判重
    sqlquery.prepare("select * from people where name = :name");
    sqlquery.bindValue(":name",QString(buffer).section("##",1,1));
    sqlquery.exec();
    if(!sqlquery.next())
    {   // 可以新建
        sqlquery.clear();
        sqlquery.prepare("insert into people values (null,:name,:password,null,0)");
        sqlquery.bindValue(":name",QString(buffer).section("##",1,1));
        sqlquery.bindValue(":password",QString(buffer).section("##",2,2));
        sqlquery.exec();

        sqlquery.clear();
        sqlquery.prepare("select * from people where name = :name");
        sqlquery.bindValue(":name",QString(buffer).section("##",1,1));
        sqlquery.exec();//获得新建的用户的id
        sqlquery.next();
        int newid = sqlquery.value(0).toInt();
        sqlquery.exec("create table if not exists friend__" + QString::number(newid) +"(id INTEGER unique, name TEXT,sendmassage INTEGER,sendfile INTEGER)");

        tcpSocket[0]->write(QString("register_success").toUtf8());
        tcpSocket[0]->flush();
        db.close();
    }
    else
    {   // 有重名
         tcpSocket[0]->write(QString("register_error##same_name").toUtf8());
         tcpSocket[0]->flush();
         db.close();
    }
}

void server::wantSendMsg(QByteArray buffer)
{
    db.setDatabaseName("./people.db");
    db.open();
    QSqlQuery sqlquery;
    sqlquery.prepare("select * from people where name = :name");
    sqlquery.bindValue(":name",QString(buffer).section("##",2,2));
    sqlquery.exec();
    qDebug()<<"send msg check";
    if(sqlquery.next())
    {   // 有这个人在，可以发消息
        qDebug()<<"send msg check ok";
        int otherid = sqlquery.value(0).toInt();
        qDebug()<<otherid;
        tcpSocket[0]->write(QString("wantsendmessage_ok##%1").arg(otherid).toUtf8());
        qDebug()<<"send msg check write ok";
        tcpSocket[0]->flush();

        // 发消息前把数据库准备好
        int thisid = QString(buffer).section("##",1,1).toInt();
        if(thisid < otherid)
        {
            sqlquery.exec("CREATE TABLE if not exists chat__" + QString::number(thisid) + "__" + QString::number(otherid) + "(time datetime NOT NULL UNIQUE,id INTEGER,message TEXT, PRIMARY KEY(time))");
        }
        else
        {
            sqlquery.exec("CREATE TABLE if not exists chat__" + QString::number(otherid) + "__" + QString::number(thisid) + "(time datetime NOT NULL UNIQUE,id INTEGER,message TEXT, PRIMARY KEY(time))");
        }

        db.close();
    }
    else
    {   // 查无此人，无法对话
        tcpSocket[0]->write(QString("wantsendmessage_error").toUtf8());
        tcpSocket[0]->flush();
        db.close();
    }
}

void server::chatHistory(QByteArray buffer) // 聊天记录 idone->idtwo, one是发信息方，已经阅览了two的所有消息
{
    int idone = QString(buffer).section("##", 1, 1).toInt();
    // 解析buffer中第一个"##"之间的字符串，并转换为整数赋值给idone变量
    int idtwo = QString(buffer).section("##", 2, 2).toInt();
    // 解析buffer中第二个"##"之间的字符串，并转换为整数赋值给idtwo变量

    db.setDatabaseName("./people.db");  // 设置数据库名称为"./people.db"
    db.open();  // 打开数据库连接

    QSqlQuery sqlquery; // 创建QSqlQuery对象
    QString sqlstring = ""; // 初始化sqlstring变量为空字符串

    if (idone < idtwo){
        sqlstring = "select * from chat__" + QString::number(idone) + "__" + QString::number(idtwo) + " order by time desc limit 20";
        // 如果idone小于idtwo，构建查询语句，选择chat__idone__idtwo表中的所有行，按照时间降序排列，限制20条记录
    } else {
        sqlstring = "select * from chat__" + QString::number(idtwo) + "__" + QString::number(idone) + " order by time desc limit 20";
        // 如果idone大于等于idtwo，构建查询语句，选择chat__idtwo__idone表中的所有行，按照时间降序排列，限制20条记录
    }
    qDebug() << sqlstring; // 在调试输出中打印sqlstring的值
    sqlquery.exec(sqlstring);
    // 执行查询语句

    if(sqlquery.next())
    // 如果sqlquery有下一行记录
    {
        QString history = "##" + sqlquery.value(0).toDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz")+ "##" + sqlquery.value(1).toString()+ "##" + sqlquery.value(2).toString();
        // 以特定格式构建字符串history，包括日期时间、值1和值2
        int hisnum = 1;
        // 初始化计数器hisnum为1
        while(sqlquery.next())
        // 遍历sqlquery的剩余记录
        {
            hisnum++; // 计数器加1
            QDateTime time = sqlquery.value(0).toDateTime();
            // 获取日期时间值
            QString timestr = time.toString("yyyy-MM-dd hh:mm:ss.zzz");
            // 将日期时间值转为字符串
            history = history + "##" + timestr;
            // 将日期时间追加到history字符串中
            history = history + "##" + sqlquery.value(1).toString();
            // 追加值1到history字符串中
            history = history + "##" + sqlquery.value(2).toString();
            // 追加值2到history字符串中
        }
        history = "chat_history_ok##" + QString::number(hisnum) + history;
        // 将计数器和history字符串拼接为完整的历史记录字符串
        tcpSocket[0]->write(history.toUtf8());
        // 将历史记录字符串以UTF-8编码写入tcpSocket
        tcpSocket[0]->flush();
        // 刷新tcpSocket的缓冲区

        QString sqlstring = "update friend__" + QString::number(idone) + " set sendmassage = 0 where id = :id";
        // 构建更新数据库的SQL语句
        db.setDatabaseName("./people.db"); // 设置数据库文件名
        db.open(); // 打开数据库连接
        QSqlQuery sqlquery; // 创建一个新的查询对象sqlquery
        sqlquery.prepare(sqlstring); // 准备SQL查询
        sqlquery.bindValue(":id", idtwo);
        // 绑定参数id
        sqlquery.exec();
        // 执行SQL查询
        db.close(); // 关闭数据库连接
    }
    else
    {   // 无历史记录
        tcpSocket[0]->write(QString("chat_history_error").toUtf8());
        tcpSocket[0]->flush();
        db.close();
    }
}

void server::chatSend(QByteArray buffer)
{   //one发消息的，two收消息的
    QDateTime nowstr = QDateTime::fromString(QString(buffer).section("##",1,1), "yyyy-MM-dd hh:mm:ss.zzz");
    // 从buffer中提取日期时间字符串，并根据指定格式转换为QDateTime对象

    int idone = QString(buffer).section("##",2,2).toInt();
    // 从buffer中提取第二个"##"分隔符后的整数，并将其转换为int类型

    int idtwo = QString(buffer).section("##",3,3).toInt();
    // 从buffer中提取第三个"##"分隔符后的整数，并将其转换为int类型

    db.setDatabaseName("./people.db");
    db.open();
    // 设置数据库名称并打开数据库连接

    QSqlQuery sqlquery; // 创建一个SQL查询对象
    QString sqlstring = ""; // 声明一个空字符串用于存储SQL语句
    if(idone < idtwo)
    {
        sqlstring = "insert into chat__" + QString::number(idone) + "__" + QString::number(idtwo) + " values(:time,:id,:message)";
    }
    else
    {
        sqlstring = "insert into chat__" + QString::number(idtwo) + "__" + QString::number(idone) + " values(:time,:id,:message)";
    }
    // 根据idone和idtwo的大小关系构建插入数据的SQL语句
    qDebug()<<sqlstring;
    // 打印SQL语句到调试输出

    sqlquery.prepare(sqlstring);
    sqlquery.bindValue(":time",nowstr);
    sqlquery.bindValue(":id",idone);
    sqlquery.bindValue(":message",QString(buffer).section("##",4,4));
    // 绑定参数的值到SQL查询的占位符

    sqlquery.exec();
    // 执行SQL查询

    sqlstring = "update friend__" + QString::number(idtwo) + " set sendmassage = 1 where id = :id";
    // 构建更新数据的SQL语句

    db.setDatabaseName("./people.db");
    db.open();

    sqlquery.clear();
    sqlquery.prepare(sqlstring);
    sqlquery.bindValue(":id", idone);
    // 绑定参数的值到SQL查询的占位符

    sqlquery.exec();
    // 执行SQL查询

    db.close(); // 关闭数据库连接
}

void server::logout(QByteArray buffer)
{
    db.setDatabaseName("./people.db"); // 设置数据库文件名为 "./people.db"
    db.open();  // 打开数据库连接

    QSqlQuery sqlquery; // 创建 QSqlQuery 对象用于执行数据库查询
    // 准备 SQL 查询语句，更新 "people" 表中 "islogin" 字段为 0，根据传入的id来确定更新的行
    sqlquery.prepare("update people set islogin=0 where id = :id");
    sqlquery.bindValue(":id", QString(buffer).section("##", 1, 1)); // 将传入的 buffer 字符串以 "##" 分割，并取第二个分割结果作为 id
    sqlquery.exec(); // 执行 SQL 查询

    // 清空服务器界面的列表控件
    ui->listWidget->clear();

    // 准备 SQL 查询语句，查询所有 "people" 表中 islogin 字段为 1 的记录
    sqlquery.prepare("select * from people where islogin = 1");
    sqlquery.exec(); // 执行 SQL 查询

    // 如果存在查询结果
    if (sqlquery.next()) {
        // 获取查询结果中的字段值
        QString userid = sqlquery.value(0).toString();
        QString username = sqlquery.value(1).toString();
        QString userip = sqlquery.value(3).toString();

        // 在服务器界面的列表控件中插入第一项，显示用户 ID、昵称和 IP
        ui->listWidget->insertItem(0, "用户ID：" + userid + "，用户昵称：" + username + "，用户IP：" + userip);

        int rownum = 1;
        // 遍历剩余查询结果
        while (sqlquery.next()) {
            // 获取字段值
            QString userid = sqlquery.value(0).toString();
            QString username = sqlquery.value(1).toString();
            QString userip = sqlquery.value(3).toString();

            // 在服务器界面的列表控件中插入新的一行，显示用户 ID、昵称和 IP
            ui->listWidget->insertItem(rownum, "用户ID：" + userid + "，用户昵称：" + username + "，用户IP：" + userip);
            rownum++;
        }
    }
    else {
        // 如果查询结果为空，清空服务器界面的列表控件并插入一行文本
        ui->listWidget->clear();
        ui->listWidget->insertItem(0, tr("当前无在线用户"));
    }
}

void server::getFriendList(QByteArray buffer)
{
    db.setDatabaseName("./people.db");
    db.open(); // 打开数据库连接

    QSqlQuery sqlquery; // 创建 QSqlQuery 对象用于执行数据库查询
    // 使用 exec 函数执行 SQL 查询语句
    // 通过 QString 的 section 函数从 buffer 字符串中提取出 id 的部分，并拼接成完整的 SQL 查询语句
    sqlquery.exec("select * from friend__" + QString(buffer).section("##", 1, 1) + " desc");

    if(sqlquery.next())
    {
        // 创建三个 QList 对象用于存储查询结果
        QList<QString> friendlist;
        QList<QString> friendsendfilelist;
        QList<QString> friendsendmassagelist;

        // 将第一行查询结果的第二列（索引为1）添加到 friendlist 中
        friendlist.append(sqlquery.value(1).toString());

        // 初始化 sendmassagenum 和 sendfilenum 为 0
        int sendmassagenum = 0;
        int sendfilenum = 0;

        // 判断第一行查询结果的第三列（索引为2）是否为'1'，如果是，则 sendmassagenum 加1
        if (sqlquery.value(2).toString() == '1') {
            sendmassagenum++;
        }

        // 将第一行查询结果的第三列（索引为2）添加到 friendsendmassagelist 中
        friendsendmassagelist.append(sqlquery.value(2).toString());

        // 判断第一行查询结果的第四列（索引为3）是否为'1'，如果是，则 sendfilenum 加1
        if (sqlquery.value(3).toString() == '1') {
            sendfilenum++;
        }

        // 将第一行查询结果的第四列（索引为3）添加到 friendsendfilelist 中
        friendsendfilelist.append(sqlquery.value(3).toString());

        // 初始化一个空字符串 friends
        QString friends = "";

        // 循环处理后续的查询结果
        while (sqlquery.next()) {
            // 将当前行查询结果的第二列（索引为1）添加到 friendlist 中
            friendlist.append(sqlquery.value(1).toString());

            // 判断当前行查询结果的第三列（索引为2）是否为'1'，如果是，则 sendmassagenum 加1
            if (sqlquery.value(2).toString() == '1') {
                sendmassagenum++;
            }

            // 将当前行查询结果的第三列（索引为2）添加到 friendsendmassagelist 中
            friendsendmassagelist.append(sqlquery.value(2).toString());

            // 判断当前行查询结果的第四列（索引为3）是否为'1'，如果是，则 sendfilenum 加1
            if (sqlquery.value(3).toString() == '1') {
                sendfilenum++;
            }

            // 将当前行查询结果的第四列（索引为3）添加到 friendsendfilelist 中
            friendsendfilelist.append(sqlquery.value(3).toString());
        }

        // 初始化在线好友数量为 0
        int onlinefriendnum = 0;

        // 遍历 friendlist 中的每个好友
        for (int i = 0; i < friendlist.length(); i++) {
            // 准备查询语句，并使用当前好友名字进行绑定
            sqlquery.prepare("select * from people where name = :name");
            sqlquery.bindValue(":name", friendlist.at(i));
            sqlquery.exec();
            sqlquery.next();

            // 获取查询结果中第三列（索引为3）的值，即好友的 IP 地址
            QString peopleip = sqlquery.value(3).toString();

            // 判断查询结果中第四列（索引为4）是否为 1，即好友的在线状态
            if (sqlquery.value(4).toInt() == 1) {
                // 在线状态，将好友信息拼接到 friends 字符串中
                onlinefriendnum++;
                friends = "##" + friendlist.at(i) + "##1##" + peopleip + "##" + friendsendmassagelist.at(i) + "##" + friendsendfilelist.at(i) + friends;
            } else {
                // 不在线状态，将好友信息拼接到 friends 字符串中
                friends = "##" + friendlist.at(i) + "##0##" + peopleip + "##" + friendsendmassagelist.at(i) + "##" + friendsendfilelist.at(i) + friends;
            }
        }

        // 拼接最终的返回结果字符串，包含好友列表的相关统计信息
        friends = "getfriendlist_ok##" + QString::number(friendlist.length()) + "##" + QString::number(onlinefriendnum) + "##" + QString::number(sendmassagenum) + "##" + QString::number(sendfilenum) + friends;

        // 在控制台输出结果字符串
        qDebug() << friends;

        // 将结果字符串转换为 UTF-8 编码并发送给 tcpSocket[0]
        tcpSocket[0]->write(friends.toUtf8());
        tcpSocket[0]->flush();

        // 关闭数据库连接
        db.close();
    }
    else
    {   // 无朋友
        tcpSocket[0]->write(QString("getfriendlist_error").toUtf8());
        tcpSocket[0]->flush();
        db.close();
    }
}

void server::addFriend(QByteArray buffer)
{
    int whowantadd_id = QString(buffer).section("##",1,1).toInt();
    // 获取请求添加好友的用户ID
    QString friend_name = QString(buffer).section("##",2,2);
    // 获取要添加的好友的名称

    qDebug() << whowantadd_id << friend_name;

    db.setDatabaseName("./people.db");  // 设置数据库路径和名称
    db.open();  // 打开数据库连接
    QSqlQuery sqlquery;
    sqlquery.prepare("select * from people where name = :name");
    // 准备查询语句，查询是否存在该好友的名称
    sqlquery.bindValue(":name",friend_name);
    // 绑定查询参数
    sqlquery.exec();
    // 执行查询
    if (sqlquery.next()) {
        // 如果存在该好友
        int friend_id = sqlquery.value(0).toInt();
         // 获取好友的ID
        qDebug() << friend_id;
        sqlquery.clear();
        QString sqlstring = "insert into friend__" + QString::number(whowantadd_id) + " values(:id,:name,0,0)";
        // 构建插入好友列表的SQL语句
        qDebug() << sqlstring;
        sqlquery.prepare(sqlstring);
        // 准备插入语句
        sqlquery.bindValue(":id",friend_id);
        // 绑定插入参数
        sqlquery.bindValue(":name",friend_name);
        sqlquery.exec();
        // 执行插入操作
        qDebug() << sqlquery.lastError();
        // 输出错误信息（如果有）
        tcpSocket[0]->write(QString("add_friend_ok").toUtf8());
        // 发送添加好友成功的消息
        tcpSocket[0]->flush();
        db.close();
        // 关闭数据库连接
    } else {
        // 如果不存在该好友
        qDebug() << "e";
        tcpSocket[0]->write(QString("add_friend_error").toUtf8());
        // 发送添加好友失败的消息
        tcpSocket[0]->flush();
        db.close();
        // 关闭数据库连接
    }
}

void server::deleteFriend(QByteArray buffer)
{
    int whowantdelete_id = QString(buffer).section("##",1,1).toInt();
    // 获取请求删除好友的用户ID
    QString friend_name = QString(buffer).section("##",2,2);
    // 获取要删除的好友的名称

    db.setDatabaseName("./people.db"); // 设置数据库路径和名称
    db.open(); // 打开数据库连接
    QSqlQuery sqlquery;
    sqlquery.prepare("delete from friend__"+QString::number(whowantdelete_id)+" where name = :name");
    // 准备删除好友的SQL语句
    sqlquery.bindValue(":name",friend_name);
    // 绑定删除参数
    if (sqlquery.exec()) {
        // 执行删除操作
        tcpSocket[0]->write(QString("delete_friend_ok").toUtf8());
        // 发送删除好友成功的消息
        tcpSocket[0]->flush();
        db.close();
        // 关闭数据库连接
    }
    else {
        tcpSocket[0]->write(QString("delete_friend_error").toUtf8());
        // 发送删除好友失败的消息
        tcpSocket[0]->flush();
        db.close();
        // 关闭数据库连接
    }
}

void server::wantSendFile(QByteArray buffer)
{
    int userid = QString(buffer).section("##",1,1).toInt();
    // 获取发送文件的用户ID
    qDebug()<<buffer;
    db.setDatabaseName("./people.db"); // 设置数据库路径和名称
    db.open(); // 打开数据库连接
    QSqlQuery sqlquery;
    sqlquery.prepare("select * from people where name = :name");
    // 准备查询用户信息的SQL语句
    sqlquery.bindValue(":name",QString(buffer).section("##",2,2));
    // 绑定查询参数
    sqlquery.exec();
    // 执行查询操作
    sqlquery.next();
    int otheruserid = sqlquery.value(0).toInt();
    // 获取接收文件的用户ID

    QString sqlstring = "update friend__" + QString::number(otheruserid) + " set sendfile = 1 where id = :id";
    // 更新接收文件用户的表，设置sendfile字段为1
    sqlquery.prepare(sqlstring);
    sqlquery.bindValue(":id",userid);
    sqlquery.exec();
}

void server::sendFileOk(QByteArray buffer)
{
    int userid = QString(buffer).section("##",1,1).toInt();
    // 获取发送文件的用户ID
    qDebug()<<buffer;
    QString sqlstring = "update friend__" + QString::number(userid) + " set sendfile = 0 where name = :name";
    // 更新发送文件用户的表，设置sendfile字段为0
    qDebug()<<sqlstring;

    db.setDatabaseName("./people.db"); // 设置数据库路径和名称
    db.open();
    // 打开数据库连接
    QSqlQuery sqlquery;
    sqlquery.prepare(sqlstring);
    sqlquery.bindValue(":name", QString(buffer).section("##",2,2));
    // 绑定查询参数
    sqlquery.exec();
    // 执行更新操作
}

void server::sendFileMiss(QByteArray buffer)
{
    int userid = QString(buffer).section("##",1,1).toInt();
    // 获取发送文件的用户ID
    qDebug()<<buffer;
    db.setDatabaseName("./people.db"); // 设置数据库路径和名称
    db.open();
    // 打开数据库连接
    QSqlQuery sqlquery;
    sqlquery.prepare("select * from people where name = :name");
    // 准备查询用户信息的SQL语句
    sqlquery.bindValue(":name",QString(buffer).section("##",2,2));
    // 绑定查询参数
    sqlquery.exec();
    // 执行查询操作
    sqlquery.next();
    int otheruserid = sqlquery.value(0).toInt();
    // 获取接收文件的用户ID

    QString sqlstring = "update friend__" + QString::number(otheruserid) + " set sendfile = 0 where id = :id";
    // 更新接收文件用户的表，设置sendfile字段为0
    sqlquery.prepare(sqlstring);
    sqlquery.bindValue(":id",userid);
    sqlquery.exec();
}
