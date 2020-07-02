#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H
#include <QHostAddress>
#include <QWidget>
#include  <QTcpSocket>//通信套接字
namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

private slots:
    void on_buttonconnect_clicked();

    void on_buttonsend_clicked();

    void on_buttonclose_clicked();

private:
    Ui::ClientWidget *ui;
    QTcpSocket  *tcpSocket;
};

#endif // CLIENTWIDGET_H
