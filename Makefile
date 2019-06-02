modname := keylogger
obj-m := $(modname).o

kisni-objs := a.o

KVERSION = $(shell uname -r)
KDIR := /lib/modules/$(KVERSION)/build

ifdef DEBUG
CFLAGS_$(obj-m) := -DDEBUG
endif

all:
	make -C $(KDIR) M=$(PWD) modules


