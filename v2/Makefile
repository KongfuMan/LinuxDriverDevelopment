KERNELDIR:=/lib/modules/$(shell uname -r)/build
CURRENT_PATH:= $(shell pwd)
DEVICE_NAME= newchrled
obj-m:= $(DEVICE_NAME).o

build: clean clear_printk remove_module kernel_modules cp_module dep_module probe_module

kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) modules

clear_printk:
	$(shell echo qqq  |  sudo -S dmesg -C)

cp_module:
	$(shell echo qqq  |  sudo -S cp $(CURRENT_PATH)/$(DEVICE_NAME).ko /lib/modules/5.8.0-63-generic/ -f)

dep_module:
	$(shell echo qqq  |  sudo -S depmod)

probe_module:
	$(shell echo qqq  |  sudo -S modprobe $(DEVICE_NAME))

remove_module:
	$(shell echo qqq  |  sudo -S rmmod $(DEVICE_NAME))

application:
	$(CC) ./chrdevbaseAPP.c -o chrdevbaseAPP
	$(shell echo qqq  |  sudo -S cp $(CURRENT_PATH)/chrdevbaseAPP /lib/modules/5.8.0-63-generic/ -f)

clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean