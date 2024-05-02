#include <linux/types.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/init.h>

#define NAME "character_device"

static int character_device_open(struct inode *inode, struct file *file);
static int character_device_close(struct inode *inode, struct file *file);

struct cdev device_cdev;
static struct class *device_class = NULL;
static dev_t device_number;

static struct file_operations device_fops =
{
    .owner = THIS_MODULE,
    .open = character_device_open,
    .release = character_device_close
};

static int character_device_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "%s: device opened", NAME);
    return 0;
}

static int character_device_close(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "%s: device closed", NAME);
    return 0;
}

static int __init character_device_init(void)
{
    // Allocates char device numbers (major'n' minor)
    if (alloc_chrdev_region(&device_number, 0, 1, NAME) < 0)
    {
        printk("%s: could not be allocated", NAME);
        return -1;
    }

    printk(KERN_INFO "Character Device was registered: <Major, Minor>: <%d, %d>\n", MAJOR(device_number), MINOR(device_number));
    
    // Initialize the cdev struct
    cdev_init(&device_cdev, &device_fops);

    // Register a device with VFS
    device_cdev.owner = THIS_MODULE;
    if (cdev_add(&device_cdev, device_number, 1) < 0)
    {
        printk("Registering of device to kernel failed!");
        unregister_chrdev_region(device_number, 1);
        return -1;
    }

    // Create class
    if ((device_class = class_create(THIS_MODULE, NAME)) == NULL)
    {
        printk(KERN_ALERT "%s: failed to alocate class", NAME);
        cdev_del(&device_cdev);
        unregister_chrdev_region(device_number, 1);
        return -1;
    }
    
    if (device_create(device_class, NULL, device_number, NULL, NAME) == NULL)
    {
        printk(KERN_ALERT "%s: failed to allocate device file", NAME);
        cdev_del(&device_cdev);
        class_destroy(device_class);   
        unregister_chrdev_region(device_number, 1);
        return -1;
    }

    return 0;
}

static void __exit character_device_exit(void)
{
    cdev_del(&device_cdev);
    device_destroy(device_class, device_number);
    class_destroy(device_class);
    unregister_chrdev_region(device_number, 1);
    printk(KERN_INFO "Alvida: ofd unregistered");
}

module_init(character_device_init);
module_exit(character_device_exit);
