#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <userInfo.h>

QT_BEGIN_NAMESPACE
namespace Ui { class client; }
QT_END_NAMESPACE

class client : public QMainWindow
{
    Q_OBJECT

public:
    client(QWidget *parent = nullptr);
    ~client();

private slots:
    void on_btn_goToRegister_clicked();

    void on_btn_goToHome_clicked();

private:
    Ui::client *ui;
    QTcpSocket * tcpSocket;
};
#endif // CLIENT_H
