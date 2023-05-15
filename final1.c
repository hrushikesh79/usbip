#include <stdio.h>
#include <stdlib.h>
#include<libudev.h>
#include <libusb.h>

void *fun_to_detect(void *vargp){
    struct udev *udev = udev_new();
if (!udev) {
printf("Failed to create udev context\n");
return EXIT_FAILURE;
}

struct udev_monitor *monitor = udev_monitor_new_from_netlink(udev, "udev");
if (!monitor) {
printf("Failed to create udev monitor\n");
udev_unref(udev);
return EXIT_FAILURE;
}

udev_monitor_filter_add_match_subsystem_devtype(monitor, "usb", "usb_device");
udev_monitor_enable_receiving(monitor);

printf("Listening for USB device events...\n");

while (1) {
struct udev_device *dev = udev_monitor_receive_device(monitor);
if (!dev) continue;

const char *action = udev_device_get_action(dev);
const char *devnode = udev_device_get_devnode(dev);
const char *vendor_id = udev_device_get_sysattr_value(dev, "idVendor");
const char *product_id = udev_device_get_sysattr_value(dev, "idProduct");

if (action && devnode && vendor_id && product_id) {
printf("%s: VendorID=%s ProductID=%s DevNode=%s\n", action, vendor_id, product_id, devnode);
}

udev_device_unref(dev);
}

udev_monitor_unref(monitor);
udev_unref(udev);
                     return EXIT_SUCCESS;

}

void *fun_to_list(void *vargp){


    libusb_device **devices;
libusb_context *ctx = NULL;
int rc, count, i;

/* Initialize the libusb library */
rc = libusb_init(&ctx);
if (rc < 0) {
fprintf(stderr, "Failed to initialize libusb\n");
return 1;
}

/* Get a list of USB devices attached to the system */
count = libusb_get_device_list(ctx, &devices);
if (count < 0) {
fprintf(stderr, "Failed to get device list\n");
libusb_exit(ctx);
return 1;
}

/* Print information about each device */
for (i = 0; i < count; i++) {
libusb_device *device = devices[i];
struct libusb_device_descriptor desc;
char serial[256];

/* Get the device descriptor */
rc = libusb_get_device_descriptor(device, &desc);
if (rc < 0) {
fprintf(stderr, "Failed to get device descriptor\n");
continue;
}

/* Get the device serial number */
rc = libusb_get_string_descriptor_ascii(device, desc.iSerialNumber, serial, sizeof(serial));
if (rc < 0) {
serial[0] = '\0';
}

/* Print the device information */
printf("Bus %03d Device %03d: ID %04x:%04x %s\n",
libusb_get_bus_number(device), libusb_get_device_address(device),
desc.idVendor, desc.idProduct, serial);
}

/* Clean up and exit */
libusb_free_device_list(devices, 1);
libusb_exit(ctx);
}

int main(){
   pthread_t thread1, thread2;
    int i1, i2;
    i1 = pthread_create(&thread1, NULL, fun_to_detect, (void*) "thread 1");
    i2 = pthread_create(&thread2, NULL, fun_to_list, (void*) "thread 2");

    pthread_join(thread2, NULL);
    pthread_join(thread1, NULL);
  
    return 0;

}
