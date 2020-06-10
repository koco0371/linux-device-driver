#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int fd=open("/dev/koco",O_RDWR);
	if(fd<0) printf("ERROR\n");
	write(fd, "Starbucks\n",7);
	char buf[100];
	read(fd,buf,100);
	printf("%s\n",buf);
	printf("%s\n",buf);
	printf("GO\n");

	ioctl(fd,3,0);
	ioctl(fd,4,0);
	ioctl(fd,5,0);

	close(fd);

	return 0;
}
