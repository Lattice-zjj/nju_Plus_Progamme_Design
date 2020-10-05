#include "schedulewindow.h"
#include "ui_schedulewindow.h"
MyMenu::MyMenu(QWidget *parent)
    : QMenu(parent)
{
    initActions();
}

MyMenu::~MyMenu()
{
    delete  m_pShowAction;
    delete m_pSettingAction;
    delete m_pHelpAction;
    delete m_pAboutAction;
    delete m_pUpgradeAction;
    delete m_pQuitAction;
}

// 添加菜单项
void MyMenu::initActions()
{
    // 创建菜单项
    m_pShowAction = new QAction(QIcon(":/icon/open"), QString("显示"), this);
    m_pSettingAction = new QAction(QIcon(":/icon/setting"), QString("设置"), this);
    m_pHelpAction= new QAction(QIcon(":/icon/help"), QString("帮助"), this);
    m_pAboutAction = new QAction(QIcon(":/icon/about"), QString("关于"), this);
    //m_pUpgradeAction = new QAction(QIcon(":/icon/upgrade"), QString("检查更新"), this);
    m_pQuitAction = new QAction(QIcon(":/icon/quit"), QString("退出"), this);

    // 添加菜单项
    addAction(m_pShowAction);
    addAction(m_pSettingAction);
    addSeparator();
    addAction(m_pHelpAction);
    addAction(m_pAboutAction);
    //addAction(m_pUpgradeAction);
    addSeparator();
    addAction(m_pQuitAction);

    // 连接信号-信号（仅列举连接显示窗口的信号）
    connect(m_pShowAction, SIGNAL(triggered(bool)), this, SIGNAL(showWindow()));
    connect(m_pQuitAction, SIGNAL(triggered(bool)), this, SIGNAL(closeWindow()));
}


ScheduleWindow::ScheduleWindow(QWidget *parent) :
    QMainWindow (parent),
    ui(new Ui::ScheduleWindow)
{
    exitwith=false;
    ifbegin=false;
    ui->setupUi(this);
    this->setMaximumSize(640,480);
    this->setMinimumSize(640,480);
    this->setWindowIcon(QIcon("://image/1.png"));
    QString str="Superego Todo ["+name+"]";
    setWindowTitle(str);
    pSystemTray = new QSystemTrayIcon(this);
    MyMenu *pTrayMenu = new MyMenu(this);

    // 设置系统托盘的上下文菜单
    pSystemTray->setContextMenu(pTrayMenu);

    // 设置系统托盘提示信息、托盘图标
    pSystemTray->setToolTip(QString("Superego Todo"));
    pSystemTray->setIcon(QIcon("://image/8.png"));

    // 连接信号槽

    connect(pTrayMenu, SIGNAL(showWindow()), this, SLOT(showWindow()));
    connect(pTrayMenu, SIGNAL(closeWindow()), this, SLOT(closeWindow()));
    connect(pSystemTray , SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onActivated(QSystemTrayIcon::ActivationReason)));

    // 显示系统托盘
    pSystemTray->show();

    // 显示系统托盘提示信息
    pSystemTray->showMessage(QString("Superego Todo"), QString("Superego Todo已经开始运行~"));
    /*
     *
    connect(ui->actiona,&QAction::triggered,
            [=](){ QDesktopServices::openUrl (QUrl::fromLocalFile("./HelpFile/HelpFile.pdf"));
    });
    connect(ui->actionb,&QAction::triggered,
            [=](){ ui->stackedWidget_3->setCurrentWidget(ui->page_s_2);
    });
    connect(ui->actionc,&QAction::triggered,this,&QMainWindow::close);*/
    connect(this,&ScheduleWindow::thisNotesDown,this,&ScheduleWindow::on_thisNotesDown);
    ui->label_10->setStyleSheet("font-size:12px;color:black");
    //ui->label_11->setStyleSheet("font-size:12px;color:black");
    //ui->label_12->setStyleSheet("font-size:12px;color:black");
    //ui->label_13->setStyleSheet("font-size:12px;color:black");
    //ui->label_14->setStyleSheet("font-size:12px;color:white");
    ui->label->setStyleSheet("font-size:12px;color:white");
    ui->label_2->setStyleSheet("font-size:12px;color:white");
    ui->label_name->setStyleSheet("background-color:rgb(23,234,0);font-size:15px;color:blue");
    ui->label_note->setStyleSheet("background-color:rgb(23,234,0);font-size:15px;color:blue");
    ui->label_time->setStyleSheet("background-color:rgb(23,234,0);font-size:15px;color:blue");
    ui->label_name_2->setStyleSheet("background-color:rgb(23,234,0);font-size:15px;color:blue");
    ui->label_note_2->setStyleSheet("background-color:rgb(23,234,0);font-size:15px;color:blue");
    ui->label_time_2->setStyleSheet("background-color:rgb(23,234,0);font-size:15px;color:blue");


    //ui->label_time_3->setStyleSheet("background-color:rgb(23,234,0);font-size:15px;color:blue");
    //ui->display_ass->setStyleSheet("font-size:12px;color:black");
    QFont font ("Microsoft YaHei",3,75);
    ui->label_10->setFont(font);
    //ui->label_11->setFont(font);
    //ui->label_12->setFont(font);
    //ui->label_13->setFont(font);
    //ui->label_14->setFont(font);
    ui->label->setFont(font);
    ui->label_name->setFont(font);
    ui->label_time->setFont(font);
    ui->label_note->setFont(font);
    ui->label_2->setFont(font);
    //ui->display_ass->setFont(font);
    ui->search_2->setPlaceholderText("模糊搜索......");
    QString btnStyle="QPushButton{\
                color: rgb(255, 255, 255);\
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(166,164,208), stop:0.3 rgb(171,152,230), stop:1 rgb(152,140,220));\
                border:1px;\
                border-radius:5px; \
                padding:2px 4px;  \
            }\
            QPushButton:hover{\
                color: rgb(255, 255, 255); \
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(130,0,226), stop:0.3 rgb(120,0,230), stop:1 rgb(125,0,226));\
                border:1px;  \
                border-radius:5px; \
                padding:2px 4px; \
            }\
            QPushButton:pressed{    \
                color: rgb(255, 255, 255); \
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(240,156,121), stop:0.3 rgb(220,160,140), stop:1 rgb(230,140,120));  \
                border:1px;  \
                border-radius:5px; \
                padding:2px 4px; \
            }";
    //ui->stu_chooseass->setStyleSheet(btnStyle);
    ui->stu_choosecourse->setStyleSheet(btnStyle);
    ui->delete_it->setStyleSheet(btnStyle);
    //ui->stu_dele->setStyleSheet(btnStyle);
    ui->stu_inq->setStyleSheet(btnStyle);
    ui->stu_logout->setStyleSheet(btnStyle);
    ui->stu_person->setStyleSheet(btnStyle);
    //ui->stu_signforass->setStyleSheet(btnStyle);
    ui->modify_pas->setStyleSheet(btnStyle);
    ui->note_change->setStyleSheet(btnStyle);
    ui->SureModify->setStyleSheet(btnStyle);
    ui->SureModify_2->setStyleSheet(btnStyle);
    //ui->detele_s->setStyleSheet(btnStyle);
    //ui->signforass->setStyleSheet(btnStyle);
    //ui->search_ass->setStyleSheet(btnStyle);
    //ui->choose_ass->setStyleSheet(btnStyle);
    ui->tableWidget_s_1->clearContents();
    ui->idenline->setStyleSheet("font-size:16px;color:yellow");
    ui->timeline->setStyleSheet("font-size:16px;color:blue");
    ui->timeline->setFont(font);
    ui->idenline->setFont(font);

    ui->pass_past->setPlaceholderText("请输入初始密码");
    ui->pass_now->setPlaceholderText("请输入要修改成的密码");
    ui->pass_nowa->setPlaceholderText("请输入要修改成的密码");//设置lineedit提示语句
    ui->pass_now->setEchoMode(QLineEdit::Password);  //设置passlineedit显示为密码模式
    ui->pass_nowa->setEchoMode(QLineEdit::Password);  //设置passlineedit显示为密码模式


    ui->spinBox->setRange(20,180);
    ui->spinBox->setSingleStep(10);
    ui->spinBox->setSuffix("min");
    ui->spinBox_2->setRange(20,180);
    ui->spinBox_2->setSingleStep(10);
    ui->spinBox_2->setSuffix("min");
    ui->horizontalSlider_2->setOrientation(Qt::Horizontal);
    ui->horizontalSlider_2->setMinimum(20);
    ui->horizontalSlider_2->setMaximum(180);
    ui->horizontalSlider_2->setPageStep(10);
    ui->horizontalSlider_2->setTickInterval(10);  // 设置刻度间隔
    ui->horizontalSlider_2->setTickPosition(QSlider::TicksAbove);  //刻度在上方
    ui->horizontalSlider->setMinimum(20);
    ui->horizontalSlider->setMaximum(180);
    ui->horizontalSlider->setPageStep(10);
    ui->horizontalSlider->setTickInterval(10);  // 设置刻度间隔
    ui->horizontalSlider->setTickPosition(QSlider::TicksAbove);  //刻度在上方
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->spinBox_2, SLOT(setValue(int)));
    connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)), ui->spinBox, SLOT(setValue(int)));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), ui->horizontalSlider_2, SLOT(setValue(int)));
    connect(ui->spinBox_2, SIGNAL(valueChanged(int)), ui->horizontalSlider, SLOT(setValue(int)));
    //设置定时器
    timelinetimer=new QTimer(this);
    timelinetimer->setInterval(100);
    timelinetimer->start();
    connect(timelinetimer,SIGNAL(timeout()),this,SLOT(settimeline()));

    connect(ui->tableWidget_s_1->horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(mySortByColumn2(int)));
    TxtIntodata();
    printAllNotes();
    ui->pushButton_over->setStyleSheet("border-image:url(://image/bf.png);");
    ui->pushButton_music->setStyleSheet("border-image:url(://image/music.png);");
}

ScheduleWindow::~ScheduleWindow()
{
    delete ui;
}

// 显示窗体
void ScheduleWindow::showWindow()
{
    showNormal();
    raise();
    activateWindow();
}
void ScheduleWindow::closeWindow(){
    exitwith=true;
    this->close();
}
void ScheduleWindow::fromLoginWindow(QString name){
    this->name=name;
    QString str="Superego Todo ["+name+"]";
    setWindowTitle(str);
}
// 激活系统托盘
void ScheduleWindow::onActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    // 单击托盘显示窗口
    case QSystemTrayIcon::Trigger:
    {
        showNormal();
        raise();
        activateWindow();
        break;
    }
    // 双击
    case QSystemTrayIcon::DoubleClick:
    {
        // ...
        break;
    }
    default:
        break;
    }
}

void ScheduleWindow::closeEvent(QCloseEvent *event) //系统自带退出确定程序
{
    if (exitwith) {
        event->accept();
    }
    else{
        int choose;
        choose= QMessageBox::question(this, tr("退出程序"),
                                        QString(tr("确认退出程序?(Yes表示直接退出,Save表示最小化到托盘)")),
                                        QMessageBox::Save | QMessageBox::Yes);

        if (choose== QMessageBox::Save)
        {
            this->hide();
            event->ignore();
        }
        else if (choose== QMessageBox::Yes)
        {
            event->accept();
        }
    }
}
void ScheduleWindow::TxtIntodata(){
    QFile file;
    QString st="./data/"+name+".dat";
    file.setFileName(st);
    bool isOK=file.open(QIODevice::ReadOnly);
    if (isOK){
        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        while (stream.atEnd()==false){
            QString str,st1;
            int y,z;
            QString stt=stream.readLine(256);
            QList<QString> l=stt.split("\t");
            str=l.at(0);z=l.at(1).toInt();y=l.at(2).toInt();
            if (l.size()>3) st1=l.at(3);
            if (str!=""){
                cout<<str<<y<<st1<<z;
                Notes t(str,y,st1,z);
                notes.push_back(t);
            }
        }
        file.close();
    }
    for (int i=0;i<notes.size();i++){
        cout<<notes[i].name<<notes[i].note<<notes[i].length_time<<notes[i].time_complete;
    }
}
void ScheduleWindow::DataIntotxt(){
    QString st="./data/"+name+".dat";
    QFile file1;
    file1.setFileName(st);
    bool isOK1=file1.open(QIODevice::WriteOnly);
    if (isOK1 == false) {
        cout<<"打开失败！";
    }
    else {
        QTextStream stream1(&file1);
        stream1.setCodec("UTF-8");
        for (int i=0;i<notes.size();i++){
            if (notes[i].length_time != 0) {
                stream1<<notes[i].name<<"\t"<<notes[i].length_time<<"\t"<<notes[i].time_complete<<"\t"<<notes[i].note<<"\r\n";
            }
        }
        file1.close();
    }
}

void ScheduleWindow::on_search_2_textChanged(const QString &arg1)
{
    notclear_search(arg1,ui->tableWidget_s_1);
}

void ScheduleWindow::notclear_search(const QString &arg1,QTableWidget *p){//模糊搜索的通用函数
    if (arg1.isEmpty()){
        int rowCount=p->rowCount();
        for (int row=0;row<rowCount;row++){
            p->showRow(row);
        }
        return;
    }

    int rowCount=p->rowCount();
    int columnCount=p->columnCount();
    for (int row=0;row<rowCount;row++){
        QString rowData;
        for (int column=0;column<columnCount;column++){
            if (p->item(row,column)){
                rowData+=p->item(row,column)->text();
            }
        }
        if (!rowData.isEmpty()){
            if (rowData.contains(arg1)){
                p->showRow(row);
            }else{
                p->hideRow(row);
            }
        }
        else{
           p->hideRow(row);
        }
    }
}

void ScheduleWindow::paintEvent(QPaintEvent *){ //不断绘制背景
    QPainter p(this);
    p.drawPixmap(rect(),QPixmap("://image/13.png"));
}

void ScheduleWindow::settimeline()
{
    //设置时间
    QDateTime time=QDateTime::currentDateTime();
    QString str=time.toString("yyyy-MM-dd hh:mm:ss ddd");
    ui->timeline->setText(str);
    //右下角的问候语
    int hour=time.time().hour();
    QString iden="["+name+"]";
    if (hour>=13&& hour<=18) iden+=" 下午好！";
    else if (hour==12) iden+=" 中午好！";
    else if (hour>=0&&hour<=2) iden+=" 凌晨好！ 早点休息";
    else if (hour<12) iden+=" 上午好！";
    else iden+=" 晚上好！";
    ui->idenline->setText(iden);
    if (ifbegin){
        long long time_gap=QDateTime::currentDateTime().toSecsSinceEpoch()-time_start.toSecsSinceEpoch();
        int all=notes[middlename].length_time*60;
        QString st=QDateTime::fromMSecsSinceEpoch(all*1000-(QDateTime::currentDateTime().toMSecsSinceEpoch()-time_start.toMSecsSinceEpoch())).toUTC().toString("hh时mm分ss秒");
        st="<html><head/><body><p align=\"center\"><span style=\" font-size:28pt; color:#DB70DB;\">"+st+"</span></p></body></html>  ";
        ui->label_time_3->setText(st);

        if (all==time_gap) emit thisNotesDown();
        ui->progressBar->setValue((int)time_gap*100/all);
    }
}
void ScheduleWindow::mySortByColumn2(int column){
    static bool f=true;
    ui->tableWidget_s_1->sortByColumn(column,f? Qt::AscendingOrder:Qt::DescendingOrder);
    f=!f;
}

void ScheduleWindow::on_stu_logout_clicked()
{
    if (ifbegin){
        QMessageBox::warning(this,"警告","您现在正在处理代办噢，请注意保持专注！");
        return;
    }
    if(QMessageBox::question(this,"提示","是否注销用户?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        emit toLoginWindow();
        delete this;
    }
}
void ScheduleWindow::printAllNotes(){
    DataIntotxt();
    ui->tableWidget_s_1->setCurrentItem(NULL);
    ui->stackedWidget_3->setCurrentWidget(ui->page_s_1);
    ui->tableWidget_s_1->setRowCount(notes.size());
    ui->tableWidget_s_1->setColumnCount(4);
    QStringList header;
    header<<"代办项"<<"备注"<<"时间长度"<<"完成次数";
    ui->tableWidget_s_1->setHorizontalHeaderLabels(header);
    ui->tableWidget_s_1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_s_1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_s_1->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_s_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_s_1->setStyleSheet("selection-background-color:lightblue;"); //设置选中背景色
    ui->tableWidget_s_1->setStyleSheet("QTableWidget::item:selected { background-color: rgb(205, 127, 50) }");
    ui->tableWidget_s_1->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget_s_1->setAlternatingRowColors(true);
    ui->tableWidget_s_1->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_s_1->setColumnWidth(1,150);
    QHeaderView *headerView = ui->tableWidget_s_1->verticalHeader();
    headerView->setHidden(true);
    /*
    for (int i = 0; i < stud[nowstu].num_cho; i++) {
        printOneCourse_s(i,stud[nowstu].cho[i]);
        ui->tableWidget_s_1->setItem(i,5,new QTableWidgetItem(stud[nowstu].ass[i]));
        for (int j=0;j<6;j++){
            ui->tableWidget_s_1->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }*/
    for (int i=0;i<notes.size();i++){

        ui->tableWidget_s_1->setItem(i,0,new QTableWidgetItem(notes[i].name));
        ui->tableWidget_s_1->setItem(i,1,new QTableWidgetItem(notes[i].note));
        ui->tableWidget_s_1->setItem(i,2,new QTableWidgetItem(QString::number(notes[i].length_time)));
        ui->tableWidget_s_1->setItem(i,3,new QTableWidgetItem(QString::number(notes[i].time_complete)));
        ui->tableWidget_s_1->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_s_1->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_s_1->item(i, 2)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_s_1->item(i, 3)->setTextAlignment(Qt::AlignCenter);
    }
}

void ScheduleWindow::on_stu_inq_clicked()
{
    if (ifbegin){
        QMessageBox::warning(this,"警告","您现在正在处理代办噢，请注意保持专注！");
        return;
    }
    printAllNotes();
    this->clearAll();
}

void ScheduleWindow::clearAll(){
    ui->lineEdit_name->clear();
    ui->lineEdit_note->clear();
    ui->spinBox->clear();
}


void ScheduleWindow::on_stu_choosecourse_clicked()
{
    if (ifbegin){
        QMessageBox::warning(this,"警告","您现在正在处理代办噢，请注意保持专注！");
        return;
    }
    ui->stackedWidget_3->setCurrentWidget(ui->page_s_3);
}

void ScheduleWindow::on_SureModify_clicked()
{
    QString note_name=ui->lineEdit_name->text(),note_note=ui->lineEdit_note->text();
    int length_of_time=ui->spinBox->value();
    if (note_name==""){
        QMessageBox::warning(this,"警告","不能输入名字为空的代办事项");
        return;
    } else if (note_note==""){
        int ret=QMessageBox::question(this,"确定","确定要添加这个备注为空的代办？",QMessageBox::Yes,QMessageBox::Cancel);
        if (ret==QMessageBox::Yes){
            Notes t(note_name,length_of_time,note_note,0);
            notes.push_back(t);
            this->clearAll();
            printAllNotes();
        }
    } else {
        int ret=QMessageBox::question(this,"确定","确定要添加此代办？",QMessageBox::Yes,QMessageBox::Cancel);
        if (ret==QMessageBox::Yes){
            Notes t(note_name,length_of_time,note_note,0);
            notes.push_back(t);
            this->clearAll();
            printAllNotes();
        }
    }
}

void ScheduleWindow::on_delete_it_clicked()
{
    if (ifbegin){
        QMessageBox::warning(this,"警告","您现在正在处理代办噢，请注意保持专注！");
        return;
    }
    QList<QTableWidgetSelectionRange> ranges=ui->tableWidget_s_1->selectedRanges();
    int count=ranges.count();
    QString help;
    for(int i=0;i<count;i++){
        int topRow=ranges.at(i).topRow();
        int bottomRow=ranges.at(i).bottomRow();
        for(int j=topRow;j<=bottomRow;j++){
            QString note_name=ui->tableWidget_s_1->item(j,0)->text();
            deletenote(note_name);
            help=help+"["+ui->tableWidget_s_1->item(j,0)->text()+"] 代办"+"\n";
        }
    }
    if (help=="") help="你还未选中代办哦"; else help="删除的代办如下:\n"+help;
    QMessageBox::warning(this,"提示",help);
    printAllNotes();
    this->clearAll();
}
void ScheduleWindow::deletenote(QString name_of_note){
    QVector<Notes>::iterator it;
    for (it=notes.begin();it!=notes.end();it++){
        if (it->name==name_of_note) {
            notes.erase(it);break;
        }
    }
}



void ScheduleWindow::on_note_change_clicked()
{
    if (ifbegin){
        QMessageBox::warning(this,"警告","您现在正在处理代办噢，请注意保持专注！");
        return;
    }
    QList<QTableWidgetSelectionRange> ranges=ui->tableWidget_s_1->selectedRanges();
    int count=ranges.count();
    bool flag=false;
    for(int i=0;i<count;i++){
        int topRow=ranges.at(i).topRow();
        int bottomRow=ranges.at(i).bottomRow();
        for(int j=topRow;j<=bottomRow;j++){
            QString note_name=ui->tableWidget_s_1->item(j,0)->text();
            for (int k=0;k<notes.size();k++){
                if (note_name==notes[k].name) {
                    middlename=k;
                    flag=true;
                    ui->stackedWidget_3->setCurrentWidget(ui->page_s_4);
                    ui->lineEdit_name_2->setText(notes[k].name);
                    ui->lineEdit_note_2->setText(notes[k].note);
                    ui->spinBox_2->setValue(notes[k].length_time);
                }
            }
        }
    }
    if (!flag) QMessageBox::warning(this,"提示","你还未选中代办哦");
}


QPair<bool,int> ScheduleWindow::judgesame(QString name){
    for (int i=0;i<notes.size();i++){
        if (notes[i].name==name){
            return QPair<bool,int>(false,i);
        }
    }
    return QPair<bool,int>(true,0);
}
void ScheduleWindow::on_SureModify_2_clicked()
{
    QString note_name=ui->lineEdit_name_2->text(),note_note=ui->lineEdit_note_2->text();
    int length_of_time=ui->spinBox_2->value();
    if (note_name==""){
        QMessageBox::warning(this,"警告","不能添加名为空的代办噢");
        return;
    }
    QPair<bool,int> ans=judgesame(note_name);
    if (!(ans.first || (!ans.first&&ans.second==middlename))) {
        QMessageBox::warning(this,"警告","不能添加相同名字的代办噢");
        return;
    }
    notes[middlename].name=note_name;notes[middlename].length_time=length_of_time;
    notes[middlename].note=note_note;
    printAllNotes();
}

void ScheduleWindow::on_stu_person_clicked()
{
    if (ifbegin) {
        QMessageBox::warning(this,"警告","已经正在任务中了");
        ui->stackedWidget_3->setCurrentWidget(ui->page_s_5);
        return;
    }
    QList<QTableWidgetSelectionRange> ranges=ui->tableWidget_s_1->selectedRanges();
    int count=ranges.count();
    bool flag=false;
    for(int i=0;i<count;i++){
        int topRow=ranges.at(i).topRow();
        int bottomRow=ranges.at(i).bottomRow();
        for(int j=topRow;j<=bottomRow;j++){
            QString note_name=ui->tableWidget_s_1->item(j,0)->text();
            for (int k=0;k<notes.size();k++){
                if (note_name==notes[k].name) {
                    middlename=k;
                    flag=true;
                }
            }
        }
    }
    if (!flag) {
        QMessageBox::warning(this,"提示","你还未选中代办哦");
        ui->stackedWidget_3->setCurrentWidget(ui->page_s_1);
        return;
    }
    int ret=QMessageBox::question(this,"提醒","请问您是否愿意开启学霸模式(自动屏保，按任意键退出)？",QMessageBox::Yes,QMessageBox::Cancel);
    if (ret==QMessageBox::Yes){
        QDesktopServices::openUrl (QUrl::fromLocalFile("./help/bk.exe"));
    }
    ui->stackedWidget_3->setCurrentWidget(ui->page_s_5);
    time_start=QDateTime::currentDateTime();
    ifbegin=true;
    QString st=notes[middlename].name;
    st="代办事项："+st;
    st="<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; color:#0000FF;\">"+st+"</span></p></body></html>  ";
    ui->label_4->setText(st);


}


void ScheduleWindow::on_thisNotesDown(){
    mediaPlayer.setMedia(QUrl::fromLocalFile("./music/remind.mp3"));
    mediaPlayer.setVolume(50);
    mediaPlayer.play();
    pSystemTray->showMessage(notes[middlename].name, QString("该项任务时间已到了~~~"));
    notes[middlename].time_complete++;
    DataIntotxt();
    printAllNotes();
    ui->stackedWidget_3->setCurrentWidget(ui->page_s_1);
    ifbegin=false;
    for (int j=0;j<4;j++){
        ui->tableWidget_s_1->item(middlename, j)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_s_1->item(middlename, j)->setForeground(QBrush(QColor(5, 39, 175)));
        //将字体加粗
        ui->tableWidget_s_1->item(middlename, j)->setFont( QFont( "Times", 10, QFont::Black ) );
    }
    int ret=QMessageBox::question(this,"帮助","何尝不来开心一刻？",QMessageBox::Yes,QMessageBox::Cancel);
    if (ret==QMessageBox::Yes){
        on_pushButton_clicked();
    }
}

void ScheduleWindow::on_pushButton_over_clicked()
{
    int ret=QMessageBox::question(this,"确定","你真的要提前结束这个代办？",QMessageBox::Yes,QMessageBox::Cancel);
    if (ret==QMessageBox::Yes){
        ifbegin=false;
        ui->stackedWidget_3->setCurrentWidget(ui->page_s_1);
    }
}

void ScheduleWindow::on_pushButton_music_clicked()
{
    musicplayer=new MusicPlayer();
    musicplayer->setWindowIcon(QIcon("://image/logo_music.png"));
    musicplayer->setWindowTitle(("小小音乐盒"));
    musicplayer->show();
    int ret=QMessageBox::question(this,"帮助","您想要直接导入默认歌单吗？",QMessageBox::Yes,QMessageBox::Cancel);
    if (ret==QMessageBox::Yes){
        musicplayer->DirectInputDefault();
    }

}

void ScheduleWindow::on_pushButton_clicked()
{
    QDesktopServices::openUrl (QUrl::fromLocalFile("./help/bricks/Bricks.exe"));
}
