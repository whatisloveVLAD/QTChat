#include "chatwindow.h"
#include "ui_mainwindow.h"
#include "ClickLabel.h"
ChatWindow::ChatWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    nexBlockSize = 0;

    this->setFixedSize(608, 776);

    ui->chatDisplay->setStyleSheet("background-color: #f5f5f5; font-size: 14px; ");


    ui->messageInput->setStyleSheet("background-color: #ffffff; font-size: 14px; ");



    ui->sendButton->setText("→");
    ui->sendButton->setStyleSheet(
        "background-color: #4CAF50; color: white; font-size: 18px;  "
        "border-radius: 5px;"
        );



    connect(ui->sendButton, &QPushButton::clicked, this, &ChatWindow::sendMessage);


    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &ChatWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    udpSocket = new QUdpSocket(this);
    connect(udpSocket, &QUdpSocket::readyRead, this, &ChatWindow::processUdpResponse);

    searchForServers();
}

ChatWindow::~ChatWindow() {
    delete ui;
}

void ChatWindow::searchForServers() {
    QByteArray request = "FindServer";qDebug() << "Отправка UDP-запроса на поиск сервера";

    udpSocket->writeDatagram(request, QHostAddress::Broadcast, 1601);
    qDebug() << "UDP-запрос отправлен";
}

void ChatWindow::sendMessage() {
    QString message = ui->messageInput->toPlainText().trimmed();
    if (!message.isEmpty()) {
        sendToServer(message);
        ui->messageInput->clear();
    }
}

void ChatWindow::slotReadyRead() {
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_0);

    while (socket->bytesAvailable()) {
        if (nexBlockSize == 0) {
            qDebug() << "Ожидаемый размер блока:" << nexBlockSize;
            qDebug() << "Доступно байт:" << socket->bytesAvailable();

            if (socket->bytesAvailable() < sizeof(quint16)) {
                return;
            }
            in >> nexBlockSize;
        }

        if (socket->bytesAvailable() < nexBlockSize) {
            return;
        }

        MessageHeader header;
        QTime time;

        QChar type;
        in >> type;
        header.type = type;


        qDebug() << "Получен заголовок type:" << header.type;

        in >> time;

        if (header.type == 'M') {

            QString message;
            in >> message;
            ui->chatDisplay->addItem(time.toString() + " " + message);
        }
        else if (header.type == 'I') {
            bool isLastChunk;
            QByteArray chunk;
            in >> chunk >> isLastChunk;


            imageBuffer.append(chunk);
            qDebug() << "Общий размер полученных чанков: " << imageBuffer.size();

            qDebug() << "Клиент получил чанк изображения, размер: " << chunk.size();

            if (isLastChunk) {
                qDebug() << "Изображение получено полностью, размер: " << imageBuffer.size();

                QImage image;
                qDebug() << "Окончательный размер imageBuffer:" << imageBuffer.size();
                if (imageBuffer.isEmpty()) {
                    qDebug() << "Ошибка: imageBuffer пуст!";
                    return;
                }


                QString tempFilePath = QDir::tempPath() + "/debug_received_image.png";
                if (!image.save(tempFilePath)) {
                    qDebug() << "Ошибка сохранения изображения!";
                } else {
                    qDebug() << "Изображение сохранено в " << tempFilePath;
                }
                qDebug() << "Размер imageBuffer перед загрузкой:" << imageBuffer.size();

                if (image.loadFromData(imageBuffer)) {
                    QString tempFilePath = QDir::tempPath() + "/received_image.png";
                    image.save(tempFilePath);


                    QPixmap originalPixmap;
                    originalPixmap.loadFromData(imageBuffer);


                    ui->chatDisplay->addItem(time.toString() + " Получено изображение.");


                    ClickableLabel *imageLabel = new ClickableLabel(this);


                    QPixmap previewPixmap = originalPixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    imageLabel->setPixmap(previewPixmap);
                    imageLabel->setFixedSize(previewPixmap.size());


                    connect(imageLabel, &ClickableLabel::clicked, [originalPixmap]() {
                        QLabel *fullImageLabel = new QLabel;
                        fullImageLabel->setPixmap(originalPixmap);
                        fullImageLabel->setScaledContents(true);
                        fullImageLabel->resize(originalPixmap.size());
                        fullImageLabel->resize(originalPixmap.size());
                        fullImageLabel->setWindowFlags(Qt::Dialog);
                        fullImageLabel->show();
                    });


                    QListWidgetItem *imageItem = new QListWidgetItem();
                    imageItem->setSizeHint(imageLabel->size());
                    ui->chatDisplay->addItem(imageItem);
                    ui->chatDisplay->setItemWidget(imageItem, imageLabel);



                } else {
                    ui->chatDisplay->addItem(time.toString() + " Ошибка загрузки изображения.");
                }
                qDebug() << "Общий размер полученных чанков: " << imageBuffer.size();

                imageBuffer.clear();
            }
        }
        else {
            ui->chatDisplay->addItem("Неизвестный тип сообщения!");
        }

        nexBlockSize = 0;
    }
}



void ChatWindow::sendToServer(QString str) {
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);

    MessageHeader header;
    header.type = 'M';

    out << quint16(0) << header.type << QTime::currentTime() << str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));

    socket->write(Data);
}

void ChatWindow::processUdpResponse() {
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString response(datagram);
        if (response.startsWith("ServerAvailable")) {
            QStringList parts = response.split(" ");
            if (parts.size() == 3) {
                QString serverIp = parts[1];
                QString serverPort = parts[2];
                ui->chooseServer->addItem(serverIp + ":" + serverPort);
            }
        }
    }
}

void ChatWindow::on_connectToServer_clicked() {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->disconnectFromHost();
        ui->chatDisplay->addItem("Отключено от сервера.");
    }
    if (ui->chooseServer->currentIndex() == -1) {
        ui->chatDisplay->addItem("Выберите сервер из списка!");
        return;
    }




    QString selectedServer = ui->chooseServer->currentText();
    QStringList parts = selectedServer.split(":");
    if (parts.size() != 2) {
        ui->chatDisplay->addItem("Ошибка формата сервера!");
        return;
    }

    QString serverIp = parts[0];
    quint16 serverPort = parts[1].toUShort();

    ui->chatDisplay->clear();
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &ChatWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);



    socket->connectToHost(serverIp, serverPort);

    if (socket->waitForConnected(3000)) { // Ждем подключения
        ui->chatDisplay->addItem("Подключено к " + selectedServer);


    } else {
        ui->chatDisplay->addItem("Ошибка подключения к серверу!");
    }
}



void ChatWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Выберите изображение"), "", tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));
    if (!fileName.isEmpty()) {
        sendImage(fileName);
    }

}
void ChatWindow::sendImage(QString filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        ui->chatDisplay->addItem("Не удалось открыть файл: " + filePath);
        return;
    }

    QByteArray imageData = file.readAll();
    file.close();

    int chunkSize = 16384;
    int totalSize = imageData.size();
    int sentBytes = 0;
    QByteArray headerPacket;
    QDataStream headerStream(&headerPacket, QIODevice::WriteOnly);
    headerStream.setVersion(QDataStream::Qt_5_0);

    MessageHeader header;
    header.type = 'S';
    headerStream << quint16(0) << header.type << totalSize;
    headerStream.device()->seek(0);
    headerStream << quint16(headerPacket.size() - sizeof(quint16));
    qDebug() << "Размер отправленного изображения " <<  totalSize;
    socket->write(headerPacket);
    socket->waitForBytesWritten(5000);

    while (sentBytes < totalSize) {
        int currentChunkSize = qMin(chunkSize, totalSize - sentBytes);
        QByteArray chunk = imageData.mid(sentBytes, currentChunkSize);

        QByteArray packet;
        QDataStream out(&packet, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_0);

        MessageHeader header;
        header.type = 'I';

        out << quint16(0) << header.type << QTime::currentTime() << chunk;
        out.device()->seek(0);
        out << quint16(packet.size() - sizeof(quint16));

        socket->write(packet);
        if (!socket->waitForBytesWritten(5000)) {
            qDebug() << "Ошибка: Чанк данных не записан полностью!";
            return;
        }

        sentBytes += currentChunkSize;
        qDebug() << "Отправлено: " << sentBytes << " из " << totalSize;
    }

    qDebug() << "Изображение успешно отправлено! Полный размер: " << totalSize;
}





