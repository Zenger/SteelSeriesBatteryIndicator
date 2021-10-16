#include "mainwindow.h"

#include <QApplication>
#include <QSystemTrayIcon>
#include <QDebug>
#include <QPainter>
#include <QList>


#include "usbdevices.h"
#include "hidapi/hidapi.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Steel Series Battery Indicator");

    //w.show();
    return a.exec();
}


