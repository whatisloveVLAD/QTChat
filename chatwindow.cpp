#include "chatwindow.h"
#include "ui_mainwindow.h"

ChatWindow::ChatWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    nexBlockSize = 0;
    //setMinimumSize(650, 800);


    ui->chatDisplay->setReadOnly(true);
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
    if (in.status() == QDataStream::Ok) {
        while (true) {
            if (nexBlockSize == 0) {
                if (socket->bytesAvailable() < 2) {
                    break;
                }
                in >> nexBlockSize;
            }
            if (socket->bytesAvailable() < nexBlockSize) {
                break;
            }
            QString str;
            QTime time;
            in >> time >> str;
            nexBlockSize = 0;
            ui->chatDisplay->append(time.toString() + " " + str);
        }
    } else {
        ui->chatDisplay->append("Ошибка чтения данных");
    }
}

void ChatWindow::sendToServer(QString str) {
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint16(0) << QTime::currentTime() << str;
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
        ui->chatDisplay->append("Отключено от сервера.");
    }
    if (ui->chooseServer->currentIndex() == -1) {
        ui->chatDisplay->append("Выберите сервер из списка!");
        return;
    }




    QString selectedServer = ui->chooseServer->currentText();
    QStringList parts = selectedServer.split(":");
    if (parts.size() != 2) {
        ui->chatDisplay->append("Ошибка формата сервера!");
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
        ui->chatDisplay->append("Подключено к " + selectedServer);


    } else {
        ui->chatDisplay->append("Ошибка подключения к серверу!");
    }
}


