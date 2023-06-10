#include "mainwindow.h"
#include"loging.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loging log;
    log.exec();
    MainWindow w;
    w.show();
    return a.exec();
}
