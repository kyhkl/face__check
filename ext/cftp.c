#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<unistd.h>
#include<netinet/in.h>
#include<netdb.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define FTP_ADDR "192.168.3.131"
#define FTP_PORT 21
#define USER_NAME "anonymous"
#define PASSWORD  "ky"
#define LEN 256

char * hello="hello ftp put cmd  ok\r\n";
char * dir_path="/b";
static int control_sock;
static int data_sockfd;
int login();
int put(void);
void zeromery(char *a,int len);


int main (void)
{
    if(login())
        put();
}


int login(void)
{
    struct sockaddr_in addr;
    int i = 0;
    char recv_buf[LEN];
    char send_buf[LEN];
    bzero(&addr, sizeof(addr));     //将＆addr中的前sizeof（addr）字节置为0，包括'\0'
    addr.sin_family = AF_INET;      //AF_INET代表TCP／IP协议
    addr.sin_addr.s_addr = inet_addr(FTP_ADDR); //将点间隔地址转换为网络字节顺序
    addr.sin_port = htons(FTP_PORT);    //转换为网络字节顺序
    int ret;
    
    //创建套接字
    if((control_sock=socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket Error!\n");
        return -1;
    }

    if(connect(control_sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        printf("Connect Error!\n");
        return -1;
    }
    
    /* 客户端接收服务器端的一些欢迎信息 */
    ret = read(control_sock, recv_buf, LEN);
    if(ret == -1)
    {
        printf("recvdate is connect error\n");  
    }
    else if(strncmp(recv_buf,"220",3)==0)
    {
        printf("socket connect success \n");
    }
    else 
    {
        printf("220 connect is error!");
    }
        bzero(recv_buf,LEN);  
        bzero(send_buf,LEN);  
        /* 命令 ”USER username\r\n” */   
        sprintf(send_buf,"USER %s\r\n",USER_NAME);  
        /*客户端发送用户名到服务器端 */   
        write(control_sock, send_buf, strlen(send_buf));   
        /* 客户端接收服务器的响应码和信息，正常为 ”331 User name okay, need password.” */  
        read(control_sock, recv_buf, LEN);     
        /* 命令 ”PASS password\r\n” */   
        sprintf(send_buf,"PASS %s\r\n",PASSWORD); 
        /* 客户端发送密码到服务器端 */   
        write(control_sock, send_buf, strlen(send_buf));  
        /* 客户端接收服务器的响应码和信息，正常为 ”230 User logged in, proceed.” */  
        read(control_sock, recv_buf, LEN);
        if(strncmp(recv_buf,"230",3)==0)
        {
            printf("login success\r\n");
            return 1;
        }
        else
            return 0;
}

int put (void)
{
     char recv_buf[LEN];
     char send_buf[LEN];
     bzero(recv_buf,LEN);  
     bzero(send_buf,LEN); 
        /* 命令 CWD \r\n” */   
     sprintf(send_buf,"CWD %s\r\n" ,dir_path);  
        /*客户端发送CWD到服务器端 */   
     write(control_sock, send_buf, strlen(send_buf));   
        /* 客户端接收服务器的响应码和信息*/  
     read(control_sock, recv_buf, LEN);     
        printf("change dir  return %s \r\n",recv_buf);
     if(strncmp(recv_buf,"250",3)==0)
        {
            printf("change dir return success code--250\r\n");
            //return 1;
        }
     else
        {
            printf("change dir return error\r\n");
            return 0;
        }   
    bzero(recv_buf,LEN);  
    bzero(send_buf,LEN); 
        /* 命令 ”PASV\r\n” */   
     sprintf(send_buf,"PASV\r\n");  
        /*客户端发送pasv到服务器端 */   
     write(control_sock, send_buf, strlen(send_buf));   
        /* 客户端接收服务器的响应码和信息，正常为 ”227 Entering Passive Mode (127,0,0,1,195,12).” */  
     read(control_sock, recv_buf, LEN);     
        printf("pasv return %s \r\n",recv_buf);
     if(strncmp(recv_buf,"227",3)==0)
        {
            printf("pasv return success code--227\r\n");
            //return 1;
        }
     else
        {
            printf("pasv return error\r\n");
            return 0;
        }   

        char *ptr1,*ptr2;
        char num[16];
        int i ,j ;
        struct sockaddr_in serv_addr;
        bzero(num,16);

        ptr1=recv_buf+strlen(recv_buf);
        while(*(ptr1)!=')')
        {
            ptr1--;
        }
        ptr2=ptr1;
        while(*(ptr2)!=',')
            ptr2--;
        strncpy(num,ptr2+1,ptr1-ptr2-1);
        i=atoi(num);
        bzero(num,16);
        ptr1=ptr2;
        ptr2--;
        while(*(ptr2)!=',')
            ptr2--;
        strncpy(num,ptr2+1,ptr1-ptr2-1);
        j=atoi(num);
   
        int data_serviceport;
        data_serviceport=j*256+i;
        data_sockfd=socket(AF_INET,SOCK_STREAM,0);
        printf("pasv return port %d \r\n",data_serviceport);   
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_addr.s_addr=inet_addr(FTP_ADDR);;
        serv_addr.sin_port=htons(data_serviceport);
        if(connect(data_sockfd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr))==-1)
        {
            printf("pasv data connect is error!\n");
        }
        else
        {
            printf("pasv data connect is success!\n");     
        }
        
        
         bzero(recv_buf,LEN);  
         bzero(send_buf,LEN); 
        sprintf(send_buf,"STOR %s\r\n","text.txt");  
        /*客户端发送pasv到服务器端 */   
        write(control_sock, send_buf, strlen(send_buf));   
        /* 客户端接收服务器的响应码和信息，正常为 ”227 Entering Passive Mode (127,0,0,1,195,12).” */  
        read(control_sock, recv_buf, LEN);         
        if(strncmp(recv_buf,"150",3)==0) 
        {
            printf("stor cmd return 150 ok\r\n");
        }   
        
        write(data_sockfd, hello, strlen(hello));  
        close(data_sockfd);
        bzero(recv_buf,LEN);  
        bzero(send_buf,LEN); 
        read(control_sock, recv_buf, LEN);         
        if(strncmp(recv_buf,"226",3)==0) 
        {
            printf("send file 226 ok\r\n");
        } 
        else
        {
            printf("send file error\r\n");
        }
        
}


