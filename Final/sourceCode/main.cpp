#include "mainwindow.h"
#include "findpath.h"
#include <QApplication>
#include <form.h>
#include <QTime>

void sleep(int msec)
{
    QTime _Timer = QTime::currentTime();
        QTime _NowTimer;
        do{
                  _NowTimer=QTime::currentTime();
        }while (_Timer.msecsTo(_NowTimer)<=msec);
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    Form d;
    d.show();

    sleep(2000);
    d.close();

    w.setWindowTitle("WELCOME!");
    w.show();

    return a.exec();
}
