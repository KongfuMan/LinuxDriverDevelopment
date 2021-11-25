KERNELDIR:=/lib/modules/$(shell uname -r)/build

obj-m+= chrdevchild.o

CURRENT_PATH:= $(shell pwd)

build: clean kernel_modules clear_printk cp_module dep_module load_module application

kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) modules

clear_printk:
	$(shell echo qqq  |  sudo -S dmesg -C)

cp_module:
	$(shell echo qqq  |  sudo -S cp /home/liang/Documents/projects/LinuxDriver/1_chardevbase/chrdevchild.ko /lib/modules/5.8.0-63-generic/ -f)

dep_module:
	$(shell echo qqq  |  sudo -S depmod)

load_module:
	$(shell echo qqq  |  sudo -S modprobe chrdevchild)

unload_module:
	$(shell echo qqq  |  sudo -S rmmod chrdevchild)

application:
	$(CC) ./chrdevbaseAPP.c -o chrdevbaseAPP
	$(shell echo qqq  |  sudo -S cp /home/liang/Documents/projects/LinuxDriver/1_chardevbase/chrdevbaseAPP /lib/modules/5.8.0-63-generic/ -f)

clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean