/********************************************************************************
** Form generated from reading UI file 'sendfiledialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDFILEDIALOG_H
#define UI_SENDFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sendfiledialog
{
public:
    QLabel *label;
    QLabel *userName;
    QLabel *userName_2;
    QLabel *friendName;
    QLabel *statusLabel;
    QPushButton *chooseFileBtn;
    QPushButton *sendFileBtn;
    QLabel *userName_3;
    QLabel *userName_4;

    void setupUi(QWidget *sendfiledialog)
    {
        if (sendfiledialog->objectName().isEmpty())
            sendfiledialog->setObjectName(QString::fromUtf8("sendfiledialog"));
        sendfiledialog->resize(580, 820);
        label = new QLabel(sendfiledialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 580, 820));
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu"));
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-image: url(:/background/pic/background/fileBackground.png);"));
        userName = new QLabel(sendfiledialog);
        userName->setObjectName(QString::fromUtf8("userName"));
        userName->setGeometry(QRect(130, 0, 311, 111));
        QFont font1;
        font1.setPointSize(50);
        font1.setBold(true);
        //font1.setWeight(75);
        userName->setFont(font1);
        userName->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        userName_2 = new QLabel(sendfiledialog);
        userName_2->setObjectName(QString::fromUtf8("userName_2"));
        userName_2->setGeometry(QRect(100, 80, 51, 61));
        QFont font2;
        font2.setPointSize(30);
        font2.setBold(true);
        //font2.setWeight(75);
        userName_2->setFont(font2);
        userName_2->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        friendName = new QLabel(sendfiledialog);
        friendName->setObjectName(QString::fromUtf8("friendName"));
        friendName->setGeometry(QRect(0, 120, 581, 61));
        friendName->setFont(font2);
        friendName->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        friendName->setAlignment(Qt::AlignCenter);
        statusLabel = new QLabel(sendfiledialog);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(0, 230, 581, 61));
        QFont font3;
        font3.setFamily(QString::fromUtf8("FreeSans"));
        font3.setPointSize(20);
        font3.setBold(false);
        //font3.setWeight(50);
        statusLabel->setFont(font3);
        statusLabel->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        statusLabel->setAlignment(Qt::AlignCenter);
        chooseFileBtn = new QPushButton(sendfiledialog);
        chooseFileBtn->setObjectName(QString::fromUtf8("chooseFileBtn"));
        chooseFileBtn->setGeometry(QRect(140, 370, 91, 91));
        chooseFileBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/chooseFile.png);"));
        sendFileBtn = new QPushButton(sendfiledialog);
        sendFileBtn->setObjectName(QString::fromUtf8("sendFileBtn"));
        sendFileBtn->setGeometry(QRect(230, 560, 91, 91));
        sendFileBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/sendFile.png);"));
        userName_3 = new QLabel(sendfiledialog);
        userName_3->setObjectName(QString::fromUtf8("userName_3"));
        userName_3->setGeometry(QRect(250, 380, 161, 61));
        QFont font4;
        font4.setPointSize(25);
        font4.setBold(false);
        //font4.setWeight(50);
        userName_3->setFont(font4);
        userName_3->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        userName_4 = new QLabel(sendfiledialog);
        userName_4->setObjectName(QString::fromUtf8("userName_4"));
        userName_4->setGeometry(QRect(240, 650, 161, 61));
        userName_4->setFont(font4);
        userName_4->setStyleSheet(QString::fromUtf8("color:#3E5684"));

        retranslateUi(sendfiledialog);

        QMetaObject::connectSlotsByName(sendfiledialog);
    } // setupUi

    void retranslateUi(QWidget *sendfiledialog)
    {
        sendfiledialog->setWindowTitle(QApplication::translate("sendfiledialog", "Send File", nullptr));
        label->setText(QString());
        userName->setText(QApplication::translate("sendfiledialog", "Send File", nullptr));
        userName_2->setText(QApplication::translate("sendfiledialog", "to", nullptr));
        friendName->setText(QApplication::translate("sendfiledialog", "Someone", nullptr));
        statusLabel->setText(QApplication::translate("sendfiledialog", "\350\257\267\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        chooseFileBtn->setText(QString());
        sendFileBtn->setText(QString());
        userName_3->setText(QApplication::translate("sendfiledialog", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        userName_4->setText(QApplication::translate("sendfiledialog", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sendfiledialog: public Ui_sendfiledialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDFILEDIALOG_H
