#include "server.h"

server::server() {
    if(this->listen(QHostAddress::Any,1600))
    {
        qDebug() << "Server has been started";
    }else{
        qDebug() << "Error";
    }
    nextBlockSize =0;

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

