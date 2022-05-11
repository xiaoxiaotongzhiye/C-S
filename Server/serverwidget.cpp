#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ServerWidget)
{
    ui->setupUi(this);

    //连接数据库
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("xxx");
    db.setUserName("root");
    db.setPassword("123456");
    bool ok = db.open();
    if(ok){
        QMessageBox::information(this,"infor",QString::fromLocal8Bit("数据库连接成功"));
    }
    else{
        QMessageBox::information(this,"infor","failed");
        qDebug()<<"error open database"<<db.lastError().text();
    }

    //监听TCP端口
    svr = new server(1234);

    //客户端连接信号
    connect(svr,SIGNAL(sendMessage(QString)),this,SLOT(getMessage(QString)));

    //连接接收注册信号和注册槽函数
    connect(svr,SIGNAL(sendReg(user *)),this,SLOT(getReg(user *)));

    //连接接收登录信号和槽函数
    connect(svr,SIGNAL(sendLog(user *)),this,SLOT(getLog(user *)));

    //接收修改信号
    connect(svr,SIGNAL(sendUpd(user *)),this,SLOT(getUpd(user *)));

    //连接反馈登录信号和服务器返回处理槽函数
    connect(this,SIGNAL(sendLog(user *)),svr,SLOT(receiveLog(user *)));

    //反馈注册信号
    connect(this,SIGNAL(sendReg(QString)),svr,SLOT(receiveReg(QString)));

    //反馈修改信号
    connect(this,SIGNAL(sendUpdate(QString)),svr,SLOT(receiveUpdate(QString)));
}

void ServerWidget::getReg(user *u)
{
    QSqlQuery que(db);
    QString insert = "insert into user(nickName,password,phoneNum,userName,job,sex,birth) values";
    insert += QString::fromLocal8Bit("('%1','%2','%3','%4','%5','%6','%7')")
               .arg(u->getNickName())
               .arg(u->getPassword())
               .arg(u->getPhoneNum())
               .arg(u->getUserName())
               .arg(u->getJob())
               .arg(u->getSex())
               .arg(u->getBirthDay());

    bool okk = que.exec(insert);
    if(okk){
        emit sendReg("succeed");
    }
    else{
        qDebug() << que.lastError();
        emit sendReg("failed");
    }
}

void ServerWidget::getLog(user *u){

    QString select = "select * from user where nickName='"+u->getNickName()+"'";
    QSqlQuery que=db.exec(select);
    if(que.next()){
        if(que.value("password").toString()==u->getPassword()){
            u->setJob(que.value("job").toString());
            u->setSex(que.value("sex").toInt());
            u->setBirthDay(que.value("birth").toString());
            u->setUserName(que.value("userName").toString());
            u->setPhoneNum(que.value("phoneNum").toString());
            emit sendLog(u);
        }
        else
        {
            emit sendLog(nullptr);
        }
    }
    else{
        emit sendLog(nullptr);
    }
}

void ServerWidget::getUpd(user *u)
{
    QSqlQuery que(db);
    QString update = QString::fromLocal8Bit("update user set password='%1',phoneNum='%2',userName='%3',job='%4',sex='%5',birth='%6' where nickName='%7'")
               .arg(u->getPassword())
               .arg(u->getPhoneNum())
               .arg(u->getUserName())
               .arg(u->getJob())
               .arg(u->getSex())
               .arg(u->getBirthDay())
               .arg(u->getNickName());
    bool okk = que.exec(update);
    if(okk){
        emit sendUpdate("succeed");
    }
    else{
        qDebug() << que.lastError();
        emit sendUpdate("failed");
    }
}


ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::getMessage(QString str)
{
    qDebug() << str;
}

