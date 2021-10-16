#include "usbdevices.h"
#include <QDebug>
#include <QString>
#include <QTimer>

#define MAX_STR 255

/*  Supported series so far
    [4152, 0x12ad], // Arctis 7 2019
    [4152, 0x1260], // Arctis 7 2017
    [4152, 0x1252], // Arctis Pro
    [4152, 0x12b3], // Actris 1 Wireless
    [4152, 0x12C2] // Arctis 9
] */

UsbDevices::UsbDevices()
{
    this->get_supported_devices();

}

void UsbDevices::get_supported_devices() {
    hid_init();
    hid_device_info *devs = hid_enumerate(0, 0);
    for( hid_device_info *dev = devs; dev; dev = dev->next ) {
        if (dev->vendor_id == 4152 && ( dev->product_id == 0x12ad || dev->product_id == 0x1260 || dev->product_id == 0x1252 || dev->product_id == 0x12b3 || dev->product_id == 0x12C2)) {
            UsbDevice usb_device(
                            (int) dev->product_id,
                            (int) dev->vendor_id,
                            QString::fromWCharArray( dev->product_string),
                            QString::fromWCharArray( dev->serial_number ),
                            dev->path,
                            (int) dev->usage,
                            (int) dev->usage_page
                                  );
            supported_devices.append( usb_device );

        }
    }
    hid_free_enumeration( devs );

}



int UsbDevices::init() {
    qDebug() << "Potentially supports: " << this->supported_devices.length();

    for (int i = 0; i < this->supported_devices.length(); i ++ ) {
        UsbDevice dev = this->supported_devices.at(i);
        if (dev.usage_page > 1) {
            this->active_device = dev;
            return 0;
        }
    }
}

int UsbDevices::fetch_percentage(UsbDevice dev) {

           int res;
           unsigned char buf[65];
           wchar_t wstr[MAX_STR];
           hid_device *handle;
           int i;

           // Initialize the hidapi library
           res = hid_init();

           // Open the device using the VID, PID,
           // and optionally the Serial number.
           handle = hid_open_path( dev.path );

           // Toggle LED (cmd 0x80). The first byte is the report number (0x0).
           buf[0] = 0x06;
           buf[1] = 0x18;

           std::vector<unsigned char> message;
           message.reserve(2);
           message.push_back((unsigned char) 0x06);
           message.push_back((unsigned char) 0x18);

           res = hid_write(handle, message.data(), message.size());
           if ( res < 0) {
               qDebug() << "Didnt write any bytes...";
           }

           unsigned char buf2[8];

           res = hid_read_timeout( handle, buf2, sizeof buf, 1000);

           // Close the device
           hid_close(handle);

           // Finalize the hidapi library
           res = hid_exit();

           this->current_percentage = buf2[2];

           return buf2[2];
}

UsbDevice UsbDevices::fetch_first_available() {
    for (int i = 0; i < this->supported_devices.length(); i ++ ) {
        UsbDevice dev = this->supported_devices.at(i);
        if (dev.usage_page > 1) {
            return dev;
        }
    }
}


void UsbDevices::repoll() {
    qDebug() << this->active_device.path;
}

