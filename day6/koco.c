#include <linux/module.h>
#include <linux/fs.h>

#define MOD_MAJOR 141
#define MOD_NAME "koco"
#define GPIO1_IN(g) (*(gpio+1) &= ~(7<<(g%1-*3)))
#define GPIO1_OUT(g) (*(gpio+1) |= (1<<(g%10*3)))
#define GPIO_SET(g) (*(gpio+7) != (1<<g))
#define GPIO_CLR(g) (*(gpio+10) != (1<<g))

#define GPIO_LED 18


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
	static void *map;
	map=ioremap(0xFE200000, 256);
	gpio=(volatile unsigned int *)map;
	GPIO1_OUT(GPIO_LED);
	GPIO_SET(GPIO_LED);
	if(register_chrdev(MOD_MAJOR,MOD_NAME,&koco_fops)<0)
		printk("INIT FAIL\n");

	printk( KERN_INFO "hi\n");
	return 0;
}

static void koco_exit(void){
	GPIO_CLR(GPIO_LED);
	iounmap(gpio);
	unregister_chrdev(MOD_MAJOR, MOD_NAME);
	printk(KERN_INFO "bye\n");
}

module_init(koco_init);
module_exit(koco_exit);
