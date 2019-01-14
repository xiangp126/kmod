MAKE := make
CC   := gcc
LD   := ld
PWD  := $(shell pwd)

# build *.o as an module, not into kernel
obj-m := reverse.o
# put extra headers here
# ccflags-y := -I$(PWD)/include

ifeq ($(KERNDIR), )
	KDIR := /lib/modules/$(shell uname -r)/build
else
	KDIR := $(KERNDIR)
endif

ifeq ($(DEBUG), )
	ccflangs-y += -g3 -O0
endif

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) modules clean

install:
	if [ -d "$(INSDIR)" ]; then \
		install -m 644 reverse.ko $(INSDIR)/reverse.ko; \
	fi
