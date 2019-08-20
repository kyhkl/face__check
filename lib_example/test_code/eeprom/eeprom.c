#include <stdio.h>  
#include <string.h>  
#include <unistd.h>  
#include <sys/ioctl.h>  
#include <stdlib.h>  
#include <fcntl.h>  
#include <sys/io.h>  

int main(int argc, char **argv)  
{  
		int ret, fd, i, j;  
		char read_data[256];  
		char write_data[256];  
		char offset;  
		fd = open("/sys/devices/platform/omap/omap_i2c.1/i2c-1/1-0050/eeprom", O_RDWR); 
		if(fd < 0){  
				printf("Open at24c08 fail\n");  
				return -1;  
		}  
		ret = read(fd, &offset, 1);  
		if(ret < 0){  
				printf("Read error\n");  
				return -1;  
		}else if(ret < 1){  
				perror("Incomplete read\n");  
				printf("%d\n", ret);  
				return -1;  
		}  
		for(i = 0; i < 256; i++) 
				write_data[i] =  i;  
		lseek(fd, 0 , SEEK_SET);        //It's a must, or something wierd will happen  
		ret = write(fd, write_data, 256);  
		if(ret < 0){  
				printf("Write error\n");  
				return -1;  
		}  
		lseek(fd, 0 , SEEK_SET);     //It's a must, or something wierd will happen  
		ret = read(fd, read_data, 256);  
		if(ret < 0){  
				printf("Read error\n");  
				return -1;  
		}else if(ret < 256){  
				perror("Incomplete read\n");  
				printf("%d\n", ret);  
				return -1;  
		}
		for(i = 0; i < 256; i++){  
				if(i %16 == 0)  
						printf("\n");  
				printf(" %03d ", read_data[i]);  
		}
		printf("\n");        
		printf("eeprom test is successful\n");
}  

