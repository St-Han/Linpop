/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_client
{
public:
    QWidget *centralwidget;
    QLabel *label_loginName;
    QLabel *label_password;
    QLineEdit *lineEdit_loginName;
    QLineEdit *lineEdit_password;
    QPushButton *btn_goToRegister;
    QPushButton *btn_goToHome;
    QListView *background;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QMainWindow *client)
    {
        if (client->objectName().isEmpty())
            client->setObjectName(QString::fromUtf8("client"));
        client->resize(580, 820);
        client->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(client);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_loginName = new QLabel(centralwidget);
        label_loginName->setObjectName(QString::fromUtf8("label_loginName"));
        label_loginName->setGeometry(QRect(80, 280, 71, 71));
        label_loginName->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/login_name.png);"));
        label_password = new QLabel(centralwidget);
        label_password->setObjectName(QString::fromUtf8("label_password"));
        label_password->setGeometry(QRect(80, 380, 71, 71));
        label_password->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/password.png);"));
        lineEdit_loginName = new QLineEdit(centralwidget);
        lineEdit_loginName->setObjectName(QString::fromUtf8("lineEdit_loginName"));
        lineEdit_loginName->setGeometry(QRect(170, 290, 331, 61));
        QFont font;
        font.setPointSize(20);
        lineEdit_loginName->setFont(font);
        lineEdit_loginName->setStyleSheet(QString::fromUtf8("border-radius:15px; padding:5px 15px; background-color:#F2FAFF"));
        lineEdit_loginName->setClearButtonEnabled(false);
        lineEdit_password = new QLineEdit(centralwidget);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setGeometry(QRect(170, 390, 331, 61));
        lineEdit_password->setFont(font);
        lineEdit_password->setStyleSheet(QString::fromUtf8("border-radius:15px; padding:5px 15px;background-color:#F2FAFF"));
        btn_goToRegister = new QPushButton(centralwidget);
        btn_goToRegister->setObjectName(QString::fromUtf8("btn_goToRegister"));
        btn_goToRegister->setGeometry(QRect(150, 520, 89, 91));
        btn_goToRegister->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/goToRegister.png);"));
        btn_goToHome = new QPushButton(centralwidget);
        btn_goToHome->setObjectName(QString::fromUtf8("btn_goToHome"));
        btn_goToHome->setGeometry(QRect(310, 520, 89, 91));
        btn_goToHome->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/goToHome.png);"));
        background = new QListView(centralwidget);
        background->setObjectName(QString::fromUtf8("background"));
        background->setGeometry(QRect(0, 0, 580, 820));
        background->setStyleSheet(QString::fromUtf8("background-image: url(:/background/pic/background/Linpop.png);"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(170, 620, 71, 31));
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(330, 620, 71, 31));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        client->setCentralWidget(centralwidget);
        background->raise();
        label_loginName->raise();
        label_password->raise();
        lineEdit_password->raise();
        btn_goToRegister->raise();
        btn_goToHome->raise();
        lineEdit_loginName->raise();
        label->raise();
        label_2->raise();

        retranslateUi(client);

        QMetaObject::connectSlotsByName(client);
    } // setupUi

    void retranslateUi(QMainWindow *client)
    {
        client->setWindowTitle(QApplication::translate("client", "Welcom to Linpop", nullptr));
        label_loginName->setText(QString());
        label_password->setText(QString());
        btn_goToRegister->setText(QString());
        btn_goToHome->setText(QString());
        label->setText(QApplication::translate("client", "\346\263\250\345\206\214", nullptr));
        label_2->setText(QApplication::translate("client", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class client: public Ui_client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
