#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QList>
#include <QPair>

class UdpServer:public QObject
{
    Q_OBJECT
public:
    UdpServer(QObject *parent = NULL);
    ~UdpServer();

public slots:
    void readPendingDatagrams();
private:
    QUdpSocket *m_UdpSocket;


    QList<QPair<QHostAddress,quint16>> clientList;
};

#endif // UDPSERVER_H
