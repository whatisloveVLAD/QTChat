#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QTcpSocket>
#include <QTime>

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    ChatWindow();

private slots:
    void sendMessage();

private:
    QTextEdit *chatDisplay;
    QTextEdit *messageInput;
    QPushButton *sendButton;
    QTcpSocket *socket;
    QByteArray Data;
    void sendToServer(QString st);
    quint16 nexBlockSize;

public slots:
    void slotReadyRead();
};



#endif // CHATWINDOW_H
