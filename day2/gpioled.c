#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
// stdio.h is for printf
//fcntl.h, sys/types.h, sys/stat.h is for open
//unstd.h is for close,write,read
//stdlib.h is for atoi
//string.h is for strcpy, strcat
int main(int argc, char** argv){
	if(argc<2){	//we need number argument to execute this program
		printf("<Usage> %s number \n",argv[0]);	//usage example
		return 1;	//error return
	}
	int fd;//this variable is for file descirptor
	int num=atoi(argv[1]);	//this is for counting number-character
	if(num<10){	//if number character is  only one, we save 2 at num
		num=2;
	}
	else{	//if number character is two, we save 3 at num.
			//Because of NULL
		num=3;
	}
	char buf[BUFSIZ]; //this variable is for file path.
	fd=open("/sys/class/gpio/export",O_WRONLY);	//open export file, to allocate memory for LED
	if(fd<0){	//if there is an error, fd will be less than 0
		printf("open export error\n");
		return 1;	//error return
	}
	write(fd,argv[1],num); //we write argument number at this export file.
	close(fd);	//close file
	strcpy(buf,"/sys/class/gpio/gpio");	//for making file path
	strcat(buf,argv[1]);	//plus argument number
	strcat(buf,"/direction");	//plus direction 
	fd=open(buf,O_WRONLY);	//open gpio argv[1]/direction
	if(fd<0){	//if there is an error, fd will be less than 0
		printf("open direction error\n");
		return 1;	//error return
	}
	write(fd,"out",4);	//save direction for LED(OUT)
	close(fd);	//close file
	strcpy(buf,"/sys/class/gpio/gpio");	//for making file path
	strcat(buf,argv[1]);	//plus argument number
	strcat(buf,"/value");	//plus value
	fd=open(buf,O_WRONLY);	//open gpio argv[1]/value
	if(fd<0){	//if there is an error, fd will be less than 0
		printf("open value error\n");
		return 1;	//return error
	}
	write(fd,"1",2);	//save 1 at this file(LED ON);
	close(fd); //close file
	sleep(10);	//this delay is for check
	fd=open(buf,O_WRONLY);	//reopen gpio argv[1]/value
	if(fd<0){	//if there is an error, fd will be less than 0
		printf("open value error\n");
		return 1; //error return
	}
	write(fd,"0",2);	//save 0 at this file(LED off);
	close(fd);	//close file
	fd=open("sys/class/gpio/unexport",O_WRONLY);	//open unexport file, to release memory for LED
	if(fd<0){	//if there is an error, fd, will be less than 0
		printf("open unexport error\n");
		return 1;	//error return
	}
	write(fd,argv[1],num);	//write argument number
	close(fd);	//close file
	return 0;	//success return
}
