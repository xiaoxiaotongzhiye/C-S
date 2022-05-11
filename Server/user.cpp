#include "user.h"

user::user()
{

}

void user::setNickName(QString nickName)
{
    this->nickName = nickName;
}
QString user::getNickName()
{
    return nickName;
}


void user::setPassword(QString password)
{
    this->password = password;
}
QString user::getPassword()
{
    return password;
}


void user::setPhoneNum(QString phoneNum)
{
    this->phoneNum = phoneNum;
}
QString user::getPhoneNum()
{
    return phoneNum;
}


void user::setUserName(QString userName)
{
    this->userName = userName;
}
QString user::getUserName()
{
    return userName;
}


void user::setSex(int sex)
{
    this->sex=sex;;
}
int user::getSex()
{
    return sex;
}


void user::setJob(QString job)
{
    this->job = job;
}
QString user::getJob()
{
    return job;
}


void user::setBirthDay(QString birthDay)
{
    this->birthDay = birthDay;
}

QString user::getBirthDay()
{
    return birthDay;
}
