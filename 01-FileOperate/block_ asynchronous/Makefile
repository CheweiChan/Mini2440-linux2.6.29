CONFIG_MODULE_SIG=n

obj-m := polldevice.o

ifeq ($(KERNELDIR),)
KERNELDIR=/lib/modules/$(shell uname -r)/build
endif
KDIR := /home/parallels/Desktop/linux/linux-2.6.32.2/
KERNEL =/home/parallels/Desktop/linux_friendlyArm/opt/FriendlyARM/toolschain/4.4.3/bin/arm-none-linux-gnueabi-gcc
all:
	make -C $(KDIR) M=$(PWD) modules 
	$(KERNEL) -o poll_app poll_app.c
clean:
	make -C $(KERNELDIR) M=$(PWD) clean
