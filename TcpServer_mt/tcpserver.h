#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include "mythread.h"


class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);
    void StartServer();
signals:

public slots:

protected:
    void incomingConnection(int socketDescriptor);

};

#endif // TCPSERVER_H
