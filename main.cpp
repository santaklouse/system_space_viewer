#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//#ifdef Q_OS_LINUX
//    root_path = "/";
//#elif defined(Q_OS_WIN)
//    root_path = "";
//#endif

    return a.exec();
}
