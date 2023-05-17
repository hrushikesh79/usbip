/* SPDX-License-Identifier: GPL-2.0-only
 *
 * source file to detect the usb at run time
 *
 * Copyright (C) 2023 Samsung Electronics Co., Ltd.
 *
 * Author: Hrushikesh Reddy Mudhireddy  (h.mudhireddy)
 */

#include "monitor.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int monitor()
{
const char *action;
const char *devnode;
const char *vendor_id;
const char *product_id;
	const char *busid ;
    struct udev *udev = udev_new();
    if (!udev)
    {
        printf("Failed to create udev context\n");
        return EXIT_FAILURE;
    }

    struct udev_monitor *monitor = udev_monitor_new_from_netlink(udev, "udev");
    if (!monitor)
    {
        printf("Failed to create udev monitor\n");
        udev_unref(udev);
        return EXIT_FAILURE;
    }

    udev_monitor_filter_add_match_subsystem_devtype(monitor, "usb", "usb_device");
    udev_monitor_enable_receiving(monitor);

    printf("Listening for USB device events...\n");

    while (1)
    {
        struct udev_device *dev = udev_monitor_receive_device(monitor);
        if (!dev)
            continue;

        action = udev_device_get_action(dev);
        devnode = udev_device_get_devnode(dev);
        vendor_id = udev_device_get_sysattr_value(dev, "idVendor");
        product_id = udev_device_get_sysattr_value(dev, "idProduct");

	busid = udev_device_get_sysname(dev);



	if (action && devnode && vendor_id && product_id)
        {
            printf("%s: VendorID=%s ProductID=%s DevNode=%s\n", action, vendor_id, product_id, devnode);
        }

       


        
        udev_device_unref(dev);
    }

    udev_monitor_unref(monitor);
    udev_unref(udev);

    return EXIT_SUCCESS;
}
