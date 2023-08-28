#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QWidget>
#include <QTcpSocket>
#include <QTimer>
#include <QCloseEvent>

namespace Ui { class chatdialog; }

class chatdialog : public QWidget
{
    Q_OBJECT

public:
    explicit chatdialog(QWidget *parent = nullptr);
    ~chatdialog();
    QTimer *timer;

private slots:
    void getchathistory();

    void on_backBtn_clicked();

    void on_sendMsgBtn_clicked();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::chatdialog *ui;
    QTcpSocket *tcpSocket;
};

#endif // CHATDIALOG_H
