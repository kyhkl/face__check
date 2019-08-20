/*
 * main.c
 *
 *  Created on: 2013-3-14
 *      Author: tom
 */
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
	FILE *fp;
	fp = fopen("/dev/buzzer","w");
	if(fp==NULL){
		printf("Can not open the buzzer device.\n");
		return 0;
	}
	while(1){
		fprintf(fp,"0");
		fflush(fp);
		sleep(1);
		fprintf(fp,"1");
		fflush(fp);
		sleep(1);
	}
	fclose(fp);
}


