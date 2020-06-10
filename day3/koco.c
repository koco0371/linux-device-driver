#include <linux/module.h>
#include <linux/fs.h>

#define MOD_MAJOR 141
#define MOD_NAME "koco"

MODULE_LICENSE("GPL");

static int koco_open(struct inode *inode, struct file *filp){
		printk(KERN_INFO "welcome\n");
		return 0;
}

static int koco_release(struct inode *inode, struct file *filp){
	printk(KERN_INFO "release\n");
	return 0;
}

static struct file_operations koco_fops={
	.open	= koco_open,
	.release	= koco_release,
};

static int koco_init(void){
	if(register_chrdev(MOD_MAJOR,MOD_NAME,&koco_fops)<0)
		printk("INIT FAIL\n");

	printk( KERN_INFO "hi\n");
	return 0;
}

static void koco_exit(void){
	unregister_chrdev(MOD_MAJOR, MOD_NAME);
	printk(KERN_INFO "bye\n");
}

module_init(koco_init);
module_exit(koco_exit);
