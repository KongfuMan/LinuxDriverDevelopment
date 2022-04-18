KERNELROOT:=/lib/modules/$(shell uname -r)/
KERNELDIR:=/lib/modules/$(shell uname -r)/build
PASSWORD:=qqq
obj-m+= chrdevchild.o

CURRENT_PATH:= $(shell pwd)

build: clean kernel_modules clear_printk cp_module dep_module load_module refresh_dev_node application

kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) modules

clear_printk:
	$(shell echo $(PASSWORD)  |  sudo -S dmesg -C)

cp_module:
	$(shell echo $(PASSWORD)  |  sudo -S cp $(CURRENT_PATH)/chrdevchild.ko $(KERNELROOT) -f)

dep_module:
	$(shell echo $(PASSWORD)  |  sudo -S depmod)

load_module:
	$(shell echo $(PASSWORD)  |  sudo -S modprobe chrdevchild)


refresh_dev_node:
	$(shell echo $(PASSWORD)  |  sudo -S rm /dev/chrdevchild)
	$(shell echo $(PASSWORD)  |  sudo -S mknod /dev/chrdevchild c 200 0)

unload_module:
	$(shell echo $(PASSWORD)  |  sudo -S rmmod chrdevchild)

application:
	$(CC) ./chrdevbaseAPP.c -o chrdevbaseAPP
	$(shell echo $(PASSWORD)  |  sudo -S cp $(CURRENT_PATH)/chrdevbaseAPP $(KERNELROOT) -f)

clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean