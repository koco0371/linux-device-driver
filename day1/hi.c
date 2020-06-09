#include <linux/module.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("PSW");
MODULE_DESCRIPTION("My Device Driver");
MODULE_INFO(KFC, "jmt");
int mod_init(void)
{
	printk( KERN_INFO "\n");
	printk( KERN_INFO "hi\n");
	printk( KERN_INFO "hi\n");
	printk( KERN_INFO "hi\n");
	printk( KERN_INFO "\n");
	return 0;
}
void mod_exit(void)
{
	printk( KERN_INFO "\n");
	printk( KERN_INFO "bye\n");
	printk( KERN_INFO "bye\n");
	printk( KERN_INFO "bye\n");
	printk( KERN_INFO "\n");
}
module_init(mod_init);
module_exit(mod_exit);
