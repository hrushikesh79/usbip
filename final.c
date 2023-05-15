#include <stdio.h>
#include <stdlib.h>
#include<libudev.h>
#include <libusb.h>


void *fun(void *vargp){
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


int main() {
pid_t pid;
    pthread_t thread;

    // Create a child process
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
  if (pid == 0) {
        sleep(2);
        exit(0);
    } else {
        // Parent process
       
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

	// Create a thread to wait for the child process
        pthread_create(&thread, NULL, fun, (void*)&pid);

        // Continue executing in the parent process



        // Wait for the thread to finish
        pthread_join(thread, NULL);

        printf("Parent process exiting\n");



}

} 
