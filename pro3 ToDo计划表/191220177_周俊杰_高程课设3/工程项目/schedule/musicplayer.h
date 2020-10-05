#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QtWin>
#include <QMenu>
#include <QWinThumbnailToolBar>
#include <QWinThumbnailToolButton>
#include <QListWidgetItem>
#include <QListWidget>

#include <windows.h>        //注意头文件
#include <windowsx.h>

#include <QWinTaskbarButton>
#include <qlistwidget.h>
#include <QTime>
#include <QMessageBox>
#include <QWinTaskbarProgress>
#include <QAction>
#include <QDir>
#include <QFileDialog>
#include <QVector>
#include <QActionEvent>
#include <QActionGroup>
#include <QList>
#include <QString>
#include <QStringLiteral>
#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPixmap>
#include <QPalette>
#include <QScrollBar>
#include <QGraphicsOpacityEffect>
#include <QDesktopWidget>
#include <dwmapi.h>
#include <windowsx.h>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QAction>
#include <QtWinExtras>
#include <QMouseEvent>
#include <QList>
#include <QStringList>
#include <QPaintEvent>
#include <QSqlTableModel>
#include <QPropertyAnimation>
namespace Ui {
class MusicPlayer;
}

class MusicPlayer : public QWidget
{
    Q_OBJECT
private:
    void InitWithConnection();
    //void setResizeCursor(ResizeRegion region);
    //ResizeRegion getResizeRegion(QPoint clientPos);
    //void handleResize();
    void setPushButton_volumnStyleSheet_have();
    void setPushButton_volumnStyleSheet_none();
    void setPushButton_coreStyleSheet_play();
    void setPushButton_coreStyleSheet_pause();
    static QString Time(qint64 time);
    bool JudgeIfRepeat(QString path);
    void addMusicToList(QString,QStringList);
    void initFrameMenu();
public:
    explicit MusicPlayer(QWidget *parent = nullptr);
    void DirectInputDefault();
    ~MusicPlayer();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_volumn_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_pushButton_mini_clicked();
    //void on_pushButton_pre_clicked();

    void on_pushButton_core_clicked();

    void on_pushButton_clicked();

    void on_pushButton_pre_clicked();

    void on_pushButton_nxt_clicked();

    void on_horizontalSlider_sliderMoved(int position);
    void updatePosition(int position);
    void updateDuration(int position);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_list_clicked();

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

    void on_pushButton_self_clicked();
    void on_action_delete_clicked();
    void on_action_nxt_bk_clicked();
    void on_pushButton_maxi_clicked();

    void on_frame_customContextMenuRequested(const QPoint &pos);
    void on_action_tra_ad_clicked();
    void on_action_tra_de_clicked();

    void on_pushButton_down_clicked();

protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::MusicPlayer *ui;
    QPoint dragPosition;



    QMediaPlayer *music=nullptr;//音乐
    int boundaryWidth;
    QMediaPlaylist *playlist=nullptr;//播放列表


    int currentBkIdex;
    QMenu *menu;
    QMenu *menu_frame;
    QAction *action_delete;
    QAction *action_nxt_bk;
    QAction *action_tra_ad;
    QAction *action_tra_de;
    QAction *action_change_transparency;



};

#endif // MUSICPLAYER_H
