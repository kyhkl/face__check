/*
 *omap_Watchdog Driver Test Program
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/watchdog.h>

int fd;
/*
 * This function simply sends an IOCTL to the driver, which in turn ticks
 * the PC Watchdog card to reset its internal timer so it doesn't trigger
 * a computer reset.
 */
static void keep_alive(void)
{
    int dummy;

    ioctl(fd, WDIOC_KEEPALIVE, &dummy);
}
/*
 * The main program.  Run the program with "-d" to disable the card,
 * or "-e" to enable the card, or "-t time" to set time.
 */
int main(int argc, char *argv[])
{
	int timeout,tmp;

    fd = open("/dev/watchdog", O_WRONLY);

    if (fd == -1) {
	fprintf(stderr, "Watchdog device not enabled.\n");
	fflush(stderr);
	exit(-1);
    }

    if (argc > 1) {
	if (!strncasecmp(argv[1], "-d", 2)) {
	    ioctl(fd, WDIOS_DISABLECARD, &timeout);
	    fprintf(stderr, "Watchdog card disabled.\n");
	    fflush(stderr);
	    exit(0);
	} else if (!strncasecmp(argv[1], "-e", 2)) {
	    ioctl(fd, WDIOS_ENABLECARD, &timeout);
	    fprintf(stderr, "Watchdog card enabled.\n");
	    fflush(stderr);
	    exit(0);
	}else if(!strncasecmp(argv[1],"-t",2)){
		printf("Please select from the following timeout period corresponding figures!\n");
		printf("1  <=====> 5s\n");
		printf("2  <=====> 10s\n");
		printf("3  <=====> 15s\n");
		printf("4  <=====> 20s\n");
		printf("5  <=====> 25s\n");
		printf("6  <=====> 30s\n");
		printf("7  <=====> 35s\n");
		printf("8  <=====> 40s\n");
		printf("9  <=====> 45s\n");
		printf("10 <=====> 50s\n");
		printf("11 <=====> 55s\n");
		printf("12 <=====> 60s\n");
		
		printf("Please input your choose number: ");
		scanf("%d",&tmp);
		printf("\n");
				
		switch(tmp){
		case 1:
				timeout=5;
				printf("your choice number is %d,timeout is %d s\n",tmp,timeout);
				break;
		case 2:
				timeout=10;
				printf("your choice number is %d,timeout is %d s\n",tmp,timeout);
				break;
		case 3:
				timeout=15;
				printf("your choice number is %d,timeout is %d s\n",tmp,timeout);
				break;
		case 4:
				timeout=20;
				printf("your choice number is %d,timeout is %d s\n",tmp,timeout);
				break;
		case 5:
				timeout=25;
				printf("your choice number is %d,timeout is %d s\n",tmp,timeout);
				break;
		case 6:
				timeout=30;
				printf("your choice number is %d,timeout is %d s\n",tmp,timeout);
				break;
		case 7:
				timeout=35;
				printf("your choice number is %d,timeout is %d s\n",tmp,timeout);
				break;
		case 8:
				timeout=40;
				printf("your choice number is %d,timeout is %d s\n",tmp,timeout);
				break;
		case 9:
				timeout=45;
				printf("your choice number is %d,timeout is %d s\n",tmp,timeout);
				break;
		case 10:
				timeout=50;
				printf("your choice number is %d,timeout is %d s\n",tmp,timeout);
				break;
		case 11:
				timeout=55;
				printf("your choice number is %d,timeout is %d s\n",tmp,timeout);
				break;
		case 12:
				timeout=60;
				printf("your choice number is %d,timeout is %d s\n",tmp,timeout);
				break;
		default: 
				timeout=10;
				printf("The number of your choice is not within the scope, by default 10s !\n");
				break;
		}
		ioctl(fd,WDIOC_SETTIMEOUT, &timeout);
		fprintf(stderr,"Watchdog card settimout.\n");
		fflush(stderr);
	}else {
	    fprintf(stderr, "-d to disable, -e to enable,-t x to set timemout.\n");
	    fprintf(stderr, "run by itself to tick the card.\n");
	    fflush(stderr);
	    exit(0);
	}
    } else {
	fprintf(stderr, "Watchdog Ticking Away!\n");
	fflush(stderr);
    }

    while(1) {
	keep_alive();
	sleep(1);
    }
}
