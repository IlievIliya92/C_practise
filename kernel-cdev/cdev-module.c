#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <asm/uaccess.h>

#include "cdev-ioctl.h"

#define HELLO_SIZE 128

static char hello[HELLO_SIZE];
static const ssize_t hello_len = sizeof (hello);
static int var = 0;

static ssize_t cdev_read(struct file *file, char *buf, size_t num, loff_t *pos) {
	if (*pos >= hello_len) return 0;
	if ((*pos + num) > hello_len) num = hello_len - *pos;
	if (copy_to_user(buf, hello + *pos, num))
		return -EFAULT;
	*pos += num;
	return num;
}

static ssize_t cdev_write(struct file *file, const char *buf, size_t num, loff_t *pos) {
	if (*pos >= hello_len) return 0;
	if ((*pos + num) > hello_len) num = hello_len - *pos;
	if (copy_from_user(hello + *pos, buf, num))
		return -EFAULT;
	*pos += num;
	return num;
}

static long cdev_ioctl(struct file *f, unsigned int cmd, unsigned long arg) {
	switch (cmd) {
	case QUERY_VAR_GET:
		if (copy_to_user((int *)arg, &var, sizeof(var)))
			return -EACCES;
		break;
	case QUERY_VAR_SET:
		if (copy_from_user(&var, (int *)arg, sizeof (var)))
			return -EACCES;
		break;
	case QUERY_VAR_RESET:
		var = 0;
		break;
	default:
		return -EINVAL;
	}
	
	return 0;
}

static struct file_operations cdev_ops = {
	.owner = THIS_MODULE,
	.read = &cdev_read,
	.write = &cdev_write,
	.unlocked_ioctl = &cdev_ioctl,
};

static const char *cdev_name = "our_cdev";
static int cdev_major = 0;

static int cdev_module_init(void) {
	int r = 0;
	ssize_t j;
	
	r = register_chrdev(0, cdev_name, &cdev_ops);
	if (r < 0) {
		printk("cdev_init failed with r = %d\n", r);
		return r;
	}
	cdev_major = r;
	
	for (j = 0; j < hello_len; j++)
		hello[j] = '\0';
	
	printk("registered cdev with major = %d\n", cdev_major);
	
	return 0;
}

static void cdev_module_exit(void) {
	if (cdev_major)
		unregister_chrdev(cdev_major, cdev_name);
	return;
}

module_init(cdev_module_init);
module_exit(cdev_module_exit);

