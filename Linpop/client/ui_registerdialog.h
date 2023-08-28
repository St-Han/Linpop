/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_registerdialog
{
public:
    QLabel *label;
    QLabel *label_loginName;
    QLabel *label_password;
    QLineEdit *lineEdit_name;
    QLineEdit *lineEdit_password;
    QLineEdit *lineEdit_password_2;
    QLabel *label_password_2;
    QPushButton *backBtn;
    QPushButton *goToHomeBtn;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *registerdialog)
    {
        if (registerdialog->objectName().isEmpty())
            registerdialog->setObjectName(QString::fromUtf8("registerdialog"));
        registerdialog->resize(580, 820);
        label = new QLabel(registerdialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 580, 820));
        label->setStyleSheet(QString::fromUtf8("background-image: url(:/background/pic/background/Linpop.png);"));
        label_loginName = new QLabel(registerdialog);
        label_loginName->setObjectName(QString::fromUtf8("label_loginName"));
        label_loginName->setGeometry(QRect(90, 270, 71, 71));
        label_loginName->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/login_name.png);"));
        label_password = new QLabel(registerdialog);
        label_password->setObjectName(QString::fromUtf8("label_password"));
        label_password->setGeometry(QRect(90, 360, 71, 71));
        label_password->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/password.png);"));
        lineEdit_name = new QLineEdit(registerdialog);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(170, 280, 331, 61));
        QFont font;
        font.setPointSize(20);
        lineEdit_name->setFont(font);
        lineEdit_name->setStyleSheet(QString::fromUtf8("border-radius:15px; padding:5px 15px; background-color:#F2FAFF"));
        lineEdit_name->setClearButtonEnabled(false);
        lineEdit_password = new QLineEdit(registerdialog);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setGeometry(QRect(170, 370, 331, 61));
        lineEdit_password->setFont(font);
        lineEdit_password->setStyleSheet(QString::fromUtf8("border-radius:15px; padding:5px 15px; background-color:#F2FAFF"));
        lineEdit_password->setClearButtonEnabled(false);
        lineEdit_password_2 = new QLineEdit(registerdialog);
        lineEdit_password_2->setObjectName(QString::fromUtf8("lineEdit_password_2"));
        lineEdit_password_2->setGeometry(QRect(170, 460, 331, 61));
        lineEdit_password_2->setFont(font);
        lineEdit_password_2->setStyleSheet(QString::fromUtf8("border-radius:15px; padding:5px 15px; background-color:#F2FAFF"));
        lineEdit_password_2->setClearButtonEnabled(false);
        label_password_2 = new QLabel(registerdialog);
        label_password_2->setObjectName(QString::fromUtf8("label_password_2"));
        label_password_2->setGeometry(QRect(90, 450, 71, 71));
        label_password_2->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/password2.png);"));
        backBtn = new QPushButton(registerdialog);
        backBtn->setObjectName(QString::fromUtf8("backBtn"));
        backBtn->setGeometry(QRect(150, 590, 101, 101));
        backBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/back2.png);"));
        goToHomeBtn = new QPushButton(registerdialog);
        goToHomeBtn->setObjectName(QString::fromUtf8("goToHomeBtn"));
        goToHomeBtn->setGeometry(QRect(310, 590, 91, 91));
        goToHomeBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/pic/icon/goToHome.png);"));
        label_2 = new QLabel(registerdialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(330, 690, 71, 31));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color:#3E5684"));
        label_3 = new QLabel(registerdialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(170, 690, 71, 31));
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8("color:#3E5684"));

        retranslateUi(registerdialog);

        QMetaObject::connectSlotsByName(registerdialog);
    } // setupUi

    void retranslateUi(QWidget *registerdialog)
    {
        registerdialog->setWindowTitle(QApplication::translate("registerdialog", "Register", nullptr));
        label->setText(QString());
        label_loginName->setText(QString());
        label_password->setText(QString());
        label_password_2->setText(QString());
        backBtn->setText(QString());
        goToHomeBtn->setText(QString());
        label_2->setText(QApplication::translate("registerdialog", "\347\231\273\345\275\225", nullptr));
        label_3->setText(QApplication::translate("registerdialog", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class registerdialog: public Ui_registerdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
