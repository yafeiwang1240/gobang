#ifndef SOCKET_H
#define SOCKET_H
#include <QTcpServer>
#include <QTcpSocket>

class Socket : public QObject
{

    Q_OBJECT
public:
    Socket(QObject* parent = nullptr);
    ~Socket();

    void newListen(int port = 1240);
private:
    void clear();
    void init();


    QTcpServer *m_Server = 0;
    QTcpSocket *m_Socket = 0;
    QTcpSocket *m_ConnectSocket = 0;

private slots:
    void m_Connect(QString ip, int port);
    void acceptConnect();
    void m_SendMessage(QString data);
    void receive();

signals:
    void m_Receive(QString type, QString data);
};

#endif // SOCKET_H
