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


void server::slotReadyRead() {
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_0);

    if (in.status() != QDataStream::Ok) {
        qDebug() << "Ошибка чтения данных!";
        return;
    }

    while (socket->bytesAvailable() > 0) {
        if (nextBlockSize == 0) {
            if (socket->bytesAvailable() < sizeof(quint16)) {
                return;
            }
            in >> nextBlockSize;
        }

        if (socket->bytesAvailable() < nextBlockSize) {
            return;
        }

        MessageHeader header;
        in >> header.type;
         if (header.type != 'S') {
        QTime time;
        in >> time;
         }
        qDebug() << "Получено сообщение типа:" << header.type;

        if (header.type == 'M') {
            QString str;
            in >> str;
            nextBlockSize = 0;

            QString clientName = clients.value(socket, "Unknown");
            qDebug() << "[" << clientName << "] " << str;

            sendToCLient(clientName + ": " + str, 'M'); // Передаем как текст
        }
        else if (header.type == 'I') {
            QByteArray chunk;
            in >> chunk;


            if (expectedImageSize[socket] == 0) {
                qDebug() << "Получен чанк изображения, но ожидаемый размер не установлен! Ожидаем 'S'.";
                tempImageBuffer[socket].append(chunk);
                return;
            }

            imageBuffer[socket].append(chunk);
            nextBlockSize = 0;
            qDebug() << "Получен чанк изображения, текущий размер буфера: " << imageBuffer[socket].size();

            if (imageBuffer[socket].size() >= expectedImageSize[socket]) {
                qDebug() << "Изображение получено полностью, размер: " << imageBuffer[socket].size();
                sendToCLient(imageBuffer[socket], 'I');
                imageBuffer[socket].clear();
                expectedImageSize[socket] = 0;
            }
        }
        else if (header.type == 'S') {
            int totalSize =0;
            in >> totalSize;
            expectedImageSize[socket] = totalSize;
            qDebug() << "Размер ожидаемого изображения " << expectedImageSize[socket];

            imageBuffer[socket].clear();
            nextBlockSize = 0;

            if (!tempImageBuffer[socket].isEmpty()) {
                imageBuffer[socket].append(tempImageBuffer[socket]);
                tempImageBuffer[socket].clear();
                qDebug() << "Перенесли отложенные чанки, текущий размер буфера: " << imageBuffer[socket].size();
            }
        }
        else {
            qDebug() << "Неизвестный тип данных:" << header.type;
        }
    }
}



void server::sendToCLient(const QVariant &data, QChar type) {
    const int chunkSize = 64000;  // Чанк 64 KB
    Data.clear();

    if (type == 'I') {
        QByteArray imageData = data.toByteArray();
        int totalSize = imageData.size();
        int sentSize = 0;

        while (sentSize < totalSize) {
            QByteArray chunk = imageData.mid(sentSize, chunkSize);
            sentSize += chunk.size();

            QByteArray packet;
            QDataStream out(&packet, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_0);

            out << quint16(0) << type << QTime::currentTime();
            out << chunk;
            out << (sentSize >= totalSize);  // Перенести флаг в конец

            out.device()->seek(0);
            out << quint16(packet.size() - sizeof(quint16));

            for (QTcpSocket *clientSocket : Sockets) {
                clientSocket->write(packet);
                clientSocket->waitForBytesWritten(100);
            }

            qDebug() << "Отправлен чанк изображения, размер: " << chunk.size();
        }

        qDebug() << "Изображение отправлено полностью!";
    } else {
        QDataStream out(&Data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_0);
        out << quint16(0) << type << QTime::currentTime();
        out << data.toString();
        out.device()->seek(0);
        out << quint16(Data.size() - sizeof(quint16));

        for (QTcpSocket *clientSocket : Sockets) {
            clientSocket->write(Data);
        }
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
