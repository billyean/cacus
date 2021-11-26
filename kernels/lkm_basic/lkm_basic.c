#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_AUTHOR("john doe");
MODULE_DESCRIPTION("This is a dumb module, nothing else but print something");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.01");

static int __init basic_lkm_init(void)
{
    printk(KERN_INFO "Dude, new module\n");
    return 0;
}

static void __exit basic_lkm_exit(void)
{
    printk(KERN_INFO "I am leaving, Dude\n");
}

module_init(basic_lkm_init);
module_exit(basic_lkm_exit);



