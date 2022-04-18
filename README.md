This is Linux kernel driver development project.

- V1 folder is the minimal runnable character device driver that demonstrate: 
    - Driver module implementing linux driver unified API: open/close, read/write
    - Make a device node that associate with the driver 
    - Application that read/write from the device using driver API