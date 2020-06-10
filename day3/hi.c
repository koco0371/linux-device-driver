#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int fd=open("/dev/koco",O_RDWR);
	if(fd<0) printf("ERROR\n");
	printf("GO\n");
	close(fd);

	return 0;
}
