#include "config.h"

#define Cmd_Buf_Len  128
#define Cmd_Ret_Len  256

static int control_sock;
static int data_sockfd;

struct hostent* hostent_t;

int login(void)
{
    struct sockaddr_in addr;
   
    bzero(&addr, sizeof(addr));     //将＆addr中的前sizeof（addr）字节置为0，包括'\0'
   
    int port;
    int ret;
    port = atoi(config_info.ftp_port);
    addr.sin_family = AF_INET;      //AF_INET代表TCP／IP协议
    hostent_t = gethostbyname(config_info.ftp_ip);
    addr.sin_addr = *((struct in_addr *)hostent_t->h_addr_list[0]);//将点间隔地址转换为网络字节顺序
    addr.sin_port = htons(port);    //转换为网络字节顺序
    //创建套接字
    if((control_sock=socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket Create Error!\n");
        return ftp_connect_faild;
    }
    
    
      /*连接到服务器*/
    ret=connect_timeout(control_sock,(struct sockaddr*)&addr,5);
    if(ret==-1 && errno ==ETIMEDOUT)
    {
        printf("ftp connect timeout\n");
        return  ftp_connect_faild;
    }
    else if(ret==-1)
    {
        printf("inner net connect error\n");
         return  ftp_connect_faild;
    }
    
/*
    if(connect(control_sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        printf("Ftp Connect Error!\n");
        return ftp_connect_faild;
    }
*/
		 /* 客户端接收服务器端的一些欢迎信息 */
		if(read_ret("socket","220" ) < 0)
		{
			printf("socket connect error\r\n");
			return ftp_connect_faild;
		}
		if( send_cmd("USER" ,config_info.ftp_user) < 0 )
		{
		   printf("send username cmd error\r\n");
		  return ftp_connect_faild;
		}
		if(read_ret("USER","331" ) < 0)
		{
			printf("username retrun code error\r\n");
			return ftp_connect_faild;
		}    
        if(send_cmd("PASS" ,config_info.ftp_passwd) < 0 )
		{
		   printf("send passworld cmd error\r\n");
		   return ftp_connect_faild;
		}
		if(read_ret("PASS ","230" ) < 0)
		{
			printf("passworld retrun code error\r\n");
			return ftp_connect_faild;
		}
		
		return ret_ok;
}
//切换目录
int change_dir(char * dirname)
{
	 if(send_cmd("CWD" ,dirname) < 0 )
		{
		   return change_dir_faild;
		}
	if(read_ret("CWD ","250" ) < 0)
		{
			return change_dir_faild;
		}
		return ret_ok;
}
//创建目录
int makedir(char * dirname)
{
	char cmd_read_buf[Cmd_Ret_Len];
	int ret = 0;
	bzero(cmd_read_buf,Cmd_Ret_Len);
	if(send_cmd("MKD" ,dirname) < 0 )
		{
		   return create_dir_faild;
		}
	ret = read(control_sock, cmd_read_buf, Cmd_Ret_Len);
	if(ret == -1)
    {
		return create_dir_faild;
    }
    else if(strncmp(cmd_read_buf,"257",3)==0)//????′′?¨3é1|
    {
		return ret_ok;
    }
	else if(strncmp(cmd_read_buf,"550",3)==0)//????ò??-′??ú
    {
		return ret_ok;
    }
    else 
    {
		return create_dir_faild;
    }	
		
}
//上传文件
int put(char * buf,int len)
{	
	char recv_buf[Cmd_Ret_Len];
	char *ptr1,*ptr2;
    char num[16];
    int i ,j ;
    struct sockaddr_in serv_addr;
    
    bzero(num,16);
	bzero(recv_buf,Cmd_Ret_Len);
  
    if (change_dir(config_info.ftp_path) != ret_ok)//切换目录
	{
		printf("change dir faild\r\n");
		return change_dir_faild;
	}
    if (makedir(config_info.equip_id) != ret_ok)//创建目录
	{
		printf("mkdir dir faild\r\n");
		return create_dir_faild;
	}
    if(change_dir(config_info.equip_id) != ret_ok)//切换目录
	{
		printf("change dir faild\r\n");
		return change_dir_faild;
	}
    
   if(send_cmd("PASV\r\n" ,NULL) < 0 )//进入pasv模式   
		{
		   return ret_error;
		}
    usleep(100000);    
   read(control_sock, recv_buf, Cmd_Ret_Len);     
       
   if(strncmp(recv_buf,"227",3)!=0)
       {
            return re_capture;
        }   
	ptr1=recv_buf+strlen(recv_buf);
	while(*(ptr1)!=')')
		ptr1--;
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
	//printf("pasv return port %d \r\n",data_serviceport);   
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr = *((struct in_addr *)hostent_t->h_addr_list[0]);
	serv_addr.sin_port=htons(data_serviceport);
	if(connect(data_sockfd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr))==-1)//创建socket 并连接数据端口
	{
		printf("pasv mode socket connect  error!\n");
        return ret_error;
	}

    if(send_cmd("STOR" ,sys_info.jpeg_name) < 0 )//上传文件
		{
		   printf("send stor cmd  error\r\n");
		   return ret_error;
		}
   
	if(read_ret("STOR","150" ) < 0)
		{
        
			printf("stor cmd return 150 error\r\n");
            
			return ret_error;
		}
        printf("pic len %d\n",len);
        if(len < 300)
            return re_capture;
        write(data_sockfd, buf, len);  
        close(data_sockfd);
     if(read_ret("STOR","226" ) < 0)
		{
			printf("stor cmd return 226 error\r\n");
			return put_file_faild;
		}  
	return ret_ok;
}

int delete_ftp_file(char *  filename)
{
     if(send_cmd("DELE" ,filename) < 0 )//上传文件
		{
		   printf("send delete cmd  error\r\n");
		   return ret_error;
		}
    memset(sys_info.jpeg_name,0,32);
    if(read_ret("DELE","250" ) < 0)
		{
			printf("delete cmd return error means delete file faild\r\n");
			return delete_file_faild;
		}
    printf("the mqtt push msg faild so delete the ftp jpeg\r\n");
    return ret_ok;
}


//发送命令
int send_cmd(char *cmd ,char *argv)
{
	char cmd_send_buf[Cmd_Buf_Len];
	int ret = 0;
	int buf_len = 0;
	bzero(cmd_send_buf,Cmd_Buf_Len);
	if(argv == NULL)
	sprintf(cmd_send_buf,"%s\r\n",cmd);  
    else
	sprintf(cmd_send_buf,"%s %s\r\n",cmd,argv); 	
	buf_len=strlen(cmd_send_buf);
	ret=write(control_sock, cmd_send_buf, buf_len); 
	if(ret != buf_len)
	{
		return -1;
	}
	else
    {
		return 1;
    }
}
//接收返回值并判断
int read_ret(char *cmd,char * ret_code )
{
	char cmd_read_buf[Cmd_Ret_Len];
	int ret = 0;
	bzero(cmd_read_buf,Cmd_Ret_Len);
	
	ret = read(control_sock, cmd_read_buf, Cmd_Ret_Len);
   
	if(ret == -1)
    {
		return -1;
    }
    else if(strncmp(cmd_read_buf,ret_code,3)==0)
    {
		return 1;
    }
    else 
    {
		return -2;
    }	
}

void get_pic_name (void)
{
    time_t rawtime;
    struct tm *info;
    char buffer[80];
    char jpegname[80];
    char rand_buf[6];
    memset(sys_info.jpeg_name,0,32);
    time( &rawtime );
    info = localtime( &rawtime );
    short  int rand_code= rand()/2;
    sprintf(rand_buf,"%d",rand_code);
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", info);
    strftime(jpegname, 80, "%Y%m%d%H%M%S-", info);
    strncat(jpegname,rand_buf,strlen(rand_buf));
    strncat(jpegname,".jpeg",5);
    memcpy(sys_info.jpeg_name,jpegname,strlen(jpegname));
    memcpy(sys_info.jpeg_time,buffer,strlen(buffer));
}

int ftp_put_file(char * file_buf,int len)
{
      int ret ;
      get_pic_name();
      ret = login();//login success
      if (ret == ret_ok)
      {
          ret = put(file_buf,len) ;
          if(ret != ret_ok)
            return ret;        
      }  
      else 
      {
        return ret; 
      }
      printf("ftp put file success\n");
      return ret_ok;
}
