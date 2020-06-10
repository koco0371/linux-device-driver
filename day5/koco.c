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

ssize_t koco_read(struct file *filp, char *buf, size_t count, loff_t *ppos){
	buf[0]='H';
	buf[1]='I';
	buf[2]='\0';
	return count;
}
ssize_t koco_write(struct file *filp, const char *buf, size_t count, loff_t *ppos){
	printk(KERN_INFO "app message : %s\n", buf);
	return count;
}
long koco_ioctl(struct file *filp, unsigned int cmd, unsigned long arg){
	printk(KERN_ALERT"%d\n",cmd);
	switch(cmd){
		case 3:
			printk(KERN_INFO "HI - ioctl 3\n");
			break;
		case 4:
			printk(KERN_INFO "HI - ioctl 4\n");
			break;
		case 5:
			printk(KENR_INFO "HI - ioctl 5 \n");
			break;
	}
	return 0;
}
static struct file_operations koco_fops={
	.open	= koco_open,
	.release	= koco_release,
	.read = koco_read,
	.write = koco_write,
	.unlocked_ioctl = koco_ioctl,
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
