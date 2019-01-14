## Kernel Module
[GCC Extension of Linux Kernel](https://www.ibm.com/developerworks/cn/linux/l-gcc-hacks/index.html)

### pr\_info
```c
#define pr_info(fmt, ...) \
	printk(KERN_INFO pr_fmt(fmt), ##__VA_ARGS__)
```

use `dmesg -wH` to see output of `pr_info`

### Makefile Syntax
- install prerequisite

```bash
yum install kernel-devel-$(uname -r) -y
yum groupinstall "development tools" -y
```
- kernel version

```bash
uname -r
3.10.0-327.el7.x86_64

ll /lib/modules/$(uname -r)/build
lrwxrwxrwx. 1 root root 38 Feb  6  2018 /lib/modules/3.10.0-327.el7.x86_64/build -> /usr/src/kernels/3.10.0-327.el7.x86_64/
```

- make modules

```bash
make
make -C <enter-directory>

make modules
make -C <enter-directory> modules
```

use `bash` in `makefile`, should be `$(shell COMMAND)`

```makefile
# Use make M=dir to specify directory of external module to build
# Old syntax make ... SUBDIRS=$PWD is still supported
# Setting the environment variable KBUILD_EXTMOD take precedence
make -C /lib/modules/$(shell uname -r)/build SUBDIRS=$(PWD) modules
```

### modinfo
```bash
# modinfo reverse.ko
filename:       /data/kmodules/reverse.ko
description:    In-kernel phrase reverser
author:         1894 corsair<hi.pxiang@gmail.com>
license:        GPL
rhelversion:    7.2
srcversion:     7436E523283E1A4AEBBC29C
depends:
vermagic:       3.10.0-327.el7.x86_64 SMP mod_unload modversions
```

### pass parameters to module
```bash
insmod reverse.ko buffer_size=12
```

### Refer
#### reverse
<https://linux.cn/article-3251-1.html>
<https://linux.cn/article-3251-2.html>
<https://linux.cn/article-3251-3.html>