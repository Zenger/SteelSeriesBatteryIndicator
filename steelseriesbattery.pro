QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    usbdevices.cpp

HEADERS += \
    mainwindow.h \
    usbdevices.h

FORMS += \
    mainwindow.ui
#WORKS
#INCLUDEPATH += "$$PWD/libusb-1.0/include"
#LIBS += -L$$PWD/libusb-1.0/lib -llibusb-1.0 #has to match the dll file

LIBS += -L$$PWD/hidapi -lhidapi

RC_ICONS = battery.ico



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
