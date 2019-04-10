/*****************************************************************
Filename:		keybutton.c
Author:			Vic
Date:			2014-04-09
Description:	keybutton test
******************************************************************/

#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>

typedef struct input_event INPUT_EVENT;

#define DEVICE_NAME "/dev/input/event0"

int main(int argc, char **argv)
{
	int fd;
	int num;
	INPUT_EVENT event;
	
	fd = open( DEVICE_NAME , O_RDONLY, 0);				
	if (fd < 0)
	{
		perror("Can't open button device...\n");
		return 0;
	}

	printf("Keybutton test.....\n");
	
	while(1)
	{
		num = read(fd, &event, sizeof(INPUT_EVENT));
		if (sizeof(INPUT_EVENT) != num)
		{
			printf("read data error\n");
			return 0;
		}

		if(event.type == EV_KEY)
		{	
			//printf("event type is key_event\n");

			// keybutton code
			switch (event.code)
			{
				case KEY_UP:
					printf("UP keybutton,the code is: %d",event.code);
					break;

				case KEY_DOWN:
					printf("DOWN  keybutton,the code is: %d",event.code);
					break;

				case KEY_LEFT:
					printf("LEFT  keybutton,the code is: %d",event.code);
					break;
				
				case KEY_RIGHT:
					printf("RIGHT  keybutton,the code is: %d",event.code);
					break;
				
				case KEY_ENTER:
					printf("ENTER  keybutton,the code is: %d",event.code);
					break;
				
				case KEY_ESC:
					printf("ESC  keybutton,the code is: %d",event.code);
					break;
			}

			// keybutton status
			if(event.value)
			{
				printf("    press down\n");						
			}
			else
			{
				printf("    press up\n");
			}

			printf("\n");
		}

	}
	return 0;
}

