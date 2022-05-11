#ifndef USER_H
#define USER_H

#include <QObject>

class user : public QObject
{
    Q_OBJECT
public:
     user();

    void setNickName(QString);
    QString getNickName();

    void setPassword(QString);
    QString getPassword();

    void setPhoneNum(QString);
    QString getPhoneNum();

    void setUserName(QString);
    QString getUserName();

    void setSex(int);
    int getSex();

    void setJob(QString);
    QString getJob();

    void setBirthDay(QString);
    QString getBirthDay();

private:
    QString nickName;
    QString password;
    QString phoneNum;
    QString userName;
    int sex;
    QString job;
    QString birthDay;

signals:

};

#endif // USER_H
