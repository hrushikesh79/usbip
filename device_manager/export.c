/* SPDX-License-Identifier: GPL-2.0-only
 *
 * source file contains bind and unbind function to bind and unbind
 * the usb device 
 *
 * Copyright (C) 2023 Samsung Electronics Co., Ltd.
 *
 * Author: Hrushikesh Reddy Mudhireddy  (h.mudhireddy)
 */

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include "export.h"
#define SYSFS_USBIP_BIND_PATH "/sys/bus/usb/drivers/usbip/bind"
#define MAX_BUS_ID_LENGTH 10


int bind(const char *busId)
{
    // Construct the bind command
    char bindCommand[MAX_BUS_ID_LENGTH + sizeof(SYSFS_USBIP_BIND_PATH) + 2];
    snprintf(bindCommand, sizeof(bindCommand), "%s:%s", SYSFS_USBIP_BIND_PATH, busId);

    // Execute the bind command
    int result = system(bindCommand);
    if (result == 0)
    {
        printf("Successfully bind USB device with bus ID: %s\n", busId);
    }
    else
    {
        printf("Failed to bind USB device with bus ID: %s\n", busId);
    }

    return 0;
}
void  unbind(const char *busID)
{
 // Create the sysfs path for the USB device
    char sysfsPath[256];
    snprintf(sysfsPath, sizeof(sysfsPath), "/sys/bus/usb/devices/%s/driver/unbind", busID);

    // Open the unbind file
    FILE* unbindFile = fopen(sysfsPath, "w");
    if (!unbindFile) {
        perror("Failed to open unbind file");
        return;
    }

    // Write the bus ID to the unbind file
    size_t bytesWritten = fwrite(busID, strlen(busID), 1, unbindFile);
    if (bytesWritten != 1) {
        perror("Failed to write bus ID to unbind file");
        fclose(unbindFile);
        return;
    }

    // Close the unbind file
    fclose(unbindFile);

    printf("USB device with Bus ID %s unbound successfully.\n", busID);

}



