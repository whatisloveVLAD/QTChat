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
    server(quint16);
    QTcpSocket *socket;
    void incomingConnection(qintptr socketDescriptor) override;

private:
    QVector <QTcpSocket*> Sockets;
    QByteArray Data;
    void sendToCLient(const QVariant &data, QChar type);
    quint16 nextBlockSize;
    QMap<QTcpSocket*, QString> clients;
    QUdpSocket* udpSocket;
    struct MessageHeader {
        QChar type;

    };
private:
    QMap<QTcpSocket*, QByteArray> imageBuffer;
    QMap<QTcpSocket*, QByteArray>  tempImageBuffer;
    QMap<QTcpSocket*, int> expectedImageSize;

public slots:

    void slotReadyRead();
    void clientDisconnected();
    void processUdpRequest();
};



#endif // SERVER_H
