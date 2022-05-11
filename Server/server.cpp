#include "server.h"

server::server()
{

}

server::server(int port)
{
    listen(QHostAddress::Any,port);
}

void server::incomingConnection(qintptr handle)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(handle);

    //连接客户端发送信息与处理函数
    connect(socket,SIGNAL(readyRead()),this,SLOT(receiveMessage()));

    emit sendMessage(QString::fromLocal8Bit("客户端")+ socket->peerAddress().toString() + QString::fromLocal8Bit("连接至服务器"));

}

//处理从客户接收到的消息
void server::receiveMessage()
{
    QByteArray arr = socket->readAll();
    QString temp = QString::fromLocal8Bit(arr.data());
    QStringList strList = temp.split(":");
    user *u = new user;
    //按序：0信号 1用户名 2密码 3电话 4真实姓名 5工作 6性别 7生日
    if(strList.value(0)=="REG"){
        u->setNickName(strList.value(1));
        u->setPassword(strList.value(2));
        u->setPhoneNum(strList.value(3));
        u->setUserName(strList.value(4));
        u->setJob(strList.value(5));
        u->setSex(strList.value(6).toUInt());
        u->setBirthDay(strList.value(7));
        emit sendReg(u);

    }
    else if(strList.value(0)=="LOG"){
        u->setNickName(strList.value(1));
        u->setPassword(strList.value(2));
        emit sendLog(u);
    }
    else if(strList.value(0)=="UPD"){
        u->setNickName(strList.value(1));
        u->setPassword(strList.value(2));
        u->setPhoneNum(strList.value(3));
        u->setUserName(strList.value(4));
        u->setJob(strList.value(5));
        u->setSex(strList.value(6).toUInt());
        u->setBirthDay(strList.value(7));
        emit sendUpd(u);
    }
}

void server::receiveLog(user *u)
{
    if(u==nullptr){
        socket->write("LOG:falied");
    }
    else{
        int sex=u->getSex();
        QString temp="LOG:succeed:" + u->getNickName() +
                ":"+ u->getPassword() +
                ":"+ u->getPhoneNum() +
                ":"+ u->getUserName() +
                ":"+ u->getJob()      +
                ":"+ QString::number(sex) +
                ":"+ u->getBirthDay();

        socket->write(temp.toLocal8Bit());
    }
    socket->flush();
}


void server::receiveReg(QString res)
{
    if(res=="succeed"){
        socket->write("REG:succeed");
    }
    else{
        socket->write("REG:failed");
    }
    socket->flush();
}

void server::receiveUpdate(QString res)
{
    if(res=="succeed"){
        socket->write("UPD:succeed");
    }
    else{
        socket->write("UPD:failed");
    }
    socket->flush();
}
