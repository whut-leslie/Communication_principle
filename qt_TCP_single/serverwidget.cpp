#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);

    tcpServer = NULL;
    tcpSocket = NULL;

    //监听套接字   指定父对象的目的，让其自动回收空间
    tcpServer = new QTcpServer(this);

    tcpServer->listen(QHostAddress::Any,2020);

    setWindowTitle("服务器：2020");

    connect(tcpServer,&QTcpServer::newConnection,[=](){
        //取出建立好连接的的套接字
        tcpSocket = tcpServer->nextPendingConnection();

        //获取对方的IP和端口
        QString ip = tcpSocket->peerAddress().toString();
        qint16  port = tcpSocket->peerPort();
        QString temp = QString("[%1:%2]:成功连接").arg(ip).arg(port);

        ui->textEditRead->setText(temp);

            /*注意这里的connect的位置，一定在建立好连接后，
             * 不然会出现野指针的错误，前面定义的QTcpSocket  *tcpSocket;
             * 而程序会先从构造函数执行的，还没有执行到定义的QTcpSocket  *tcpSocket指针。
            */
            connect(tcpSocket,&QTcpSocket::readyRead,[=](){

                //从通信套接字中取出内容
                QByteArray array = tcpSocket->readAll();

                ui->textEditRead->append(array);
            });

        });

}

ServerWidget::~ServerWidget()
{
    delete ui;
}


void ServerWidget::on_butttonSend_clicked()
{
    if(NULL == tcpSocket)
    {
        return ;
    }
    //获取编辑区的内容
    QString str = ui->textEditWrite->toPlainText();

    //给对方发送数据，使用套接字是tcpSocket
    tcpSocket->write(str.toUtf8().data());

}

void ServerWidget::on_buttonClose_clicked()
{
    if(NULL == tcpSocket)
    {
        return ;
    }
    //主动和客户端端口断开连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();

    tcpSocket = NULL;
}
