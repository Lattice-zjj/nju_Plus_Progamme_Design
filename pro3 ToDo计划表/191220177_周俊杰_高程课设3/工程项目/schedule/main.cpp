#include "loginwindow.h"
#include "schedulewindow.h"
#include "musicplayer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //最后一个可视窗口关闭时，不退出程序
    //a.setQuitOnLastWindowClosed(false);
    LoginWindow w;
    w.show();
    return a.exec();
}
