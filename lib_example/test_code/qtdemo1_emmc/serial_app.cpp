#include "serial_app.h"

/***********************************/
//#define  RS485  	0020000							// rs485
#define  Normal 	0020001							// normal
#define  HWHD		0020002							// hardware handing
#define	 Modem  	0020004							// modem
#define  ISO7816T0 	0020010							// iso7816 t=0
#define  ISO7816T1 	0020020							// iso7816 t=1
#define  IrDA	  	0020040							// IrDA
/***********************************/

//  设置串口通信速率
static int speed_arr[] = {B230400, B115200, B57600, B38400,
        B19200, B9600, B4800, B2400, B1800, B1200, B600, B300};
static int name_arr[]  = {230400,  115200,  57600,  38400,
        19200,  9600,  4800,  2400,  1800,  1200,  600,  300};

/****************************************************
brief: 设置串口波特率
param:
       1.fd  类型 int  打开的串口文件句柄
       2.speed  波特率
****************************************************/
int set_speed(int fd, int speed)
{
    int   i;
    int   status;
    struct termios   Opt;

    tcgetattr(fd, &Opt);

    for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)
    {
        if (speed == name_arr[i])
        {
            tcflush(fd, TCIOFLUSH);
            cfsetispeed(&Opt, speed_arr[i]);
            cfsetospeed(&Opt, speed_arr[i]);

            status = tcsetattr(fd, TCSANOW, &Opt);
            if  (status != 0)
            {
                perror("tcsetattr fd");
                return -1;
            }

            tcflush(fd,TCIOFLUSH);
            return 0;
        }
    }

    return -1;
}
//****************************************************
//brief: 设置串口数据位，停止位和效验位
//param:  fd  类型 int  打开的串口文件句柄
//param:  databits  类型 int  数据位  取值  为 7  或者 8
//param:  stopbits  类型 int  停止位  取值为 1 或者2
//param:  parity    类型 int  效验类型  取值为 N,E,O,S
//param:  mode      为0是RS232   为1是485
//****************************************************
int set_Parity(int fd,int databits,int stopbits,int parity, int mode)
{
    struct termios options;

    if (tcgetattr(fd, &options) != 0)
    {
        perror("SetupSerial 1");
        return -1;
    }
    options.c_cflag &= ~CSIZE;
    switch (databits)
    {
        case 7:
            options.c_cflag |= CS7;
            break;

        case 8:
            options.c_cflag |= CS8;
            break;

        default:
            fprintf(stderr,"Unsupported data size\n");
            return -1;
    }

    switch (parity)
    {
        case 'n':
        case 'N':
            options.c_cflag &= ~PARENB;   			// Clear parity enable
            options.c_iflag &= ~INPCK;     			// Enable parity checking
            break;

        case 'o':
        case 'O':
        case 1:
            options.c_cflag |= (PARODD | PARENB);
            options.c_iflag |= INPCK;             	// Disnable parity checking
            break;

        case 'e':
        case 'E':
        case 2:
            options.c_cflag |= PARENB;     			// Enable parity
            options.c_cflag &= ~PARODD;
            options.c_iflag |= INPCK;      			// Disnable parity checking
            break;

        case 'S':
        case 's':  /*as no parity*/
        case 0:
            options.c_cflag &= ~PARENB;
            options.c_cflag &= ~CSTOPB;
            break;

        default:
            fprintf(stderr,"Unsupported parity\n");
            return -1;
    }

    /*设置停止位*/
    switch (stopbits)
    {
        case 1:
            options.c_cflag &= ~CSTOPB;
            break;

        case 2:
            options.c_cflag |= CSTOPB;
            break;

        default:
            fprintf(stderr,"Unsupported stop bits\n");
            return -1;
    }

    /* Set input parity option */
    if (parity != 'n')
        options.c_iflag |= INPCK;

    tcflush(fd,TCIFLUSH);
    options.c_iflag = 0;
    options.c_oflag = 0;
    options.c_lflag = 0;
    options.c_cc[VTIME] = 150;
    options.c_cc[VMIN] = 0; 						// Update the options and do it NOW
//	options.c_oflag 0;

    switch(mode)
    {
        case 1:
           // rs485
//            options.c_cflag |= RS485;
           struct serial_rs485 rs485conf;
           rs485conf.flags |= SER_RS485_ENABLED;
           ioctl (fd, TIOCSRS485, &rs485conf);
           printf("Enable RS485 mode! \n");
            break;

        case 2:										// HWHD
            options.c_cflag |= HWHD;
            printf("Enable HWHD !\n");
            break;

        case 3:										// Modem
            options.c_cflag |= Modem;
            printf("Enable Modem !\n");
            break;

        case 4:										// ISO7816T0
            options.c_cflag |= ISO7816T0;
            printf("Enable ISO7816 T=0 \n");
            break;

        case 5:										// ISO7816T1
            options.c_cflag |= ISO7816T1;
            printf("Enable ISO7816 T=1 \n");
            break;

        case 6:										// IrDA
            options.c_cflag |= IrDA;
            printf("Enable IrDA \n");
            break;

        default:
            printf("Enable RS232 ! \n");
            break;
    }

    if (tcsetattr(fd,TCSANOW,&options) != 0)
    {
        perror("SetupSerial 3");
        return -1;
    }

    return 0;
}

int OpenDev(char *Dev)
{
    int fd = open( Dev, O_RDWR );   //| O_NOCTTY | O_NDELAY
    return fd;
}

int CloseDev(int fd)
{
    close(fd);
}
