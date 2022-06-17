#ifndef MYWSOCKET_H
#define MYWSOCKET_H

#include <QObject>
#include <QtWebSockets/QWebSocket>

class MyWsocket : public QObject
{
    Q_OBJECT
public:
    explicit MyWsocket(const QUrl &url, bool debug = false, QObject *parent = nullptr);

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;


};

#endif // MYWSOCKET_H
