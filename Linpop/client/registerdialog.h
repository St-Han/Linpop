#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class registerdialog; }
QT_END_NAMESPACE


class registerdialog : public QWidget
{
    Q_OBJECT

public:
    explicit registerdialog(QWidget *parent = nullptr);
    ~registerdialog();

protected:
    void back_to_login();

private slots:

    void on_backBtn_clicked();

    void on_goToHomeBtn_clicked();

private:
    Ui::registerdialog *ui;
    QTcpSocket *tcpSocket;
};

#endif // REGISTERDIALOG_H
