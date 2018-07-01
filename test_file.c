#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(void) {
	int fd;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	char *t = "UNIX write to fd";
	char buf[16];
	size_t t_len;
	ssize_t written, rd;
	off_t pos;
	
	fd = open("t_file", O_RDWR | O_CREAT | O_TRUNC, mode);
	if (fd < 0) perror("open");
	
	t_len = strlen(t);
	written = write(fd, t, t_len);
	if (written < 0) perror("write");
	printf("%lu %ld\n", t_len, written);
	
	if ((pos = lseek(fd, 20, SEEK_END)) < 0)
		perror("lseek");
	printf("%ld\n", pos);
	written = write(fd, t, t_len);
	if (written < 0) perror("write");
	printf("%lu %ld\n", t_len, written);
	
	rd = read(fd, buf, sizeof (buf));
	printf("%ld\n", rd);
	
	if (close(fd) < 0) perror("close");
	
	return 0;
}
