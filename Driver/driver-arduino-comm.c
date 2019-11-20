/******************************************************************************/
/* Instituto Tecnológico de Costa Rica                                          */
/* Área Académica de Ingeniería en Computadores                                 */
/* Principios de Sistemas Operativos                                            */
/* Prof. Jason Leitón                                                           */
/*                                                                              */
/* DRIVER                                                                       */
/* Basado en: Tutorial 9 Profesor Jefersson Gonzales y                          */
/*            del foro sitio: https://forum.arduino.cc/index.php?topic=348538.0 */
/******************************************************************************/


#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h> 


/******************************************************************************/
/******************************* TTY Arduino **********************************/

static struct file *arduinotty_open(const char *filename, int flags, umode_t mode)
{
    return filp_open(filename, O_RDWR | O_NOCTTY, 0);
}

static ssize_t arduinotty_write(struct file *f, const char *buf, int count)
{

    int result;
    mm_segment_t oldfs;

    oldfs = get_fs();
    set_fs(KERNEL_DS);
    f->f_pos = 0;
    result = f->f_op->write(f, buf, count, &f->f_pos);
    set_fs(oldfs);

    return result;
}

static ssize_t arduinotty_read(struct file * f, char * buf, int count)
{
	int result = 0;
	mm_segment_t oldfs;
	oldfs = get_fs();
	set_fs(KERNEL_DS);
	result = f->f_op->read(f, buf, count, &f->f_pos);
	set_fs(oldfs);
	return result;
}

static void arduinotty_close(struct file *ardtty, fl_owner_t id)
{
        filp_close(ardtty, id);
}

/******************************************************************************/
/******************************* DRIVER OPS ***********************************/

DEFINE_MUTEX(drivermutex);
static struct file *ttyfile = NULL;
static int mydriver_open(struct inode *inode, struct file *filp)
{
    printk("<1>Open function of myarmdriver");
    char filename[20];

    /* only one process at a time */
    if(!(mutex_trylock(&drivermutex)))
        return -EBUSY;

    snprintf(filename, 20, "/dev/ttyACM%d", 0);
    ttyfile = arduinotty_open(filename, 0, O_RDWR);
    if (PTR_RET(ttyfile)) {
        mutex_unlock(&drivermutex);
        return PTR_RET(ttyfile);
    }

    return 0;
}

static int mydriver_release(struct inode *inode, struct file *file)
{
    printk("<1>Realease function of myarmdriver");
    if(!IS_ERR_OR_NULL(ttyfile))
        arduinotty_close(ttyfile, 0);
    mutex_unlock(&drivermutex);
    return 0;
}

static ssize_t mydriver_write(struct file *filp,
                 const char __user * buf, size_t count,
                 loff_t * f_pos)
{
    printk("<1>Write function of myarmdriver");

    const char kbuf[200];

    count = count < 200 ? count : 200;
    if (copy_from_user((char *)kbuf, (const char __user *)buf, count))
        return -EFAULT;
        
    if (!IS_ERR_OR_NULL(ttyfile))
        {printk(">>>>>>>>>> WRITTING %s\n\n",kbuf);
        return arduinotty_write(ttyfile, kbuf, count);}
    else
       { printk(">>>>>>> ERROR WRITTING\n");
        return -EFAULT;}
}

static ssize_t mydriver_read(struct file * flip, char __user * buf, size_t count,
		loff_t * f_pos)
{
    printk("<1>Read function of myarmdriver");
	char kbuf[200] = { '\0' };
	int result = 0;
	count = count < 200 ? count : 200;

	if (!IS_ERR_OR_NULL(ttyfile))
	{
		printk(KERN_INFO "Tying to read...Count: %d\n", count);
		result = arduinotty_read(ttyfile, kbuf, count);
		printk("Buf: %s\nResult: %d\n", kbuf, result);

		if (copy_to_user((char *)buf, (char __user *)kbuf, result))
		{
			printk(KERN_ERR "Cannot copy\n");
			return -EFAULT;
		}
	}
	else
	{
		return -EFAULT;
	}

	return result;
}

static struct file_operations mydriver_ops = {
    .owner = THIS_MODULE,
    .open = mydriver_open,
    .release = mydriver_release,
    .write = mydriver_write,
	.read = mydriver_read
};

static struct cdev cdev;
static struct class *class;
static int major_number;

static int mydriver_init(void)
{
    printk("<1>Init function of myarmdriver");

    dev_t devt = MKDEV(0, 0);
    if (alloc_chrdev_region(&devt, 0, 1, "myarmdriver") < 0)
        return -1;
    major_number = MAJOR(devt);

    cdev_init(&cdev, &mydriver_ops);
    cdev.owner = THIS_MODULE;
    devt = MKDEV(major_number, 0);
    if (cdev_add(&cdev, devt, 1))
        goto exit0;

    class = class_create(THIS_MODULE, "myarmdriver");
    if (!class)
        goto exit1;

    devt = MKDEV(major_number, 0);
    if (!(device_create(class, NULL, devt, NULL, "myarmdriver")))
        goto exit2;

    return 0;

    exit2:
        class_destroy(class);
    exit1:
        cdev_del(&cdev);
    exit0:
        unregister_chrdev_region(MKDEV(major_number, 0), 1);

    return -1;
}

static void mydriver_exit(void)
{
    printk("<1>Exit function of myarmdriver");
    device_destroy(class, MKDEV(major_number, 0));
    class_destroy(class);
    cdev_del(&cdev);
    unregister_chrdev_region(MKDEV(major_number, 0), 1);
}

module_init(mydriver_init);
module_exit(mydriver_exit);
MODULE_LICENSE("GPL");