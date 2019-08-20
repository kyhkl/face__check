#include "config.h"

#define MAXBYTEMUN   1024

/**  
 * activiate_nonblock  设置IO为非阻塞模式
 * fd 文件描述符
 */
void activiate_nonblock(int fd)
{
    int ret;
    int flags = fcntl(fd,F_GETFL);  //获取fd的当前标记
    if(flags == -1)
        perror("fcntl");
    
    flags |= O_NONBLOCK;            //与新标记逻辑或
    ret = fcntl(fd,F_SETFL,flags);  //设置标记
    if(ret == -1)
        perror("fntl");
}
/**  
 * deactiviate_nonblock  设置IO为阻塞模式
 * fd 文件描述符
 */
 void deactiviate_nonblock(int fd)
{
    int ret;
    int flags = fcntl(fd,F_GETFL);  //获取fd的当前标记
    if(flags == -1)
        perror("fcntl");
    
    flags &=~O_NONBLOCK;            //与新标记逻辑与
    ret = fcntl(fd,F_SETFL,flags);  //设置标记
    if(ret == -1)
        perror("fntl");
}

/**
 *connect_timeout 带超时的accept函数
 *fd：文件描述符
 *addr 要连接的对等方的地址结构
 *wait_seconds：等待超时秒数，如果为0则表示正常模式
 *成功（未超时）返回0，失败返回-1，超时返回-1并且errno=ETIMEDOUT
 */
 int connect_timeout(int fd,struct sockaddr_in *addr,unsigned int wait_seconds)
 {
     int ret=0;           //默认为0，当wait_seconds==0时，不检测直接返回0
     socklen_t addrlen =sizeof(struct sockaddr_in);
     if(wait_seconds>0)  //需要检测超时
        activiate_nonblock(fd); //设置套接字为非阻塞模式
    ret=connect(fd,(struct sockaddr*)addr,addrlen);  
    if(ret<0 && errno == EINPROGRESS)   //连接失败而且是因为连接正在处理中
     {
         fd_set connect_fdset;      //描述符集合
         struct timeval timeout;  //超时时间
         
         FD_ZERO(&connect_fdset);
         FD_SET(fd,&connect_fdset);
         
         timeout.tv_sec = wait_seconds;
         timeout.tv_usec = 0;
         do
         { 
             /*一旦连接建立，套接字就处于可写的状态*/
             ret=select(fd+1,NULL,&connect_fdset,NULL,&timeout);
             /*
              * select会阻塞直到检测到事件或则超时，如果超时，select会返回0，
              * 如果检测到事件会返回1，如果异常会返回-1，
              * 如果是由于信号中断引起的异常errno==EINTR
             */
            
         }
         while(ret<0 && errno == EINTR);   //如果是有信号引起的异常则继续阻塞select，直到检测到事件或则超时
         
         if(ret==-1) //失败
         {
             
             return -1;
         }
         else if(ret==0) //select超时退出
         {
             errno= ETIMEDOUT;
             return -1;
         }
         else if(ret==1) 
         {
            /*ret为1有两种情况，一种是连接建立成功，一种是套接字产生错误 
              此时错误信息不回保存在errno变量中，因此，需要调用getsockopt函数来获取。*/
             int err;
             socklen_t socklen = sizeof(err);
             int sockoptret = getsockopt(fd,SOL_SOCKET,SO_ERROR,&err,&socklen);//获取套接字的错误放在err中
             if(sockoptret == -1)  //调用getsockopt失败
             {
                  return -1;
             }
             if(err==0) //表示没有错误即套接字建立连接成功
                ret=0;
             else    //套接字产生错误
             {
                 errno=err;
                 ret=-1;
             }                 
         }
     }
    
    if(wait_seconds>0)
    {
        deactiviate_nonblock(fd);     //重新将套接字设为阻塞模式
    }
     return ret;    
  }
 
 /*
 int main(int argc,char *argv[])
{
    int sock_fd,numbytes,maxfd,fd_stdin,nready;
    struct hostent;
    struct sockaddr_in client_addr;//客户机的地址信息
    ssize_t ret;
    char recvbuf[1024]={'0'},sendbuf[1024]={'0'};
    fd_set  rset;
        int stdineof;
    
    if(argc!=2)
    {
        fprintf(stderr,"usage: client IPAddress\n");   //执行客户端程序时，输入客户端程序名称和其IP地址
        exit(1);    
    }
    
    /*创建套接字*
    sock_fd=socket(AF_INET,SOCK_STREAM,0);//采用IPv4协议
    if(sock_fd==-1)
    {
        perror("creat socket failed");
        exit(1);
    }
    
    /*服务器地址参数*
    client_addr.sin_family=AF_INET;  
    client_addr.sin_port=htons(3490);
    client_addr.sin_addr.s_addr=inet_addr(argv[1]);
    bzero(&client_addr.sin_zero,sizeof(struct sockaddr_in));//bzero位清零函数，将sin_zero清零，sin_zero为填充字段，必须全部为零
    
    
    /*连接到服务器*
    ret=connect_timeout(sock_fd,(struct sockaddr*)&client_addr,10);
    if(ret==-1 && errno ==ETIMEDOUT)
    {
        perror("connect timedout\n");
        exit(1);
    }
    else if(ret==-1)
        perror("connect error\n");
    
    if((numbytes=recv(sock_fd,recvbuf,MAXBYTEMUN,0))==-1)
        {       
            perror("receive failed");
            exit(1);
        }
        
    recvbuf[numbytes]='\0';//在字符串末尾加上\0，否则字符串无法输出
    printf("Received: %s\n",recvbuf);
    return 0;
}
 */
