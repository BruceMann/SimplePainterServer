#include <QDebug>
#include "udpserver.h"

UdpServer::UdpServer(QObject *parent)
    :QObject(parent)
{
    m_UdpSocket = new QUdpSocket(this);
    m_UdpSocket->bind(QHostAddress::LocalHost,44444);
    qDebug()<<"Server is Running .. Listen on port: 44444";
    connect(m_UdpSocket,&QUdpSocket::readyRead,this,&UdpServer::readPendingDatagrams);
}

UdpServer::~UdpServer()
{

}

void UdpServer::readPendingDatagrams()
{
    QByteArray datagram;
    QHostAddress sender;
    quint16 senderPort;
    while (m_UdpSocket->hasPendingDatagrams()) {
        datagram.resize(m_UdpSocket->pendingDatagramSize());
        m_UdpSocket->readDatagram(datagram.data(),datagram.size(),&sender,&senderPort);
    }
     QString data(datagram.constData());
     if(QString::compare(data,"login",Qt::CaseInsensitive)==0){
        qDebug()<<sender.toString()<<"connect to server,listen on port"<<senderPort;
        qDebug()<<clientList.size();
        clientList.append(qMakePair(sender,senderPort));
        qDebug()<<clientList.size();
     }else{
         foreach (auto client, clientList) {
             if(client.first!=sender||client.second!=senderPort)
             {
                m_UdpSocket->writeDatagram(datagram,datagram.size(),client.first,client.second);
             }
         }
     }
}


