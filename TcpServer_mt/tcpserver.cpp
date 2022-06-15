#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent)
    :    QTcpServer{parent}
{

}

void TcpServer::StartServer()
{
    if(!this->listen(QHostAddress::Any,1234))
    {
        qDebug()  << "Could not start server";

    }
    else
    {
        qDebug() << "Listening...";
    }
}
void TcpServer::incomingConnection(int socketDescriptor)
{
    qDebug() << socketDescriptor << " Connecting...";
    MyThread *thread = new MyThread(socketDescriptor,this);
    connect(thread, SIGNAL(finished()),thread,SLOT(deleteLater()));
    thread->start();



}
