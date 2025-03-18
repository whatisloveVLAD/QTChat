#include "chatwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

ChatWindow::ChatWindow()
{
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
}

void ChatWindow::sendMessage() {
    QString message = messageInput->toPlainText().trimmed();
    if (!message.isEmpty()) {
        chatDisplay->append("<b>Вы:</b> " + message);
        messageInput->clear();
    }
}
