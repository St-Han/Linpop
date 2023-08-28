/********************************************************************************
** Form generated from reading UI file 'receivefiledialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECEIVEFILEDIALOG_H
#define UI_RECEIVEFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_receivefiledialog
{
public:
    QLabel *label_2;
    QLabel *friendName;
    QLabel *userName_2;
    QLabel *userName;
    QProgressBar *progressBar;
    QLabel *statusLabel;
    QPushButton *receiveFileBtn;
    QLabel *userName_4;

    void setupUi(QWidget *receivefiledialog)
    {
        if (receivefiledialog->objectName().isEmpty())
            receivefiledialog->setObjectName(QString::fromUtf8("receivefiledialog"));
        receivefiledialog->resize(580, 820);
        label_2 = new QLabel(receivefiledialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 0, 580, 820));
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu"));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("background-image: url(:/background/pic/background/fileBackground.png);"));
        friendName = new QLabel(receivefiledialog);
        friendName->setObjectName(QString::fromUtf8("friendName"));
        friendName->setGeometry(QRect(-10, 140, 581, 61));
        QFont font1;
        font1.setPointSize(30);
        font1.setBold(true);
        //font1.setWeight(75);
        friendName->setFont(font1);
        friendName->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        friendName->setAlignment(Qt::AlignCenter);
        userName_2 = new QLabel(receivefiledialog);
        userName_2->setObjectName(QString::fromUtf8("userName_2"));
        userName_2->setGeometry(QRect(90, 80, 101, 61));
        userName_2->setFont(font1);
        userName_2->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        userName = new QLabel(receivefiledialog);
        userName->setObjectName(QString::fromUtf8("userName"));
        userName->setGeometry(QRect(90, 0, 391, 111));
        QFont font2;
        font2.setPointSize(50);
        font2.setBold(true);
        //font2.setWeight(75);
        userName->setFont(font2);
        userName->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        progressBar = new QProgressBar(receivefiledialog);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(50, 390, 481, 41));
        QFont font3;
        font3.setPointSize(15);
        progressBar->setFont(font3);
        progressBar->setStyleSheet(QString::fromUtf8("border-radius: 15px;"));
        progressBar->setValue(24);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setOrientation(Qt::Horizontal);
        statusLabel = new QLabel(receivefiledialog);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(10, 270, 581, 61));
        QFont font4;
        font4.setFamily(QString::fromUtf8("FreeSans"));
        font4.setPointSize(20);
        font4.setBold(false);
        //font4.setWeight(50);
        statusLabel->setFont(font4);
        statusLabel->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        statusLabel->setAlignment(Qt::AlignCenter);
        receiveFileBtn = new QPushButton(receivefiledialog);
        receiveFileBtn->setObjectName(QString::fromUtf8("receiveFileBtn"));
        receiveFileBtn->setGeometry(QRect(240, 520, 91, 91));
        receiveFileBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/recvFile.png);"));
        userName_4 = new QLabel(receivefiledialog);
        userName_4->setObjectName(QString::fromUtf8("userName_4"));
        userName_4->setGeometry(QRect(250, 610, 161, 61));
        QFont font5;
        font5.setPointSize(25);
        font5.setBold(false);
        //font5.setWeight(50);
        userName_4->setFont(font5);
        userName_4->setStyleSheet(QString::fromUtf8("color:#3E5684"));

        retranslateUi(receivefiledialog);

        QMetaObject::connectSlotsByName(receivefiledialog);
    } // setupUi

    void retranslateUi(QWidget *receivefiledialog)
    {
        receivefiledialog->setWindowTitle(QApplication::translate("receivefiledialog", "receive file", nullptr));
        label_2->setText(QString());
        friendName->setText(QApplication::translate("receivefiledialog", "Someone", nullptr));
        userName_2->setText(QApplication::translate("receivefiledialog", "from", nullptr));
        userName->setText(QApplication::translate("receivefiledialog", "Receive File", nullptr));
        statusLabel->setText(QApplication::translate("receivefiledialog", "\347\255\211\345\276\205\344\270\216\345\217\221\351\200\201\347\253\257\350\277\236\346\216\245", nullptr));
        receiveFileBtn->setText(QString());
        userName_4->setText(QApplication::translate("receivefiledialog", "\346\216\245\346\224\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class receivefiledialog: public Ui_receivefiledialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECEIVEFILEDIALOG_H
