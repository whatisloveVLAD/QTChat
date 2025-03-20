#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDataStream>
#include <QTime>
#include <QUdpSocket>

class server : public QTcpServer
{
    Q_OBJECT
public:
    server();
    QTcpSocket *socket;
    void incomingConnection(qintptr socketDescriptor) override;

private:
    QVector <QTcpSocket*> Sockets;
    QByteArray Data;
    void sendToCLient(QString str);
    quint16 nextBlockSize;
    QMap<QTcpSocket*, QString> clients;
    QUdpSocket* udpSocket;
public slots:

    void slotReadyRead();
    void clientDisconnected();
    void processUdpRequest();
};



#endif // SERVER_H
