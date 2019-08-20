#include <stdio.h>
#include <linux/rtc.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

static const char default_rtc[] = "/dev/rtc";

int main(int argc, char **argv)
{
    int i, fd, retval, irqcount = 0;
    unsigned long tmp, data;
    struct rtc_time rtc_tm;
    const char *rtc = default_rtc;
    

    fd = open(rtc, O_RDONLY);
    if (fd == -1) {
        perror(rtc);
        exit(errno);
    }
    fprintf(stderr, "\n\t\tRTC Driver Test Example.\n");
    
    /* Read the RTC time/date */
    for (i=0; i<10; i++) {
	sleep(1);
	retval = ioctl(fd, RTC_RD_TIME, &rtc_tm);
    	if (retval == -1) {
        	perror("RTC_RD_TIME ioctl");
        	exit(errno);
    	}
    	printf("Current RTC date/time is %d-%d-%d, %02d:%02d:%02d.\n",
		rtc_tm.tm_mday, rtc_tm.tm_mon + 1, rtc_tm.tm_year + 1900,
		rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);
    }

    fprintf(stderr, "\n\t\t *** Test complete ***\n");
    close(fd);
    return 0;
}

