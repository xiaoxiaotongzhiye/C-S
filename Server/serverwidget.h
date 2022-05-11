#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QPushButton>
#include <QDebug>
#include <QtSql>
#include <QString>
#include <QMessageBox>
#include "server.h"
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ServerWidget; }
QT_END_NAMESPACE

class ServerWidget : public QMainWindow
{
    Q_OBJECT

public:
    ServerWidget(QWidget *parent = nullptr);
    ~ServerWidget();

private slots:
    void getMessage(QString);
    void getReg(user *);
    void getLog(user *);
    void getUpd(user *);

signals:
    void sendLog(user *);
    void sendUpdate(QString);
    void sendReg(QString);



private:
    Ui::ServerWidget *ui;
    server *svr;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
};
#endif // SERVERWIDGET_H
