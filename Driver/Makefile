DRIVER=driver-arduino-comm

obj-m:= $(DRIVER).o



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