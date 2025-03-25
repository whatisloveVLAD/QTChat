#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QTcpSocket>
#include <QTime>
#include <QUdpSocket>
#include<QFileDialog>
#include<QLabel>
#include <QImage>
#include<QVBoxLayout>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();

private slots:
    void sendMessage();
    void slotReadyRead();
    void searchForServers();
    void processUdpResponse();

    void on_connectToServer_clicked();

    void on_pushButton_clicked();
private:
    QByteArray imageBuffer;
    QMap<QTcpSocket*, quint16> expectedImageSize;
private:
    Ui::MainWindow *ui; // Подключаем UI
    QTcpSocket *socket;
    QByteArray Data;
    quint16 nexBlockSize;
     QUdpSocket *udpSocket;
    void sendToServer(QString st);
     void sendImage( QString filePath);
    struct MessageHeader {
        QChar type;

    };
    bool isImageData(const QByteArray &data);
};

#endif // CHATWINDOW_H
