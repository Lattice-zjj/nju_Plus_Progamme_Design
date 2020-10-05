#include "musicplayer.h"
#include "ui_musicplayer.h"

MusicPlayer::MusicPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicPlayer)
{

    ui->setupUi(this);
    initFrameMenu();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    currentBkIdex=0;
    boundaryWidth=4;
    setAutoFillBackground(true);
    setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("background:#D1EEEE");
    setMouseTracking(true);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setOffset(1,1);
    effect->setColor(QColor(0,0,0,100));
    effect->setBlurRadius(15);
    ui->frame->setGraphicsEffect(effect);
    ui->frame->setAutoFillBackground(true);
    ui->verticalSlider->hide();
    ui->verticalSlider->setValue(100);
    setPushButton_volumnStyleSheet_have();
    setPushButton_coreStyleSheet_pause();

    QString listWidgetStyle1 = "QScrollBar:vertical"
                                  "{"
                                          "width:8px;"
                                          "background-color:transparent;"
                                          "margin:0px,0px,0px,0px;"
                                         " padding-top:12px;   "
                                         " padding-bottom:12px; "
                                      "}"


                                    "  QScrollBar::handle:vertical"
                                     " {"
                                          "width:8px;"
                                         " background-color:rgba(255,255,255,0.2);"
                                         " border-radius:4px;"
                                         " min-height:20px;"
                                     " }"


                                  "    QScrollBar::handle:vertical:hover"
                                   "   {"
                                    "      width:9px;"
                                         " background-color:rgba(255,255,255,0.5);"
                                       "   border-radius:4px;"
                                     "     min-height:20;"
                                    "  }"

                                    "  QScrollBar::add-line:vertical"
                                    "  {"
                                         " height:12px;"
                                     "     width:10px;"
                                  "        border-image:url(://image/down.png);"
                                         " subcontrol-position:bottom;"
                                  "    }"

                                  "    QScrollBar::sub-line:vertical"
                                  "    {"
                                  "        height:12px;"
                                          "width:10px;"
                                       "   border-image:url(://image/up.png);"
                                          "subcontrol-position:top;"
                                   "   }"
                                  "    QScrollBar::add-line:vertical:hover"
                                   "   {"
                                         " height:12px;"
                                          "width:10px;"
                                         " border-image:url(://image/down.png);"
                                          "subcontrol-position:bottom;"
                                     " }"


                                     " QScrollBar::sub-line:vertical:hover"
                                     " {"
                                     "     height:12px;"
                                        "  width:10px;"
                                        "  border-image:url(://image/up.png);"
                                         " subcontrol-position:top;"
                                     " }"

                                     " QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical"
                                     " {"
                                         " background-color:transparent;"
                                       "   border-radius:4px;"
                                      "}";
    QString listWidgetStyle2 = "QScrollBar:horizontal {"
            "background-color:transparent;"
            "height:8px;"
            "margin:0px 0px 0px 0px;"
            " padding-left:12px;   "
            " padding-right:12px; "
        "}"

        /* 滑动块设置 */
        "QScrollBar::handle:horizontal {"
            "height:8px;"
        " background-color:rgba(255,255,255,0.2);"
        " border-radius:4px;"
        "min-width:8px;"
        "}"
        "    QScrollBar::handle:horizontal:hover"
         "   {"
          "      height:9px;"
               " background-color:rgba(255,255,255,0.5);"
             "   border-radius:4px;"
           "     min-width:20;"
          "  }"

        " QScrollBar::add-page:horizontal,QScrollBar::sub-page:horizontal"
        " {"
            " background-color:transparent;"
          "   border-radius:4px;"
         "}"
            ;
    ui->listWidget->verticalScrollBar()->setStyleSheet(listWidgetStyle1);
    ui->listWidget->horizontalScrollBar()->setStyleSheet(listWidgetStyle2);
    QScrollBar *scrollbar=ui->listWidget->verticalScrollBar();
    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    scrollbar->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.5);
    music=new QMediaPlayer(this);
    playlist =new QMediaPlaylist(this);//本地音乐播放列表
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    playlist->setPlaybackMode(QMediaPlaylist::Sequential);
    music->setPlaylist(playlist);



    connect(music,&QMediaPlayer::positionChanged,this,&MusicPlayer::updatePosition);//播放的位置改变->更新进度条播放位置
    connect(music,&QMediaPlayer::durationChanged,this,&MusicPlayer::updateDuration);//播放歌曲改变->更新进度条

}

void MusicPlayer::DirectInputDefault()
{
    on_pushButton_clicked();
}

MusicPlayer::~MusicPlayer()
{
    delete ui;
}

void MusicPlayer::InitWithConnection()
{


}

void MusicPlayer::setPushButton_volumnStyleSheet_have()
{
    ui->pushButton_volumn->setStyleSheet("QPushButton"
                                         " {"
                                         "background-image:url(://image/image/music-voice.png);"
                                       "   background-repeat:no-repeat;"
                                        "  background-position:center center;"
                                       "   border:none;"
                                      "    }"

                                          "QPushButton:hover{"
                                        "  background-repeat:no-repeat;"
                                       "   background-position:center center;"
                                       "background-image:url(://image/image-hover/music-voice-hover.png);"

                                         " }"
                                         " QPushButton:pressed{"
                                          "background-repeat:no-repeat;"
                                         " background-position:center center;"
                                         " background-image:url(://image/image/music-voice.png);"

                                           "}");

}

void MusicPlayer::setPushButton_volumnStyleSheet_none()
{

    ui->pushButton_volumn->setStyleSheet("QPushButton"
                                         " {"
                                         "background-image:url(://image/image/none-music.png);"
                                       "   background-repeat:no-repeat;"
                                        "  background-position:center center;"
                                       "   border:none;"

                                      "    }"

                                          "QPushButton:hover{"
                                        "  background-repeat:no-repeat;"
                                       "   background-position:center center;"
                                       "background-image:url(://image/image-hover/none-music-hover.png);"

                                         " }"
                                         " QPushButton:pressed{"
                                          "background-repeat:no-repeat;"
                                         " background-position:center center;"
                                         " background-image:url(://image/image/none-music.png);"

                                         "}");
}

void MusicPlayer::setPushButton_coreStyleSheet_play()
{
    ui->pushButton_core->setStyleSheet("QPushButton"
                                       " {"
                                       "background-image:url(://image/bf.png);"
                                     "   background-repeat:no-repeat;"
                                      "  background-position:center center;"
                                     "   border:none;"

                                    "    }"

                                        "QPushButton:hover{"
                                      "  background-repeat:no-repeat;"
                                     "   background-position:center center;"
                                     "background-image:url(://image/image-hover/play-hover.png);"

                                       " }"
                                       " QPushButton:pressed{"
                                        "background-repeat:no-repeat;"
                                       " background-position:center center;"
                                       " background-image:url(://image/bf.png);"

                                         "}");
}

void MusicPlayer::setPushButton_coreStyleSheet_pause()
{
    ui->pushButton_core->setStyleSheet("QPushButton"
                                       " {"
                                       "background-image:url(://image/bofang.png);"
                                     "   background-repeat:no-repeat;"
                                      "  background-position:center center;"
                                     "   border:none;"

                                    "    }"

                                        "QPushButton:hover{"
                                      "  background-repeat:no-repeat;"
                                     "   background-position:center center;"
                                     "background-image:url(://image/image-hover/pase-hover.png);"

                                       " }"
                                       " QPushButton:pressed{"
                                        "background-repeat:no-repeat;"
                                       " background-position:center center;"
                                       " background-image:url(://image/bofang.png);"

                                         "}");
}

void MusicPlayer::on_pushButton_exit_clicked()
{
    music->pause();
    this->close();
}

void MusicPlayer::on_pushButton_volumn_clicked()
{
    if(ui->verticalSlider->isHidden()) {
        ui->verticalSlider->show();
    }
    else {
        ui->verticalSlider->hide();
    }
}

void MusicPlayer::on_verticalSlider_valueChanged(int value)
{

    if (value==0){//音量变成0
        setPushButton_volumnStyleSheet_none();
    }else{
        setPushButton_volumnStyleSheet_have();
    }
   if (music!=nullptr) music->setVolume(value);
}

void MusicPlayer::on_pushButton_mini_clicked()
{
    showMinimized();
}
void MusicPlayer::mousePressEvent(QMouseEvent *event){
    if(event->buttons()==Qt::LeftButton)
    {
        dragPosition=event->globalPos()-frameGeometry().topLeft();
        event->accept();
    }
}

void MusicPlayer::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        this ->move(event->globalPos() - dragPosition);
        event->accept();
    }
}
void MusicPlayer::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        QPoint temp=event->globalPos() - dragPosition;
        if(temp.x()<QApplication::desktop()->x()) { //吸附于屏幕左侧
            temp.setX(QApplication::desktop()->x());
        }
        else if (temp.x()+this->width()>QApplication::desktop()->width()) { //吸附于屏幕右侧
            temp.setX(QApplication::desktop()->width()-this->width());
        }
        if(temp.y()<QApplication::desktop()->y()) { //吸附于屏幕顶部
            temp.setY(QApplication::desktop()->y());
        }
        this ->move(temp);
        event->accept();
    }

}

void MusicPlayer::on_pushButton_core_clicked()
{
    if (playlist->mediaCount()==0){
        QMessageBox::warning(this,"警告","您还没有添加mp3文件！");
        return;
    }
    if(music->state()==QMediaPlayer::PlayingState){
        setPushButton_coreStyleSheet_pause();
        music->pause();
   }
   else {
        setPushButton_coreStyleSheet_play();
        music->play();
   }
}

void MusicPlayer::on_pushButton_clicked()
{

    QString mFolderPath="./music/music";
    QStringList pathList;
    if (mFolderPath.isEmpty()) return;
    // 获取所有文件名

    QDir dir(mFolderPath);
    mFolderPath = dir.fromNativeSeparators(mFolderPath);//  "\\"转为"/"
    if (!dir.exists()) pathList = QStringList("");
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Name);
    dir.setNameFilters(QString("*.mp3;*.mp4").split(";"));
    pathList = dir.entryList();
    addMusicToList(mFolderPath+"/",pathList);
}


void MusicPlayer::on_pushButton_pre_clicked()
{
    int currentIndex = playlist->currentIndex();
    if(--currentIndex<0) currentIndex = ui->listWidget->count() - 1;
    playlist->setCurrentIndex(currentIndex);
    setPushButton_coreStyleSheet_play();
    music->play();
}

void MusicPlayer::on_pushButton_nxt_clicked()
{
    int currentIndex=playlist->currentIndex();
    if(++currentIndex==playlist->mediaCount())
    currentIndex=0;
    playlist->setCurrentIndex(currentIndex);
    setPushButton_coreStyleSheet_play();
    music->play();
}



void MusicPlayer::on_horizontalSlider_sliderMoved(int position)
{
    music->setPosition(position);
}


void MusicPlayer::updatePosition(int position){
    ui->horizontalSlider->setValue(position);
    ui->label_time->setText(Time(position)+"/"+Time(music->duration()));
}

void MusicPlayer::updateDuration(int duration)//更新播放进度
{
    ui->horizontalSlider->setRange(0,duration);
    ui->horizontalSlider->setEnabled(duration>0);
    ui->horizontalSlider->setPageStep(duration/10);
}

QString MusicPlayer::Time(qint64 time)//转换时间
{
    qint64 seconds=time/1000;
    const qint64 minutes=seconds/60;
    seconds-=minutes*60;
    return QStringLiteral("%1:%2").arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0'));
}

bool MusicPlayer::JudgeIfRepeat(QString path)
{
    for (int i=0;i<playlist->mediaCount();i++){
        if (path==playlist->media(i).canonicalUrl().path()) return true;
    }
    return false;
}

void MusicPlayer::addMusicToList(QString mFolderPath,QStringList pathList)
{
    for(int i=0; i<pathList.size(); ++i) {
        QString path=QDir::toNativeSeparators(mFolderPath+pathList.at(i));
        if(!path.isEmpty()) {
            if (JudgeIfRepeat(path)) continue;
            playlist->addMedia(QUrl::fromLocalFile(path));
            QString fileName=path.split("\\").last();
            QListWidgetItem *item1=new QListWidgetItem;
            item1->setIcon(QIcon("://image/music.png"));
            item1->setText(fileName);
            ui->listWidget->addItem(item1);
        }
    }
}

void MusicPlayer::initFrameMenu()
{
    action_nxt_bk=new QAction(this);
    action_nxt_bk->setIcon(QIcon("://image/image-hover/like-hover.png"));
    action_nxt_bk->setText("下一个背景");
    action_change_transparency=new QAction(this);
    action_change_transparency->setIcon(QIcon("://image/tran.png"));
    action_change_transparency->setText("歌曲选择");
    action_tra_ad=new QAction(this);
    action_tra_ad->setIcon(QIcon("://image/image/pre.png"));
    action_tra_ad->setText("上一首");
    action_tra_de=new QAction(this);
    action_tra_de->setIcon(QIcon("://image/image/next.png"));
    action_tra_de->setText("下一首");
    QMenu *middlemenu=new QMenu(this);
    middlemenu->setStyleSheet(" QMenu {"
                        " background: white; "
                            "border-radius:2px;"
                         "border:1px solid rgb(200,200,200);"

                   "  }"
                   "  QMenu::item {"

                        " background-color: transparent;"
                        " padding:5px 30px;"
                  "       margin:0px 0px;"
                        " border-bottom:0px solid #DBDBDB;"
                     "}"
                    " QMenu::item:selected { "
                         "background-color: aqua;"
                     "}");
    middlemenu->addAction(action_tra_ad);
    middlemenu->addSeparator();
    middlemenu->addAction(action_tra_de);
    action_change_transparency->setMenu(middlemenu);
    connect(action_nxt_bk,&QAction::triggered,this,&MusicPlayer::on_action_nxt_bk_clicked);
    connect(action_tra_ad,&QAction::triggered,this,&MusicPlayer::on_action_tra_ad_clicked);
    connect(action_tra_de,&QAction::triggered,this,&MusicPlayer::on_action_tra_de_clicked);
}

void MusicPlayer::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    for (int i=0;i<playlist->mediaCount();i++){
        QString path=playlist->media(i).canonicalUrl().url();
        QString fileName=path.split("/").last();
        if (fileName==item->text()){
            playlist->setCurrentIndex(i);
            setPushButton_coreStyleSheet_play();
            music->play();
        }
    }
}

void MusicPlayer::on_pushButton_list_clicked()
{
    if (ui->listWidget->isHidden()) ui->listWidget->show(); else ui->listWidget->hide();
}

void MusicPlayer::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    if(ui->listWidget->itemAt(pos)==nullptr) return;
    menu=new QMenu(this);
    menu->setStyleSheet(" QMenu {"
                        " background: white; "
                            "border-radius:2px;"
                         "border:1px solid rgb(200,200,200);"

                   "  }"
                   "  QMenu::item {"

                        " background-color: transparent;"
                        " padding:5px 30px;"
                  "       margin:0px 0px;"
                        " border-bottom:0px solid #DBDBDB;"
                     "}"
                    " QMenu::item:selected { "
                         "background-color: aqua;"
                     "}");
    action_delete=new QAction(this);
    action_delete->setIcon(QIcon("://image/image/position.png"));
    action_delete->setText("删除");
    menu->addAction(action_delete);
    connect(action_delete,&QAction::triggered,this,&MusicPlayer::on_action_delete_clicked);
    menu->exec(QCursor::pos());

}

void MusicPlayer::on_pushButton_self_clicked()
{
    QStringList pathList=QFileDialog::getOpenFileNames(this, tr("选择文件"),"./", tr("*.mp3"));
    addMusicToList("",pathList);
}

void MusicPlayer::on_action_delete_clicked()
{
    int Row=playlist->currentIndex();
    int row=ui->listWidget->currentIndex().row();
    if (Row==row) playlist->setCurrentIndex(0);
    delete ui->listWidget->takeItem(row);
    playlist->removeMedia(row,row);
    setPushButton_coreStyleSheet_play();
    music->play();
}

void MusicPlayer::on_action_nxt_bk_clicked()
{
    currentBkIdex=qrand()%9;
    QString pathname="://image/background/bg"+QString::number(currentBkIdex)+".jpg";
    ui->frame->setStyleSheet(QString("QFrame#frame{border-radius:5px;border-image: url(%1);}").arg(pathname));
}

void MusicPlayer::on_pushButton_maxi_clicked()
{
    this->setWindowFlags(this->windowFlags()& ~Qt::WindowMaximizeButtonHint& ~Qt::WindowMinimizeButtonHint);
    this->showMaximized();
    this->move(0,0);
}

void MusicPlayer::on_frame_customContextMenuRequested(const QPoint &pos)
{

}


void MusicPlayer::contextMenuEvent(QContextMenuEvent *){
    menu_frame=new QMenu(this);
    menu_frame->setStyleSheet(" QMenu {"
                        " background: white; "
                            "border-radius:2px;"
                         "border:1px solid rgb(200,200,200);"

                   "  }"
                   "  QMenu::item {"

                        " background-color: transparent;"
                        " padding:5px 30px;"
                  "       margin:0px 0px;"
                        " border-bottom:0px solid #DBDBDB;"
                     "}"
                    " QMenu::item:selected { "
                         "background-color: aqua;"
                     "}");
    menu_frame->addAction(action_change_transparency);
    menu_frame->addAction(action_nxt_bk);
    menu_frame->exec(QCursor::pos());
}


bool MusicPlayer::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = (MSG*)message;
    switch(msg->message)
        {
        case WM_NCHITTEST:
            int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
            int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
            if(xPos < boundaryWidth && yPos<boundaryWidth)                    //左上角
                *result = HTTOPLEFT;
            else if(xPos>=width()-boundaryWidth&&yPos<boundaryWidth)          //右上角
                *result = HTTOPRIGHT;
            else if(xPos<boundaryWidth&&yPos>=height()-boundaryWidth)         //左下角
                *result = HTBOTTOMLEFT;
            else if(xPos>=width()-boundaryWidth&&yPos>=height()-boundaryWidth)//右下角
                *result = HTBOTTOMRIGHT;
            else if(xPos < boundaryWidth)                                     //左边
                *result =  HTLEFT;
            else if(xPos>=width()-boundaryWidth)                              //右边
                *result = HTRIGHT;
            else if(yPos<boundaryWidth)                                       //上边
                *result = HTTOP;
            else if(yPos>=height()-boundaryWidth)                             //下边
                *result = HTBOTTOM;
            else              //其他部分不做处理，返回false，留给其他事件处理器处理
               return false;
            return true;
        }
        return false;         //此处返回false，留给其他事件处理器处理
}

void MusicPlayer::on_action_tra_ad_clicked()
{
    on_pushButton_pre_clicked();
}

void MusicPlayer::on_action_tra_de_clicked()
{
    on_pushButton_nxt_clicked();
}

void MusicPlayer::on_pushButton_down_clicked()
{
    this->resize(698,414);
}
