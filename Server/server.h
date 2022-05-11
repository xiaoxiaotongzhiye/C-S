#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QByteArray>
#include <QString>
#include "user.h"

class server : public QTcpServer
{
    Q_OBJECT
public:
    server();
    server(int port);
    void incomingConnection(qintptr handle) override;
    QTcpSocket *socket;

private slots:
    void receiveMessage();
    void receiveLog(user *);
    void receiveReg(QString);
    void receiveUpdate(QString);

signals:
    void sendMessage(QString);
    void sendReg(user *);
    void sendLog(user *);
    void sendUpd(user *);
};

#endif // SERVER_H
