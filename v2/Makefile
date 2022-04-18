KERNELROOT:=/lib/modules/$(shell uname -r)/
KERNELDIR:=/lib/modules/$(shell uname -r)/build
CURRENT_PATH:= $(shell pwd)
PASSWORD:=qqq
DEVICE_NAME:=newchrled
APP_NAME:=chrdevbaseAPP
obj-m:= $(DEVICE_NAME).o

build: clean clear_printk remove_module kernel_modules cp_module dep_module probe_module

kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) modules

clear_printk:
	$(shell echo $(PASSWORD)  |  sudo -S dmesg -C)

cp_module:
	$(shell echo $(PASSWORD)  |  sudo -S cp $(CURRENT_PATH)/$(DEVICE_NAME).ko $(KERNELROOT) -f)

dep_module:
	$(shell echo $(PASSWORD)  |  sudo -S depmod)

probe_module:
	$(shell echo $(PASSWORD)  |  sudo -S modprobe $(DEVICE_NAME))

remove_module:
	$(shell echo $(PASSWORD)  |  sudo -S rmmod $(DEVICE_NAME))

application:
	$(CC) ./$(APP_NAME).c -o $(APP_NAME)
	$(shell echo $(PASSWORD)  |  sudo -S cp $(CURRENT_PATH)/$(APP_NAME) $(KERNELROOT) -f)

clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean