#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QtNetwork>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class home; }
QT_END_NAMESPACE

class home : public QWidget
{
    Q_OBJECT

public:
    explicit home(QWidget *parent = nullptr);
    ~home();
    QTimer *timer;

private slots:
    void createFriendList();

    void on_backBtn_clicked();

    void on_goToChatBtn_clicked();

    void on_refreshBtn_clicked();

    void on_addFriendBtn_clicked();

    void on_removeFriendBtn_clicked();

    void on_sendFileBtn_clicked();

    void on_receiveFileBtn_clicked();

protected:
    void closeEvent(QCloseEvent *event);
    void back_to_login();

private:
    Ui::home *ui;
    QTcpSocket *tcpSocket;
};

#endif // HOME_H
