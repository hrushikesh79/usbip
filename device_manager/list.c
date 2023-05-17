/* SPDX-License-Identifier: GPL-2.0-only
 *
 *
 * usbip project file
 *
 * Copyright (C) 2023 Samsung Electronics Co., Ltd.
 *
 * Author: Hrushikesh Reddy Mudhireddy  (h.mudhireddy)
 */

#include "list.h"


#include <libudev.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int init()
{
struct udev *udev;
        struct udev_enumerate *enumerate;
        struct udev_list_entry *devices, *dev_list_entry;
        struct udev_device *dev;
        const char *path;
        const char *idVendor;
        const char *idProduct;
        const char *bConfValue;
        const char *bNumIntfs;
        const char *busid;
        char product_name[128];
        int ret = -1;
        const char *devpath;

        /* Create libudev context. */
        udev = udev_new();

        /* Create libudev device enumeration. */
        enumerate = udev_enumerate_new(udev);

        /* Take only USB devices that are not hubs and do not have
         * the bInterfaceNumber attribute, i.e. are not interfaces.
         */
        udev_enumerate_add_match_subsystem(enumerate, "usb");
 udev_enumerate_add_match_subsystem(enumerate, "usb_device");
        

        udev_enumerate_add_nomatch_sysattr(enumerate, "bDeviceClass", "09");
        udev_enumerate_add_nomatch_sysattr(enumerate, "bInterfaceNumber", NULL);
        udev_enumerate_scan_devices(enumerate);
    devices = udev_enumerate_get_list_entry(enumerate);

        /* Show information about each device. */
        udev_list_entry_foreach(dev_list_entry, devices) {
                path = udev_list_entry_get_name(dev_list_entry);
                dev = udev_device_new_from_syspath(udev, path);

                /* Get device information. */
                idVendor = udev_device_get_sysattr_value(dev, "idVendor");
                idProduct = udev_device_get_sysattr_value(dev, "idProduct");
                bConfValue = udev_device_get_sysattr_value(dev,
                                "bConfigurationValue");
                bNumIntfs = udev_device_get_sysattr_value(dev,
                                "bNumInterfaces");
                busid = udev_device_get_sysname(dev);

                /* Print information. */
                  printf(" - busid %s\n", busid);

printf("vendor id is %s and productid is %s\n",idVendor,idProduct);

                udev_device_unref(dev);
        }

        ret = 0;

err_out:
        udev_enumerate_unref(enumerate);
        udev_unref(udev);

        return ret;
}
