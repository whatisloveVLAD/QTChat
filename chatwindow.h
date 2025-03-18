#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>

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
};

#endif // CHATWINDOW_H
