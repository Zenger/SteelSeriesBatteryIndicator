#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>
#include <QSystemTrayIcon>
#include "usbdevices.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void tray_icon_init(int);
    QSystemTrayIcon *systemTrayIcon;
    QIcon get_icon(int);
    UsbDevices usbdevices;
    UsbDevice active_device;


private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *mainIcon;




public slots:
    void refresh();
signals:
    void timedout(UsbDevice dev);

};
#endif // MAINWINDOW_H
