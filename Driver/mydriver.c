/* Necessary includes for device drivers */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h> /* O_ACCMODE */
#include <linux/uaccess.h> /* copy_from/to_user */
MODULE_LICENSE("Dual BSD/GPL");

/* Declaration of mydriver.c functions */
int mydriver_open(struct inode *inode, struct file *filp);
int mydriver_release(struct inode *inode, struct file *filp);
ssize_t mydriver_read(struct file *filp, char *buf,
size_t count, loff_t *f_pos);
ssize_t mydriver_write(struct file *filp, const char *buf,
size_t count, loff_t *f_pos);
void mydriver_exit(void);
int mydriver_init(void);
/* Structure that declares the usual file */
/* access functions */
struct file_operations mydriver_fops = {
	read: mydriver_read,
	write: mydriver_write,
	open: mydriver_open,
	release: mydriver_release
};


/* Declaration of the init and exit functions */
module_init(mydriver_init);
module_exit(mydriver_exit);

/* Global variables of the driver */
/* Major number */
int mydriver_major = 60;
/* Buffer to store data */
char *mydriver_buffer;

int mydriver_init(void) {
	int result;
	/* Registering device */
	result = register_chrdev(mydriver_major, "driver-mem", &mydriver_fops);
	printk("<1>Result %d\n", result);
	if (result < 0) {
		printk("<1>ttyACM0: cannot obtain major number %d\n", mydriver_major);
		return result;
	}
	/* Allocating memory for the buffer */
	mydriver_buffer = kmalloc(1, GFP_KERNEL);
	if (!mydriver_buffer) {
		result = -ENOMEM;
		goto fail;
	}
	/*Set buffer to 0 by default */
	memset(mydriver_buffer, 0, 1);
	printk("<1> Inserting mydriver module\n");
	return 0;
	fail:
	mydriver_exit();
	return result;
}

void mydriver_exit(void) {
	/* Freeing the major number */
	unregister_chrdev(mydriver_major, "driver-mem");
	/* Freeing buffer mydriver */
	if (mydriver_buffer) {
		kfree(mydriver_buffer);
	}
	printk("<1> Removing mydriver module\n");
}

int mydriver_open(struct inode *inode, struct file *filp) {
	/* Success */
	return 0;
}

int mydriver_release(struct inode *inode, struct file *filp) {
	/* Success */
	return 0;
}

ssize_t mydriver_read(struct file *filp, char *buf,
										size_t count, loff_t *f_pos) {
	printk("<1>Reading\n");
	/* Changing reading position as best suits */
	if (*f_pos == 0) {
		*f_pos+=1;
		/* Transfering data to user space */
		copy_to_user(buf,mydriver_buffer,1);
		return 1;
	} else {
		return 0;
	}
}

ssize_t mydriver_write( struct file *filp, const char *buf,
											size_t count, loff_t *f_pos) {
	printk("<1>Writing\n");
	copy_from_user(mydriver_buffer,buf,1);
	
	//file->f_op->open(file, (char *)&ac, sizeof(struct acct), &file->f_pos);


	return 1;
}