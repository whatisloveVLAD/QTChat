#include <QApplication>
#include "chatwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ChatWindow window;
    window.setWindowTitle("Чат");
    window.setStyleSheet("background-color: #eeeeee;");

    window.show();

    return a.exec();
}
