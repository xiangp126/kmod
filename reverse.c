/* three common headers to include */
#include <linux/init.h>     /* module_init and module_exit macros */
#include <linux/kernel.h>   /* pr_info macros */
#include <linux/module.h>   /* required for all kernel modules */
#include <linux/moduleparam.h>	/* module_param() and MODULE_PARM_DESC() */
#include <linux/fs.h>		    /* struct file_operations, struct file */
#include <linux/miscdevice.h>	/* struct miscdevice and misc_[de]register() */
#include <linux/mutex.h>	    /* mutexes */
#include <linux/string.h>	    /* memchr() function */
#include <linux/slab.h>		    /* kzalloc() function */
#include <linux/sched.h>	    /* wait queues */
#include <linux/uaccess.h>	    /* copy_{to,from}_user() */

static unsigned long buffer_size = 8192;
module_param(buffer_size, ulong, (S_IRUSR | S_IRGRP | S_IROTH));
MODULE_PARM_DESC(buffer_size, "Internal buffer size");

static struct miscdevice reverse_misc_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name  = "reverse",
    .fops  = &reverse_fops
};

static struct file_operations reverse_fops = {
    .owner   = THIS_MODULE,
    .open    = reverse_open,
    .read    = reverse_read,
    .write   = reverse_write,
    .release = reverse_close,
    .llseek  = noop_llseek
};

struct buffer {
    char *data;
    char *end;
    char *read_ptr;
    unsigned long size;
};

/* the initialization function */
static int __init reverse_init(void)
{
    if (!buffer_size)
        return -1;

    misc_register(&reverse_misc_device);
    pr_info("reverse device has been registered, buffer size is %lu bytes.\n",
                buffer_size);
    return 0;
}

/* the shutdown function */
static void __exit reverse_exit(void)
{
    misc_deregister(&reverse_misc_device);
    pr_info("Goodbye!\n");
}

/* declares which function will be invoked when the module is loaded */
module_init(reverse_init);

/* declares which function will be invoked when the module is removed */
module_exit(reverse_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("1894 corsair<hi.pxiang@gmail.com>");
MODULE_DESCRIPTION("In-kernel phrase reverser");
