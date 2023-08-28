/********************************************************************************
** Form generated from reading UI file 'home.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_H
#define UI_HOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_home
{
public:
    QLabel *userName;
    QLabel *userName_2;
    QPushButton *refreshBtn;
    QPushButton *goToChatBtn;
    QPushButton *addFriendBtn;
    QPushButton *removeFriendBtn;
    QPushButton *sendFileBtn;
    QPushButton *receiveFileBtn;
    QPushButton *backBtn;
    QListWidget *friendList;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;

    void setupUi(QWidget *home)
    {
        if (home->objectName().isEmpty())
            home->setObjectName(QString::fromUtf8("home"));
        home->resize(580, 820);
        userName = new QLabel(home);
        userName->setObjectName(QString::fromUtf8("userName"));
        userName->setGeometry(QRect(110, 20, 351, 131));
        QFont font;
        font.setPointSize(50);
        font.setBold(true);
        //font.setWeight(75);
        userName->setFont(font);
        userName->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        userName->setAlignment(Qt::AlignCenter);
        userName_2 = new QLabel(home);
        userName_2->setObjectName(QString::fromUtf8("userName_2"));
        userName_2->setGeometry(QRect(60, 130, 131, 51));
        QFont font1;
        font1.setPointSize(25);
        font1.setBold(false);
        //font1.setWeight(50);
        userName_2->setFont(font1);
        userName_2->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        refreshBtn = new QPushButton(home);
        refreshBtn->setObjectName(QString::fromUtf8("refreshBtn"));
        refreshBtn->setGeometry(QRect(460, 460, 61, 61));
        refreshBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/refresh.png);"));
        goToChatBtn = new QPushButton(home);
        goToChatBtn->setObjectName(QString::fromUtf8("goToChatBtn"));
        goToChatBtn->setGeometry(QRect(80, 540, 81, 81));
        goToChatBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/goToChat.png);"));
        addFriendBtn = new QPushButton(home);
        addFriendBtn->setObjectName(QString::fromUtf8("addFriendBtn"));
        addFriendBtn->setGeometry(QRect(230, 540, 81, 81));
        addFriendBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/addFriend.png);"));
        removeFriendBtn = new QPushButton(home);
        removeFriendBtn->setObjectName(QString::fromUtf8("removeFriendBtn"));
        removeFriendBtn->setGeometry(QRect(380, 540, 81, 81));
        removeFriendBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/removeFriend.png);"));
        sendFileBtn = new QPushButton(home);
        sendFileBtn->setObjectName(QString::fromUtf8("sendFileBtn"));
        sendFileBtn->setGeometry(QRect(150, 670, 81, 81));
        sendFileBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/sendFile.png);"));
        receiveFileBtn = new QPushButton(home);
        receiveFileBtn->setObjectName(QString::fromUtf8("receiveFileBtn"));
        receiveFileBtn->setGeometry(QRect(320, 670, 81, 81));
        receiveFileBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/recvFile.png);"));
        backBtn = new QPushButton(home);
        backBtn->setObjectName(QString::fromUtf8("backBtn"));
        backBtn->setGeometry(QRect(10, 750, 71, 61));
        backBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/back.png);"));
        friendList = new QListWidget(home);
        friendList->setObjectName(QString::fromUtf8("friendList"));
        friendList->setGeometry(QRect(50, 180, 481, 341));
        QFont font2;
        font2.setPointSize(20);
        friendList->setFont(font2);
        friendList->setStyleSheet(QString::fromUtf8("border-radius: 15px; background-color:#F2FAFF; padding:15px 25px;"));
        label = new QLabel(home);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 620, 51, 41));
        QFont font3;
        font3.setPointSize(18);
        label->setFont(font3);
        label->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        label_2 = new QLabel(home);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(220, 620, 101, 41));
        label_2->setFont(font3);
        label_2->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        label_3 = new QLabel(home);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(370, 620, 101, 41));
        label_3->setFont(font3);
        label_3->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        label_4 = new QLabel(home);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(140, 750, 101, 41));
        label_4->setFont(font3);
        label_4->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        label_5 = new QLabel(home);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(310, 750, 101, 41));
        label_5->setFont(font3);
        label_5->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        label_6 = new QLabel(home);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(0, 0, 580, 820));
        label_6->setStyleSheet(QString::fromUtf8("background-image: url(:/background/pic/background/homeBackground.png);"));
        label_6->raise();
        friendList->raise();
        userName->raise();
        userName_2->raise();
        refreshBtn->raise();
        goToChatBtn->raise();
        addFriendBtn->raise();
        removeFriendBtn->raise();
        sendFileBtn->raise();
        receiveFileBtn->raise();
        backBtn->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();

        retranslateUi(home);

        QMetaObject::connectSlotsByName(home);
    } // setupUi

    void retranslateUi(QWidget *home)
    {
        home->setWindowTitle(QApplication::translate("home", "Linpop", nullptr));
        userName->setText(QApplication::translate("home", "TextLabel", nullptr));
        userName_2->setText(QApplication::translate("home", "\345\245\275\345\217\213\345\210\227\350\241\250", nullptr));
        refreshBtn->setText(QString());
        goToChatBtn->setText(QString());
        addFriendBtn->setText(QString());
        removeFriendBtn->setText(QString());
        sendFileBtn->setText(QString());
        receiveFileBtn->setText(QString());
        backBtn->setText(QString());
        label->setText(QApplication::translate("home", "\350\201\212\345\244\251", nullptr));
        label_2->setText(QApplication::translate("home", "\346\267\273\345\212\240\345\245\275\345\217\213", nullptr));
        label_3->setText(QApplication::translate("home", "\345\210\240\351\231\244\345\245\275\345\217\213", nullptr));
        label_4->setText(QApplication::translate("home", "\345\217\221\351\200\201\346\226\207\344\273\266", nullptr));
        label_5->setText(QApplication::translate("home", "\346\216\245\346\224\266\346\226\207\344\273\266", nullptr));
        label_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class home: public Ui_home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_H
