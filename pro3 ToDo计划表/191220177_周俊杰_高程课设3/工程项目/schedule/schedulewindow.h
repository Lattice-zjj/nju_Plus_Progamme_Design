#ifndef SCHEDULEWINDOW_H
#define SCHEDULEWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QMenu>
#include <QCloseEvent>
#include <QTableWidget>
#include <QDebug>
#include <QMediaPlayer>
#include <QDateTime>
#include <QDesktopServices>
#include <QTimer>
#include <QPainter>
#include <QVector>
#include <QString>
#include <fstream>
#include "musicplayer.h"
#define cout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"

class Notes{
public:
    QString name;
    int length_time;
    QString note;
    QDateTime start_time;
    int time_complete;
    Notes(){}
    Notes(QString n,int l,QString no,int time){name=n;length_time=l;note=no;time_complete=time;}
    ~Notes(){}
};

class MyMenu : public QMenu
{
    Q_OBJECT

public:
    explicit MyMenu(QWidget *parent = nullptr);
    ~MyMenu();

signals:
    // 自定义信号
    void showWindow();
    void closeWindow();
private:
    // 添加菜单项
    void initActions();

private:
    QAction *m_pShowAction;
    QAction *m_pSettingAction;
    QAction *m_pHelpAction;
    QAction *m_pAboutAction;
    QAction *m_pUpgradeAction;
    QAction *m_pQuitAction;

};
namespace Ui {
class ScheduleWindow;
}

class ScheduleWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ScheduleWindow(QWidget *parent = nullptr);
    ~ScheduleWindow();
    void closeEvent(QCloseEvent *event);
    void notclear_search(const QString &arg1,QTableWidget *p); //模糊搜索
private:
    void TxtIntodata();
    void DataIntotxt();
    void printAllNotes();
    void clearAll();
    void deletenote(QString name_of_note);
    QPair<bool,int> judgesame(QString name);
private slots:
    void onActivated(QSystemTrayIcon::ActivationReason reason);
    void showWindow();
    void closeWindow();
    void fromLoginWindow(QString name);
    void on_search_2_textChanged(const QString &arg1);
    void settimeline(); //设置时间
    void mySortByColumn2(int column);//用于表头排序的槽函数

    void on_stu_logout_clicked();

    void on_stu_inq_clicked();

    void on_stu_choosecourse_clicked();

    void on_SureModify_clicked();

    void on_delete_it_clicked();

    void on_note_change_clicked();

    void on_SureModify_2_clicked();

    void on_stu_person_clicked();
    void on_thisNotesDown();
    void on_pushButton_over_clicked();

    void on_pushButton_music_clicked();

    void on_pushButton_clicked();

signals:
    void toLoginWindow();//发出给登陆界面的
    void thisNotesDown();
protected:
    void paintEvent(QPaintEvent *);
private:
    Ui::ScheduleWindow *ui;
    bool exitwith;
    QString name;
    QVector<Notes> notes;
    QTimer* timelinetimer;
    QDateTime time_start;
    int middlename;
    bool ifbegin;
    QMediaPlayer mediaPlayer;
    QSystemTrayIcon *pSystemTray;
    MusicPlayer *musicplayer;
};

#endif // SCHEDULEWINDOW_H
