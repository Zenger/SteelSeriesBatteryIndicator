#ifndef USBDEVICES_H
#define USBDEVICES_H

#include "hidapi/hidapi.h"
#include <QList>

struct UsbDevice {
    QString name;
    QString serial;
    int product_id;
    int vendor_id;
    int usage_page;
    int usage;
    char* path;

    UsbDevice (int product_id, int vendor_id, QString name, QString serial, char* path, int usage_page, int usage) {
        this->product_id = product_id;
        this->vendor_id = vendor_id;
        this->name = name;
        this->serial = serial;
        this->path = path;
        this->usage = usage;
        this->usage_page = usage_page;
    };

    UsbDevice() {}
};

class UsbDevices
{
public:
    UsbDevices();

    int res;
    hid_device *handle;
    void get_supported_devices();
    int init();
    QList<UsbDevice> supported_devices;
    int fetch_percentage(UsbDevice dev);
    int current_percentage;
    UsbDevice fetch_first_available();
    UsbDevice active_device;

public slots:
    void repoll();

private:
    //QList<libusb_device> devices;

};

#endif // USBDEVICES_H
