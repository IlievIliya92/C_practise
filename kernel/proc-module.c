#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>

static int proc_show(struct seq_file *m, void *v) {
	seq_printf(m, "Hello world!\n");
	return 0;
}

static int proc_open(struct inode *inode, struct file *file) {
	return single_open(file, proc_show, NULL);
}

static const struct file_operations proc_fops = {
	.owner = THIS_MODULE,
	.open = &proc_open,
	.read = &seq_read,
	.llseek = &seq_lseek,
	.release = &single_release
};

static int proc_init(void) {
	proc_create("proc-module", 0, NULL, &proc_fops);
	return 0;
}

static void proc_exit(void) {
	remove_proc_entry("proc-module", NULL);
}

module_init(proc_init);
module_exit(proc_exit);

