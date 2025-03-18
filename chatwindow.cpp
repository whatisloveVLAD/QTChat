#include "chatwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

ChatWindow::ChatWindow()
{
    nexBlockSize =0;
    chatDisplay = new QTextEdit(this);
    chatDisplay->setReadOnly(true);
    chatDisplay->setStyleSheet("background-color: #f5f5f5; font-size: 14px; padding: 10px;");


    QWidget *inputContainer = new QWidget(this);
    QHBoxLayout *inputLayout = new QHBoxLayout(inputContainer);
    inputLayout->setSpacing(5);
    inputLayout->setContentsMargins(5, 5, 5, 5);

    messageInput = new QTextEdit(inputContainer);
    messageInput->setPlaceholderText("Введите сообщение...");
    messageInput->setStyleSheet("background-color: #ffffff; font-size: 14px; padding: 10px;");
    messageInput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    messageInput->setFixedHeight(70);
    messageInput->setMaximumHeight(200);

    sendButton = new QPushButton("→", inputContainer);
    sendButton->setStyleSheet(
        "background-color: #4CAF50; color: white; font-size: 18px; padding: 5px; "
        "border-radius: 5px; min-width: 40px; min-height: 40px;"
        );
    sendButton->setFixedSize(40, 40); // Фиксированный размер кнопки

    inputLayout->addWidget(messageInput);
    inputLayout->addWidget(sendButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(chatDisplay);
    mainLayout->addWidget(inputContainer);

    setLayout(mainLayout);

    connect(sendButton, &QPushButton::clicked, this, &ChatWindow::sendMessage);

    socket = new QTcpSocket(this);
    connect(socket,&QTcpSocket::readyRead,this,&ChatWindow::slotReadyRead);
    connect(socket,&QTcpSocket::disconnected,socket,&QTcpSocket::deleteLater);

    socket->connectToHost("127.0.0.1", 1600);




}

void ChatWindow::sendMessage() {
    QString message = messageInput->toPlainText().trimmed();
    if (!message.isEmpty()) {
       // chatDisplay->append("<b>Вы:</b> " + message);

        sendToServer(message);
        messageInput->clear();
    }
}
void ChatWindow::slotReadyRead(){
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_0);
    if(in.status() == QDataStream::Ok){
        // QString str;
        // in >> str;
        // chatDisplay -> append(str);
        while(true){
            if(nexBlockSize == 0){
                if(socket->bytesAvailable() < 2){
                    break;
                }
                in >> nexBlockSize;
            }
            if(socket->bytesAvailable() < nexBlockSize){
                break;
            }
            QString str;
            QTime time;
            in >>time >> str;
            nexBlockSize = 0;
            chatDisplay -> append(time.toString() + " " + str);
        }
    }else{
        chatDisplay -> append("error");
    }

}
void ChatWindow::sendToServer(QString str){
    Data.clear();
    QDataStream out(&Data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint16(0)<<QTime::currentTime() <<str;
    out.device()->seek(0);
    out<< quint16(Data.size()-sizeof(quint16));
    socket->write(Data);

}
