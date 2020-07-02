#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QHostAddress>
#include <QMessageBox>
ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    tcpSocket=NULL;
     setWindowTitle("客户端");
    //分配空间，指定父对象
    tcpSocket=new QTcpSocket(this);

    connect(tcpSocket,&QTcpSocket::connected,
            [=]()
    {
        ui->textEditRead->setText("成功和服务器建立好链接");
    });
    connect(tcpSocket,&QTcpSocket::readyRead,
            [=]
    {
        //获取对方发送到内容
        QByteArray array =tcpSocket->readAll();
        //追加到编辑区中
        ui->textEditRead->append(array);

    }

            );
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_buttonconnect_clicked()
{
    if(ui->lineEditUsername->text() == "")
    {
        //用户名不能为空
        QMessageBox::warning(this, "错误", "用户名不能为空");
        return;
    }
    //获取服务器IP和端口
    QString ip =ui->lineEditIP->text();
    qint16 port =ui->lineEditPort->text().toInt();

    //主动和服务器建立链接
    tcpSocket->connectToHost(QHostAddress(ip),port);

}

void ClientWidget::on_buttonsend_clicked()
{
    //获取编辑框内容
    QString str = ui->textEditWrite->toPlainText();
    QString User_name=ui->lineEditUsername->text();
    str=User_name+":"+str;
    //发送数据
    tcpSocket->write(str.toUtf8().data());

}

void ClientWidget::on_buttonclose_clicked()
{
    //主动和对方断开链接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();

}
