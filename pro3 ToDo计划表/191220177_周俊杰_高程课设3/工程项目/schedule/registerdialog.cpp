#include "registerdialog.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    //设置大小固定为640*480
    this->setMaximumSize(640,480);
    this->setMinimumSize(640,480);
    this->setWindowIcon(QIcon("://image/1.png"));
    setWindowTitle("Superego Todo ");
    ui->label_16->setStyleSheet("font-size:12px;color:black");
    ui->label_17->setStyleSheet("font-size:12px;color:black");
    ui->label_18->setStyleSheet("font-size:12px;color:black");
    QFont font ("Microsoft YaHei",1,75);
    ui->label_16->setFont(font);
    ui->label_17->setFont(font);
    ui->label_18->setFont(font);
    ui->idenline_4->setStyleSheet("font-size:16px;color:yellow");
    ui->timeline_4->setStyleSheet("font-size:16px;color:blue");
    ui->timeline_4->setFont(font);
    ui->idenline_4->setFont(font);

    //设置调色板,用于设置titlelabel的颜色
    QPalette p;
    p.setColor(QPalette::WindowText,Qt::blue);
    ui->title_4->setStyleSheet("font-size:40px;color:blue");
    ui->title_4->setFont(font);
    ui->title_4->setPalette(p);
    ui->lineEdit_s_z_id_4->setPlaceholderText("请输入用户名");
    ui->lineEdit_s_z_pa_4->setPlaceholderText("请输入密码");
    ui->lineEdit_s_z_apa_4->setPlaceholderText("请再一次输入密码");
    ui->lineEdit_s_z_pa_4->setEchoMode(QLineEdit::Password);
    ui->lineEdit_s_z_apa_4->setEchoMode(QLineEdit::Password);
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
    ui->back_to_4->setStyleSheet(btnStyle);
    ui->register_s_4->setStyleSheet(btnStyle);
    //设置定时器
    timelinetimer=new QTimer(this);
    timelinetimer->setInterval(100);
    timelinetimer->start();
    connect(timelinetimer,SIGNAL(timeout()),this,SLOT(settimeline()));
    ui->register_s_4->setEnabled(false);//设置注册按钮不可用
    connect(ui->lineEdit_s_z_id_4,SIGNAL(textChanged(QString)),this,SLOT(loginbtnSetSlot(QString)));
    connect(ui->lineEdit_s_z_pa_4,SIGNAL(textChanged(QString)),this,SLOT(loginbtnSetSlot(QString)));
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::clearAll()
{
    ui->lineEdit_s_z_id_4->clear();
    ui->lineEdit_s_z_pa_4->clear();
    ui->lineEdit_s_z_apa_4->clear();
}
void RegisterDialog::loginbtnSetSlot(QString)
{
    ui->register_s_4->setEnabled(true);
}
void RegisterDialog::settimeline()
{
    //设置时间
    QDateTime time=QDateTime::currentDateTime();
    QString str=time.toString("yyyy-MM-dd hh:mm:ss ddd");
    ui->timeline_4->setText(str);
    //右下角的问候语
    int hour=time.time().hour();
    QString iden="[访客]";
    if (hour>=13&& hour<=18) iden+=" 下午好！";
    else if (hour==12) iden+=" 中午好！";
    else if (hour>=0&&hour<=2) iden+=" 凌晨好！ 早点休息";
    else if (hour<12) iden+=" 上午好！";
    else iden+=" 晚上好！";
    ui->idenline_4->setText(iden);
}

void RegisterDialog::fromLoginWindow()
{

}


void RegisterDialog::on_register_s_4_clicked()
{
    QString str1=ui->lineEdit_s_z_id_4->text(),str2=ui->lineEdit_s_z_pa_4->text(),str3=ui->lineEdit_s_z_apa_4->text();
    if(str1.isEmpty())
    {
        QMessageBox::warning(this,"警告","用户名不能为空");
        return;
    }
    if(str2.isEmpty())
    {
        QMessageBox::warning(this,"警告","密码不能为空");
        return;
    }
    if (str2!=str2){
        QMessageBox::warning(this,"警告","两次密码输入不一致");
        ui->lineEdit_s_z_pa_4->clear();
        ui->lineEdit_s_z_apa_4->clear();
    }else{
        int f=0;
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
                    if (stt.at(0)==str1) {f=1;break;}
                    data.push_back(QPair<QString,QString>(stt.at(0),stt.at(1)));
                }
            }
            file2.close();
        }else {
            cout<<"打开失败！";
        }
        if (f==1) {
            QMessageBox::warning(this,"警告","用户名已经被使用！");
            this->clearAll();
            return;
        }

        /*
        student=new StudentWindow;

        connect(this,SIGNAL(toStudentWindow(Admin*,int*,Student*,int)),student,SLOT(fromLoginDialog(Admin*,int*,Student*,int)));
        connect(student,&StudentWindow::toLoginDialog,
                [=](){emit toLoginDialog();});
        emit toStudentWindow(admin,st_num,stud,(*st_num) - 1);
        student->show();*/
        QString cid=str1,cpa=str2;
        user=new ScheduleWindow;
        user->show();
        connect(this,SIGNAL(toScheduleWindow(QString)),user,SLOT(fromLoginWindow(QString)));
        connect(user,SIGNAL(toLoginWindow()),this,SLOT(showNormal()));
        emit toScheduleWindow(cid);
        QByteArray byte_array=str2.toUtf8();
        QByteArray hash_byte_array=QCryptographicHash::hash(byte_array,QCryptographicHash::Md5);
        QString Md5code=hash_byte_array.toHex();
        data.push_back(QPair<QString,QString>(str1,Md5code));
        QFile file1;
        file2.setFileName("./data/user.dat");
        bool isOK1=file2.open(QIODevice::WriteOnly);
        if (isOK1 == false) {
            cout<<"打开失败！";
        }
        else {
            QTextStream stream2(&file2);
            stream2.setCodec("UTF-8");
            for (int i = 0; i < data.size(); i++) {
                QString str;
                str=data[i].first+","+data[i].second;
                stream2<<str<<"\r\n";
            }
            file2.close();
        }

        this->hide();
        this->clearAll();
        QString username;
        username="用户["+cid+"] 您已经成功注册！";
        QMessageBox::information(this,"提示",username,QMessageBox::Yes);
    }
}



void RegisterDialog::on_back_to_4_clicked()
{
    if(QMessageBox::question(this,"提示","是否返回主界面?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        emit toLoginWindow();
        delete this;
    }
}
void RegisterDialog::paintEvent(QPaintEvent *){ //不断绘制背景
    QPainter p(this);
    p.drawPixmap(rect(),QPixmap("://image/13.png"));
}
