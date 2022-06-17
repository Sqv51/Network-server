#include <QCoreApplication>
#include "myudp.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyUDP Server;
    MyUDP client;

    client.SayHello();
    return a.exec();
}
