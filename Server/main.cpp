#include <QCoreApplication>
#include "server.h"
int main(int argc, char *argv[])
{
    quint16 port = 1700;
    QCoreApplication a(argc, argv);

    server* s = nullptr;

    if (argc > 1) {
        bool ok;
        port = QString(argv[1]).toUShort(&ok);
        qDebug() << port;
        if (!ok || port <= 1023 || port > 65535) {
            qDebug() << "Error: Port must be greater than 1023 and less than or equal to 65535.";
            return 1;
        } else {
            s = new server(port);
        }
    } else {
        s = new server(port);
    }

    int result = a.exec();

    delete s;

    return result;
}
