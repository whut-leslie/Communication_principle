#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerWidget)
{
    ui->setupUi(this);

    tcpServer = NULL;

    //监听套接字，指定父对象，让其自动回收空间
    tcpServer=new  QTcpServer(this);
    tcpServer->listen(QHostAddress::Any,2020);
    setWindowTitle("服务器：2020");


    connect(tcpServer,&QTcpServer::newConnection,
            [=]()
    {
        //取出建立好连接好的套接字
        QTcpSocket* tcpSocket=tcpServer->nextPendingConnection();
        //获取对方的IP和端口
        QString ip=tcpSocket->peerAddress().toString();
        qint16 port = tcpSocket->peerPort();

        QString temp =QString("[%1:%2]成功连接").arg(ip).arg(port);
        ui->textEditRead->append(temp);
        tcpSocketlist.append(tcpSocket);
        connect(tcpSocket,&QTcpSocket::readyRead,
                [=]()
        {
            //从通信套接字中获取
            QByteArray array = tcpSocket->readAll();
            ui->textEditRead->append(array);
            for(int i = 0; i < tcpSocketlist.count(); i++)
                  {
                    QTcpSocket *item = tcpSocketlist.at(i);

                        item->write(array);
                        }
        });
    }
    );


}

ServerWidget::~ServerWidget()
{
    delete ui;
}


void ServerWidget::on_butttonSend_clicked()
{

     for(int i = 0; i < tcpSocketlist.count(); i++)
           {
             QTcpSocket *item = tcpSocketlist.at(i);

             QString str = ui->textEditWrite->toPlainText();
             //给对方发动数据，使用套接字是tcpSocket
             item->write(str.toUtf8().data());

                 }



}



void ServerWidget::on_buttonClose_clicked()
{
     QTcpSocket* tcpSocket=tcpServer->nextPendingConnection();
    if(NULL==tcpSocket)
    {
       return;
    }
    //主动和客户端断开链接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpSocket=NULL;

}
