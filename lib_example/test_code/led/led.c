/*
 * led.c
 *
 *  Created on: 2014-4-09
 *  Author: Vic
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>

int main(int argc, char *argv[]){

	int fd;
	char buf;
	fd = open("/sys/class/leds/user-led\:red/brightness",O_WRONLY);
	if(fd<0){
		printf("Can not open led device.");
		return 0;
	}
	while(1){
		buf = '0';		// LED off
		write(fd,&buf,1);
		sleep(1);
		buf = '1';		// LED on
		write(fd,&buf,1);
		sleep(1);
	}
	close(fd);
	return 0;
}

