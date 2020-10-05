#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDesktopServices>
#include <QTime>
#include <QFile>
#include <QCompleter>
#include <QPainter>
#include <QVector>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QUrl>
#include "user.h"
#include "registerdialog.h"
#include "schedulewindow.h"
#define cout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"
namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    bool judgeEmpty();//判断lineedit中是否为空
    void clearAll();//将所有的lineedit中清空
    void UpInfor();//从文件中读取数据到内存中

private slots:
    void on_yanzhenglabel_clicked();
    void loginbtnSetSlot(QString); //登陆键按下的槽函数
    void settimeline(); //设置时间
    void on_loginbtn_clicked();
    void on_userline_textEdited(const QString &arg1);
    void on_registerbtn_clicked();
signals:
    void toRegisterWindow();
    void toScheduleWindow(QString);
protected:
    void paintEvent(QPaintEvent * );
private:
    Ui::LoginWindow *ui;
    int num_yan;
    QVector<QString> history;
    QTimer *timelinetimer;
    QTimer *timer;
    QVector<User*> data;
    RegisterDialog *reg;
    ScheduleWindow *user;
};

#endif // LOGINWINDOW_H
