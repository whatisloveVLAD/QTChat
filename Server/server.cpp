#include "server.h"

server::server(quint16 port) {
    if(this->listen(QHostAddress::Any,port))
    {
        qDebug() << "Server has been started" << port;
    }else{
        qDebug() << "Error";
    }
    nextBlockSize =0;
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, 1601, QUdpSocket::ReuseAddressHint);
    connect(udpSocket, &QUdpSocket::readyRead, this, &server::processUdpRequest);
}


void server::incomingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket,&QTcpSocket::readyRead,this, &server::slotReadyRead);
    connect(socket,&QTcpSocket::disconnected,this, &server::clientDisconnected);


    Sockets.push_back(socket);

    QString clientName = "Client_" + QString::number(Sockets.size());
    clients[socket] = clientName;
    qDebug() << "new connected client" << socketDescriptor;

}


void server::slotReadyRead()
{
    socket  = (QTcpSocket*)sender();
    QDataStream in(socket);

    in.setVersion(QDataStream::Qt_5_0);
    if(in.status() == QDataStream::Ok)
    {
        qDebug() << "ok";
        while(true){
            if(nextBlockSize == 0){
                 qDebug() << "nextBlockSize == 0";
                if(socket->bytesAvailable() < 2){
                      qDebug() << "Data < 2 , break";
                    break;
                }
                in >> nextBlockSize;
                qDebug() << " nextBlockSize==" << nextBlockSize;
            }
            if(socket->bytesAvailable() < nextBlockSize){
                break;
            }
            QString str;
            QTime time;
            in >> time >> str;
            nextBlockSize = 0;
             qDebug() << str;
            QString clientName = clients.value(socket, "Unknown");
            qDebug() << "[" << clientName << "] " << str;

            sendToCLient(clientName + ": " + str);
            break;
        }

    }else{
        qDebug() << in.status();
    }

}

void server::sendToCLient(QString str){
    Data.clear();
    QDataStream out(&Data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint16(0)<< QTime::currentTime()<<str;
    out.device()->seek(0);
    out<< quint16(Data.size()-sizeof(quint16));
    for(int i= 0; i< Sockets.size();i++){
        Sockets[i]->write(Data);
    }

}
void server::clientDisconnected() {
    QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    qDebug() << "Client disconnected: " << clients[clientSocket];


    Sockets.removeOne(clientSocket);
    clients.remove(clientSocket);

    clientSocket->deleteLater();
}

void server::processUdpRequest() {
    while (udpSocket->hasPendingDatagrams()) {
        QHostAddress sender;
        quint16 senderPort;
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        qDebug() << "Received UDP request from" << sender.toString();


        QByteArray response = "ServerAvailable " + sender.toString().toUtf8() +" " + QByteArray::number(serverPort());

        udpSocket->writeDatagram(response, sender, senderPort);
    }
}
