#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QElapsedTimer>
#include <QTimer>

#include "usbdevices.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    UsbDevices devices;
    this->usbdevices = devices;
    this->usbdevices.init();
    this->active_device = this->usbdevices.fetch_first_available();
    int percentage = this->usbdevices.fetch_percentage( this->active_device );
    this->tray_icon_init(percentage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(rect(), Qt::AlignCenter, "SSB");
}

void MainWindow::tray_icon_init( int p ) {

    this->systemTrayIcon = new QSystemTrayIcon(this);

    int percentage  = p;
    qDebug() << percentage;

    this->systemTrayIcon->setIcon( this->get_icon(percentage));

    QMenu *menu = new QMenu(this);
    QAction *refreshAction = new QAction("Refresh", this);
    QAction *quitAction = new QAction("Exit", this);

    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(refreshAction, SIGNAL(triggered()), this, SLOT(refresh()));

    menu->addAction( refreshAction );
    menu->addSeparator();
    menu->addAction(quitAction);

    this->systemTrayIcon->setContextMenu(menu);
    this->systemTrayIcon->setVisible(true);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(refresh()) );
    timer->start(300000);
}

void MainWindow::refresh() {

    UsbDevices usbd;
    usbd.init();
    UsbDevice dd = usbd.fetch_first_available();


    int percentage = usbd.fetch_percentage( dd );
    this->systemTrayIcon->setIcon( this->get_icon(percentage) );

}

QIcon MainWindow::get_icon(int percentage) {

    QString qs_percentage;
    qs_percentage.setNum(percentage);


    QPixmap oPixmap = QPixmap(22,22);
    QPainter paint;
    paint.begin(&oPixmap);
    paint.setBackgroundMode(Qt::OpaqueMode);
    paint.setBackground(QBrush(QColor(255,255,255)));
    paint.setPen(QPen(Qt::black));
    paint.setFont(QFont("Arial", 14, QFont::Condensed));
    paint.drawText( oPixmap.rect(), Qt::AlignCenter, qs_percentage);
    paint.end();

    QIcon nIcon = QIcon( oPixmap );
    return nIcon;
}
