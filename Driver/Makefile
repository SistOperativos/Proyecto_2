DRIVER=driver-arduino-comm
obj-m := $(DRIVER).o

default:
		$(MAKE) -C /lib/modules/$(shell uname -r)/build  M=$(shell pwd)

install: default
		sudo insmod $(DRIVER).ko

uninstall:
		sudo rmmod $(DRIVER)

createmem: 
		sudo mknod /dev/myarmdriver c 0 0

permission: 
		sudo chmod 666 /dev/myarmdriver

clean:
		rm -f *.o
		rm -f *.ko
		rm -f *.mod.c
		rm -f *.symvers
		rm -f *.order
		rm -rf .tmp_versions
		rm -rf .$(DRIVER)*
		rm -rf .cache*
		clear