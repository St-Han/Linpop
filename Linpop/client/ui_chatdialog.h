/********************************************************************************
** Form generated from reading UI file 'chatdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATDIALOG_H
#define UI_CHATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chatdialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QTextBrowser *textBrowser;
    QLineEdit *lineEdit;
    QPushButton *backBtn;
    QPushButton *sendMsgBtn;
    QLabel *friendName;

    void setupUi(QWidget *chatdialog)
    {
        if (chatdialog->objectName().isEmpty())
            chatdialog->setObjectName(QString::fromUtf8("chatdialog"));
        chatdialog->resize(580, 820);
        label = new QLabel(chatdialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 580, 820));
        label->setStyleSheet(QString::fromUtf8("background-image: url(:/background/pic/background/chatBackground.png);"));
        label_2 = new QLabel(chatdialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, -20, 381, 131));
        QFont font;
        font.setPointSize(40);
        font.setBold(true);
        //font.setWeight(75);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        textBrowser = new QTextBrowser(chatdialog);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(60, 140, 451, 451));
        QFont font1;
        font1.setPointSize(20);
        textBrowser->setFont(font1);
        textBrowser->setStyleSheet(QString::fromUtf8("border-radius:15px; padding:15px 15px; background-color:#F2FAFF"));
        lineEdit = new QLineEdit(chatdialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(60, 620, 371, 71));
        lineEdit->setFont(font1);
        lineEdit->setStyleSheet(QString::fromUtf8("border-radius:15px; padding:5px 15px; background-color:#F2FAFF"));
        backBtn = new QPushButton(chatdialog);
        backBtn->setObjectName(QString::fromUtf8("backBtn"));
        backBtn->setGeometry(QRect(20, 710, 71, 71));
        backBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/back.png);"));
        sendMsgBtn = new QPushButton(chatdialog);
        sendMsgBtn->setObjectName(QString::fromUtf8("sendMsgBtn"));
        sendMsgBtn->setGeometry(QRect(440, 620, 81, 81));
        sendMsgBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/send.png);"));
        friendName = new QLabel(chatdialog);
        friendName->setObjectName(QString::fromUtf8("friendName"));
        friendName->setGeometry(QRect(0, 40, 581, 131));
        friendName->setFont(font);
        friendName->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        friendName->setAlignment(Qt::AlignCenter);

        retranslateUi(chatdialog);

        QMetaObject::connectSlotsByName(chatdialog);
    } // setupUi

    void retranslateUi(QWidget *chatdialog)
    {
        chatdialog->setWindowTitle(QApplication::translate("chatdialog", "Chat", nullptr));
        label->setText(QString());
        label_2->setText(QApplication::translate("chatdialog", "Chat with ", nullptr));
        backBtn->setText(QString());
        sendMsgBtn->setText(QString());
        friendName->setText(QApplication::translate("chatdialog", "who", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chatdialog: public Ui_chatdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATDIALOG_H
