#include "user.h"

User::User(QString id,QString password)
{
    this->id=id;this->password=password;
    iflock=false;num_of_login=0;
}


QString User::getid() const{
    return this->id;
}
int User::getnum_of_login() const{
    return num_of_login;
}
bool User::if_lock() const{
    return this->iflock;
}
bool User::Lock(){
    iflock=true;num_of_login=0;return true;
}
bool User::Login(QString id,QString password){
    QByteArray byte_array=password.toUtf8();
    QByteArray hash_byte_array=QCryptographicHash::hash(byte_array,QCryptographicHash::Md5);
    QString Md5code=hash_byte_array.toHex();
    if (this->id==id && this->password==Md5code) {
        num_of_login=0;
        return true;
    }
    else {
        if (this->id==id){
            num_of_login++;
        }
        return false;
    }
}
