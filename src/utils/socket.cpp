#include "socket.h"
#include "qdebug.h"
#include "qsettings.h"

extern QString g_strInitDir;

Socket::Socket(QObject *parent) : QObject(parent)
{
    init();
}

Socket::~Socket() {
    clear();
}

void Socket::init() {
    m_Server = new QTcpServer();
    m_Socket = new QTcpSocket();

    QString strFileTPath("%1/config.cnf");
    strFileTPath = strFileTPath.arg(g_strInitDir);


#ifdef _WIN32
    strFileTPath.replace("/", "\\");
#endif /* _WIN32 */


    QSettings qset(strFileTPath, QSettings::IniFormat);
    qDebug() << strFileTPath;
    int port = qset.value("Server/Port", 1240).toInt();
    QVariantMap map;
    map.insert("hh", 11);
    newListen(port);
}

void Socket::clear() {
    if(m_Server->isListening()){
        m_Server->close();
    }
    if(m_Socket->isOpen()){
        m_Socket->close();
    }
    if(m_ConnectSocket->isOpen()){
        m_ConnectSocket->close();
    }
    delete m_Server;
    delete m_Socket;
    delete m_ConnectSocket;
}

void Socket::newListen(int port){
    if(!m_Server->listen(QHostAddress::Any, port)){
        qDebug() << m_Server->errorString();
        m_Server->close();
    }
    m_Server->close();
    if(!m_Server->listen(QHostAddress::Any, port)){
        qDebug() << m_Server->errorString();
        m_Server->close();
    }
    connect(m_Server, SIGNAL(newConnection()), this, SLOT(acceptConnect()));
}

void Socket::acceptConnect() {
    m_ConnectSocket = m_Server->nextPendingConnection();
    connect(m_ConnectSocket, SIGNAL(readyRead()), this, SLOT(receive()));
}

void Socket::m_Connect(QString ip, int port){
    m_Socket->abort();
    m_Socket->connectToHost(ip, port);
}

void Socket::receive() {
    QString data;
    data.prepend(m_ConnectSocket->readAll());
    qDebug() << data;
    m_Receive("receive", data);
}

void Socket::m_SendMessage(QString data){
    QByteArray sendData = data.toUtf8();
    m_Socket->write(sendData);
}


