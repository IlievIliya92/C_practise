#ifndef _CDEV_IOCTL_
#define _CDEV_IOCTL_

#include <linux/ioctl.h>

#define QUERY_VAR_GET _IOR('q', 1, int *)
#define QUERY_VAR_SET _IOW('q', 2, int *)
#define QUERY_VAR_RESET _IO('q', 3)

#endif
