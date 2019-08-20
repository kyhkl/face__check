#ifndef SERIAL_APP_H
#define SERIAL_APP_H

#include <stdio.h> /* 标准输入输出定义*/
#include <stdlib.h> /* 标准函数库定义*/
#include <unistd.h> /*Unix  标准函数定义*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> /*文件控制定义*/
#include <termios.h> /*PPSIX  终端控制定义*/
#include <errno.h> /* 错误号定义*/
#include <linux/serial.h>
#include "sys/ioctl.h"


//#define SERIAL0   	"/dev/ttyO0"
#define SERIAL0   	"/dev/ttyO0"
#define SERIAL1 	"/dev/ttyO1"
#define SERIAL2   	"/dev/ttyO2"
#define SERIAL3 	"/dev/ttyO3"
#define SERIAL4 	"/dev/ttyO4"
#define SERIAL5 	"/dev/ttyS0"
#define SERIAL6 	"/dev/ttyS1"
#define TIOCGRS485      0x542E
#define TIOCSRS485      0x542F

extern int set_speed(int fd, int speed);//设置波特率

extern int set_Parity(int fd,int databits,int stopbits,int parity, int mode);//数据位  停止位  校验位

extern int OpenDev(char *Dev);//打开串口

extern int CloseDev(int fd);
#endif
