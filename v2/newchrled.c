//
// Created by liang on 11/24/21.
//

#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/device.h>
MODULE_LICENSE("GPL");

#define NEWCHRLED_NAME "newchrled"
#define NEWCHRLED_COUNT 1

typedef struct newchrled_dev {
    struct cdev cdev; /**char device*/
    dev_t devid;    /** device types*/
    struct class *class;
    struct device *device;
    int major;      /** major device number */
    int minor;      /** minor device number */
}newchrled_dev;

struct newchrled_dev newchrled;

static char readbuf[100];
static char writebuf[100];
static char krldate[] = {"kernel data liang!"};

static int chrdevbase_open(struct inode *inode, struct file *filp)
{
    printk("char device base open\r\n");
    return 0;
}

static int chrdevbase_release(struct inode *inode, struct file *filp)
{
    printk("char device base release\r\n");
    return 0;
}

static ssize_t chrdevbase_read(struct file *filp, __user char *buf, size_t count, loff_t *ppos)
{
    int ret = 0;
//    printk("char device base read\r\n");
    memcpy(readbuf, krldate, sizeof(krldate));

    //copy the readbuf(kernel space data) to user space
    ret = copy_to_user(buf, readbuf, count);
    if (ret <= 0){

    }else{
        //failed
        return -1;
    }
    return 0;
}

static ssize_t chrdevbase_write(struct file *filp, const char *buf, size_t count, loff_t *ppos)
{
    int ret = 0;
//    printk("char device base write\r\n");
    ret = copy_from_user(writebuf, buf, count);
    if (ret == 0){
        printk("received data from user: %s\r\n", writebuf);

    }else{
        //failed
        return -1;
    }
    return 0;
}

static const struct file_operations chrdevbase_fops={
        .owner = THIS_MODULE,
        .open = chrdevbase_open,
        .release = chrdevbase_release,
        .read = chrdevbase_read,
        .write = chrdevbase_write
};

static int __init newchrled_init(void)
{
    int ret = 0;
    printk(KERN_EMERG"newchrled module init \r\n");
    //1. register a device number
    if (newchrled.major){
        //register device number if major is given
        newchrled.devid = MKDEV(newchrled.major, 0);
        ret = register_chrdev_region(newchrled.devid, NEWCHRLED_COUNT, NEWCHRLED_NAME);
    }else{
        // apply for a device number
        ret = alloc_chrdev_region(&newchrled.devid, 0, NEWCHRLED_COUNT, NEWCHRLED_NAME);
        newchrled.major = MAJOR(newchrled.devid);
        newchrled.minor = MINOR(newchrled.devid);
    }
    if (ret < 0){
        printk("newharled chrdev region error\r\n");
        return -1;
    }
    printk("newchrled device major = %d, minor = %d\r\n", newchrled.major, newchrled.minor);

    // 2. register char device
    newchrled.cdev.owner= THIS_MODULE;
    cdev_init(&newchrled.cdev, &chrdevbase_fops);
    ret = cdev_add(&newchrled.cdev, newchrled.devid, NEWCHRLED_COUNT);

    // 3. Create device node under /dev/
    newchrled.class = class_create(THIS_MODULE, NEWCHRLED_NAME);
    if (IS_ERR(newchrled.class)){
        return PTR_ERR(newchrled.class);
    }

    // 4. Create char device under /proc/
    newchrled.device = device_create(newchrled.class, NULL, newchrled.devid, NULL, NEWCHRLED_NAME);
    if (IS_ERR(newchrled.device)){
        return PTR_ERR(newchrled.device);
    }

    return 0;
}
static void __exit newchrled_exit(void)
{
    printk(KERN_EMERG"newchrled module exit\r\n");
    // 1. delete char device
    cdev_del(&newchrled.cdev);

    // 2. unregister device number
    unregister_chrdev_region(newchrled.devid, NEWCHRLED_COUNT);

    // 3. destroy device
    device_destroy(newchrled.class, newchrled.devid);

    // 4. delete class which the device belongs to
    class_destroy(newchrled.class);
}

// fn will be executed when load / unload module
module_init(newchrled_init);
module_exit(newchrled_exit);
