#ifndef USER_H
#define USER_H
#include <QString>
#include <QCryptographicHash>
#include <QDebug>
#define cout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"

class User
{
public:
    User(QString id,QString password);
    QString getid() const;
    bool if_lock() const;
    int getnum_of_login() const;
    bool Lock();
    bool Login(QString id,QString password);
private:
    QString id;
    QString password;
    bool iflock;
    int num_of_login;
};

#endif // USER_H
