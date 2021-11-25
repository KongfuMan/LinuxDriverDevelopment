//
// Created by liang on 11/3/21.
//

#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
MODULE_LICENSE("GPL");


#define CHARDEVBASE_MAJOR  200 //major device number
#define CHARDEV_NAME "chardevchild"

static char readbuf[100];
static char writebuf[100];
static char krldate={"kernel data liang!"};

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
//    printk("char device base read\r\n");

//    copy_to_user()
    return 0;
}

static ssize_t chrdevbase_write(struct file *filp, const char *buf, size_t count, loff_t *ppos)
{
    printk("char device base write\r\n");
    return 0;
}

static struct file_operations chrdevbase_fops={
    .owner = THIS_MODULE,
    .open = chrdevbase_open,
    .release = chrdevbase_release,
    .read = chrdevbase_read,
    .write = chrdevbase_write
};

static int __init test_init(void)
{
    int ret = 0;
    printk(KERN_EMERG"Load module\r\n");
    //register a device
    ret = register_chrdev(CHARDEVBASE_MAJOR, CHARDEV_NAME, &chrdevbase_fops);
    if (ret < 0){
        printk("Failed to register device: %s\r\n", CHARDEV_NAME);
        return -1;
    }else{
        printk(KERN_EMERG"Device (%s) registered\r\n", CHARDEV_NAME);
    }
    return 0;
}
static void __exit test_exit(void)
{
    printk(KERN_EMERG"Unload module\r\n");
    unregister_chrdev(CHARDEVBASE_MAJOR, CHARDEV_NAME);
    printk(KERN_EMERG"Device (%s) unregistered", CHARDEV_NAME);
}

// fn will be executed when load / unload module
module_init(test_init);
module_exit(test_exit);