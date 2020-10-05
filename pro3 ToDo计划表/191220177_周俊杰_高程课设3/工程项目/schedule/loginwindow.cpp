#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    //帮助文档
    connect(ui->actiona,&QAction::triggered,
            [=](){ QDesktopServices::openUrl (QUrl::fromLocalFile("./HelpFile/HelpFile.pdf"));
    });

    //ui界面的各种控件的样式初始化
    this->setMaximumSize(640,480);
    this->setMinimumSize(640,480);
    this->setWindowIcon(QIcon("://image/1.png"));
    setWindowTitle("Superego Todo");
    ui->userlabel->setStyleSheet("font-size:12px;color:black");
    ui->passwordlabel->setStyleSheet("font-size:12px;color:black");
    ui->yanzheng->setStyleSheet("font-size:12px;color:black");
    ui->timeline->setStyleSheet("font-size:16px;color:blue");
    ui->idenline->setStyleSheet("font-size:16px;color:yellow");
    ui->timeline->setStyleSheet("font-size:16px;color:blue");
    QFont font ("Microsoft YaHei",1,75);
    ui->userlabel->setFont(font);
    ui->passwordlabel->setFont(font);
    ui->yanzheng->setFont(font);
    ui->timeline->setFont(font);
    ui->idenline->setFont(font);
    ui->timeline->setFont(font);
    //设置调色板,用于设置titlelabel的颜色
    QPalette pal;
    pal.setColor(QPalette::WindowText,Qt::blue);
    ui->titlelabel->setStyleSheet("font-size:40px;color:blue");
    ui->titlelabel->setPalette(pal);
    ui->titlelabel->setFont(font);
    //logo加载
    ui->logo_nju->setPixmap(QPixmap("://image/logo_nju.png").scaled(ui->logo_nju->size()));
    ui->loginbtn->setEnabled(false);//设置登录按钮不可用
    ui->userline->setPlaceholderText("请输入用户名");
    ui->passwordline->setPlaceholderText("请输入密码");
    ui->yanEdit->setPlaceholderText("请输入验证码");//设置lineedit提示语句
    ui->passwordline->setEchoMode(QLineEdit::Password);  //设置passlineedit显示为密码模式
    //设置按钮的样式
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
    ui->loginbtn->setStyleSheet(btnStyle);
    ui->registerbtn->setStyleSheet(btnStyle);
    ui->exitbtn->setStyleSheet(btnStyle);



    //设置定时器
    timelinetimer=new QTimer(this);
    timelinetimer->setInterval(100);
    timelinetimer->start();
    connect(timelinetimer,SIGNAL(timeout()),this,SLOT(settimeline()));

    //设置登录按钮可用
    connect(ui->userline,SIGNAL(textChanged(QString)),this,SLOT(loginbtnSetSlot(QString)));
    connect(ui->passwordline,SIGNAL(textChanged(QString)),this,SLOT(loginbtnSetSlot(QString)));

    //设置验证码
    QTime t;
    t=QTime::currentTime();
    qsrand(uint(t.msec()+t.second()*1000));
    this->on_yanzhenglabel_clicked();
    UpInfor();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_yanzhenglabel_clicked()
{
    num_yan=qrand()%10000;
    while(num_yan<1000) num_yan=qrand()%10000;
    int a=qrand()%256,b=qrand()%256,c=qrand()%256;
    QString st=QString::number(a)+","+QString::number(b)+","+QString::number(c);
    ui->yanzhenglabel->setText(QString::number(num_yan));
    ui->yanzhenglabel->setStyleSheet("background-color: rgb("+st+");");
}
void LoginWindow::loginbtnSetSlot(QString)
{
    ui->loginbtn->setEnabled(true);
}

void LoginWindow::on_loginbtn_clicked()
{
    if(!this->judgeEmpty()) {
        ui->passwordline->clear();
        return;
    }
    QString getyan=ui->yanEdit->text();
    if (getyan!=QString::number(num_yan)) {
        QMessageBox::information(this,"提示","验证码输入错误",QMessageBox::Yes);
        ui->passwordline->clear();
        this->on_yanzhenglabel_clicked();
        return;
    }
    //用于记录历史写入的账号
    QString now_user_name=ui->userline->text();
    QVector<QString>::iterator iter;
    for(iter=history.begin();iter!=history.end();iter++){
        if((*iter)==now_user_name){ history.erase(iter);break;}
    }
    history.push_back(ui->userline->text());
    //开始判断选的是哪个身份
    QString cid=ui->userline->text(),cpa=ui->passwordline->text();
    bool f=false;
    for (int i = 0; i < data.size(); i++) {
        if (cid==data[i]->getid()){
            f=true;
            if (data[i]->if_lock()){
                QMessageBox::information(this,"提示","您的账号封锁中....",QMessageBox::Yes);
                this->clearAll();
                return;
            }
        }
        if (data[i]->Login(cid, cpa)) {
            QString st;
            this->clearAll();
            QMessageBox::information(this,"提示","用户 ["+cid+"] 您已经成功登陆！！",QMessageBox::Yes);
            user=new ScheduleWindow;
            user->show();
            connect(this,SIGNAL(toScheduleWindow(QString)),user,SLOT(fromLoginWindow(QString)));
            connect(user,SIGNAL(toLoginWindow()),this,SLOT(showNormal()));
            emit toScheduleWindow(cid);
            /*student=new StudentWindow;
            student->show();
            connect(this,SIGNAL(toStudentWindow(Admin*,int*,Student*,int)),student,SLOT(fromLoginWindow(Admin*,int*,Student*,int)));
            connect(student,SIGNAL(toLoginWindow()),this,SLOT(showNormal()));
            emit toStudentWindow(&admin,&st_num,stud,nowstu);*/
            this->hide();

            return;
        }
        else {
            if (cid==data[i]->getid()){
                if (data[i]->getnum_of_login()>5){
                    QMessageBox::information(this,"提示","您的账号登陆尝试次数超过5次！账号封锁5分钟",QMessageBox::Yes);
                    data[i]->Lock();
                    timer=new QTimer(this);
                    timer->start( 1000*300 );
                    connect( timer, SIGNAL( timeout() ), this, SLOT( unlock_s() ) );
                    this->clearAll();
                    return;
                }
            }
        }
    }
    this->clearAll();
    if (f) QMessageBox::information(this,"提示","密码输入有误！！",QMessageBox::Yes);
    else QMessageBox::information(this,"提示","该用户名不存在！！",QMessageBox::Yes);
}


bool LoginWindow::judgeEmpty()
{
    if(ui->userline->text().isEmpty()){
        QMessageBox::warning(this,"警告","用户名不能为空");
        return false;
    }
    if(ui->passwordline->text().isEmpty()){
        QMessageBox::warning(this,"警告","密码不能为空");
        return false;
    }
    else return true;
}

void LoginWindow::clearAll()
{
    this->on_yanzhenglabel_clicked();
    ui->userline->clear();
    ui->passwordline->clear();
    ui->yanEdit->clear();
}

void LoginWindow::settimeline()
{
    //设置时间
    QDateTime time=QDateTime::currentDateTime();
    QString str=time.toString("yyyy-MM-dd hh:mm:ss ddd");
    ui->timeline->setText(str);
    //右下角的问候语
    int hour=time.time().hour();
    QString iden="[访客]";
    if (hour>=13&& hour<=18) iden+=" 下午好！";
    else if (hour==12) iden+=" 中午好！";
    else if (hour>=0&&hour<=2) iden+=" 凌晨好！ 早点休息";
    else if (hour<12) iden+=" 上午好！";
    else iden+=" 晚上好！";
    ui->idenline->setText(iden);
}


void LoginWindow::on_userline_textEdited(const QString &arg1)
{
    QStringList wordList;
    for (int i=0;i<history.size();i++)
        if (history[i].contains(arg1)) wordList<<history[i];
    QCompleter *completer = new QCompleter(wordList,this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    ui->userline->setCompleter(completer);
}
void LoginWindow::paintEvent(QPaintEvent *){ //不断绘制背景
    QPainter p(this);
    p.drawPixmap(rect(),QPixmap("://image/13.png"));
}

void LoginWindow::UpInfor(){ //用于从文件中读取所有的数据（主要是用于将上一次保留的信息拷贝到内存中
    QFile file2;
    file2.setFileName("./data/user.dat");
    bool isOK2=file2.open(QIODevice::ReadOnly);
    if (isOK2){
        QTextStream stream(&file2);
        stream.setCodec("UTF-8");
        while (stream.atEnd()==false){
            QString st1;
            stream>>st1;
            if (st1!=""){
                QList<QString> stt;
                stt=st1.split(',');
                User *user=new User(stt.at(0),stt.at(1));
                data.push_back(user);
            }
        }
        file2.close();
    }else {
        cout<<"打开失败！";
    }
}


void LoginWindow::on_registerbtn_clicked()
{
    reg=new RegisterDialog;
    reg->show();
    connect(this,SIGNAL(toRegisterWindow()),reg,SLOT(fromLoginWindow()));
    connect(reg,SIGNAL(toLoginWindow()),this,SLOT(showNormal()));
    emit toRegisterWindow();
    this->hide();
}
