#ifndef MYUDP_H
#define MYUDP_H

#include <QObject>
#include <QUdpSocket>
class MyUDP : public QObject
{
    Q_OBJECT
public:
    explicit MyUDP(QObject *parent = nullptr);
    void SayHello();

signals:

public slots:
    void readyRead();

private:
    QUdpSocket *socket;

};

#endif // MYUDP_H
