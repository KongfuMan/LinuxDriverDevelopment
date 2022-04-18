KERNELROOT:=/lib/modules/$(shell uname -r)/
KERNELDIR:=/lib/modules/$(shell uname -r)/build
PASSWORD:=qqq
APPNAME:=chrdevbaseAPP
MODULENAME:=chrdevchild
obj-m+= chrdevchild.o

CURRENT_PATH:= $(shell pwd)

build: clean kernel_modules clear_printk cp_module dep_module load_module refresh_dev_node application

kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) modules

clear_printk:
	$(shell echo $(PASSWORD)  |  sudo -S dmesg -C)

cp_module:
	$(shell echo $(PASSWORD)  |  sudo -S cp $(CURRENT_PATH)/$(MODULENAME).ko $(KERNELROOT) -f)

dep_module:
	$(shell echo $(PASSWORD)  |  sudo -S depmod)

load_module:
	$(shell echo $(PASSWORD)  |  sudo -S modprobe $(MODULENAME))

refresh_dev_node: #create device node (chrdevchild) under the /dev folder
	$(shell echo $(PASSWORD)  |  sudo -S rm /dev/$(MODULENAME))
	$(shell echo $(PASSWORD)  |  sudo -S mknod /dev/$(MODULENAME) c 200 0)

unload_module:
	$(shell echo $(PASSWORD)  |  sudo -S rmmod $(MODULENAME))

application: #compile application code into binary and copy into target folder
	$(CC) ./$(APPNAME).c -o $(APPNAME)
	$(shell echo $(PASSWORD)  |  sudo -S cp $(CURRENT_PATH)/$(APPNAME) $(KERNELROOT) -f)

clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean