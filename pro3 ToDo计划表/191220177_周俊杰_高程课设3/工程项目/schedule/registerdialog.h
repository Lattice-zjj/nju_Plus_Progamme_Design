#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <QPainter>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QVector>
#include <QFile>
#include <QPair>
#include "user.h"
#include "schedulewindow.h"
#define cout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"
namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();
    void clearAll();
private slots:
    void fromLoginWindow();//从登陆界面接受到的信号
    void loginbtnSetSlot(QString);
    void settimeline();//设置时间
    void on_register_s_4_clicked();
    void on_back_to_4_clicked();

protected:
    void paintEvent(QPaintEvent *);//画图虚函数
signals:
    //void toStudentWindow();//发给界面的
    void toLoginWindow();//发出给登陆界面的
    void toScheduleWindow(QString);
private:
    Ui::RegisterDialog *ui;
    QTimer* timelinetimer;//计时器
    QVector<QPair<QString,QString>> data;
    ScheduleWindow* user;
};

#endif // REGISTERDIALOG_H
