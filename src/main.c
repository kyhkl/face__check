
#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>
#include "config.h"
#include "mxml.h"
/*
 key_enent-->capture-->fpt put file-->mqtt push msg 
 */
char * url ="/ISAPI/Streaming/channels/101/picture" ;//抓图连接
char * cmd = "GET";//抓图方式
const char * username_t ="admin";
const char * passworld_t ="byjt1234";
const char * realm_t ="DS-2CD2520F";
const char * nonce_t ="4d6a46444d7a5a464e3045364e5449355a546c695932553d";
const char * nc_t ="00000001";
const char * cnonce_t ="8887920ea7e5c1c8";
const char * response_t ="5a9aa58fb654e667ad9d8e8adaa336df";
const char * qop_t ="auth";
const char * base64char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static unsigned int key_event = 0;
FILE *fp = NULL;
int sock_sd;
typedef struct input_event INPUT_EVENT;
#define KEY_DEVICE_NAME "/dev/input/event1"

// bindata待编码数据buffer  base64 编码后数据buffer  binlength 待编码数据大小
char *base64_encode( const unsigned char * bindata, char * base64, int binlength )
{
    int i, j;
    unsigned char current;
 
    for ( i = 0, j = 0 ; i < binlength ; i += 3 )
    {
        current = (bindata[i] >> 2) ;
        current &= (unsigned char)0x3F;
        base64[j++] = base64char[(int)current];
 
        current = ( (unsigned char)(bindata[i] << 4 ) ) & ( (unsigned char)0x30 ) ;
        if ( i + 1 >= binlength )
        {
            base64[j++] = base64char[(int)current];
            base64[j++] = '=';
            base64[j++] = '=';
            break;
        }
        current |= ( (unsigned char)(bindata[i+1] >> 4) ) & ( (unsigned char) 0x0F );
        base64[j++] = base64char[(int)current];
 
        current = ( (unsigned char)(bindata[i+1] << 2) ) & ( (unsigned char)0x3C ) ;
        if ( i + 2 >= binlength )
        {
            base64[j++] = base64char[(int)current];
            base64[j++] = '=';
            break;
        }
        current |= ( (unsigned char)(bindata[i+2] >> 6) ) & ( (unsigned char) 0x03 );
        base64[j++] = base64char[(int)current];
 
        current = ( (unsigned char)bindata[i+2] ) & ( (unsigned char)0x3F ) ;
        base64[j++] = base64char[(int)current];
    }
    base64[j] = '\0';
    return 0;
}
 // base64编码字符串 bindata 解码后buffer
int base64_decode( const char * base64, unsigned char * bindata )
{
    int i, j;
    unsigned char k;
    unsigned char temp[4];
    for ( i = 0, j = 0; base64[i] != '\0' ; i += 4 )
    {
        memset( temp, 0xFF, sizeof(temp) );
        for ( k = 0 ; k < 64 ; k ++ )
        {
            if ( base64char[k] == base64[i] )
                temp[0]= k;
        }
        for ( k = 0 ; k < 64 ; k ++ )
        {
            if ( base64char[k] == base64[i+1] )
                temp[1]= k;
        }
        for ( k = 0 ; k < 64 ; k ++ )
        {
            if ( base64char[k] == base64[i+2] )
                temp[2]= k;
        }
        for ( k = 0 ; k < 64 ; k ++ )
        {
            if ( base64char[k] == base64[i+3] )
                temp[3]= k;
        }
 
        bindata[j++] = ((unsigned char)(((unsigned char)(temp[0] << 2))&0xFC)) |
                ((unsigned char)((unsigned char)(temp[1]>>4)&0x03));
        if ( base64[i+2] == '=' )
            break;
 
        bindata[j++] = ((unsigned char)(((unsigned char)(temp[1] << 4))&0xF0)) |
                ((unsigned char)((unsigned char)(temp[2]>>2)&0x0F));
        if ( base64[i+3] == '=' )
            break;
 
        bindata[j++] = ((unsigned char)(((unsigned char)(temp[2] << 6))&0xF0)) |
                ((unsigned char)(temp[3]&0x3F));
    }
    return j;
}

void printf_ret_msg(int ret)
{
    switch (ret)
    {
    case ret_error :               printf("ret_error\n");break;   
    case camera_connect_faild :    printf("camera_connect_faild\n");break;
    case ftp_connect_faild:        printf("ftp_connect_faild\n");break;
    case create_dir_faild:         printf("create_dir_faild\n");break;
    case change_dir_faild:         printf("change_dir_faild\n");break;
    case put_file_faild:           printf("put_file_faild\n");break;
    case delete_file_faild:        printf("delete_file_faild\n");break;
    case mqtt_connect_faild:       printf("mqtt_connect_faild\n");break;
    case mqtt_push_faild:          printf("mqtt_push_faild\n");break;
    case re_capture:               key_event = 1;break;
    }
}

int  connet_camera(const char * ip)//与摄像头建立socket 连接
{	
     
    int ret;
    struct sockaddr_in ser_sockaddr;
    

    //返回套接字描述符
    sock_sd = socket(AF_INET, SOCK_STREAM, 0); //创建socket连接 选择IPV4的TCP协议数据包
    if(sock_sd==-1)
        printf("TCP套接字创建失败\r\n");
   //设置sockaddr_in结构体中相关参数
    ser_sockaddr.sin_family =  AF_INET;          //地址族 IPV4
    ser_sockaddr.sin_port   =  htons(80);  //设置为要连接的服务器的端口号(short数据转化为网络数据)
    ser_sockaddr.sin_addr.s_addr  = inet_addr(config_info.camera_ip); //设置服务器的IP地址(字符串转化为整形)
    
   /*连接到服务器*/
    ret=connect_timeout(sock_sd,(struct sockaddr*)&ser_sockaddr,5);
    if(ret==-1 && errno ==ETIMEDOUT)
    {
        printf("camrea connect timedout\n");
        return  camera_connect_faild;
    }
    else if(ret==-1)
    {
        printf("inner net connect error\n");
         return  camera_connect_faild;
    }
    return ret_ok;
}

int first_request(httpauth_t * auth ,char * rcv_buf )//第一次请求发送带header或者不带header都行
{			
    int ret = 0;
    ret = connet_camera(config_info.camera_ip);
    if(ret != ret_ok)
     {
        return ret;
     }
    httpauth_set_auth(auth,username_t,passworld_t,realm_t,nonce_t,nc_t,cnonce_t,response_t,qop_t);
    request(sock_sd,auth,0);
    ret = recv(sock_sd,rcv_buf,1024,0);
    if(ret < 0)
      {
        return camera_capture_faild;
      }
    else  
        return prase_response(rcv_buf,auth);
}

int second_request(httpauth_t* auth, char* rcv_buf, int len)//第二次请求发送带header
{
    int rs = 1;
    int ret = 0 ;
    int buflen = 0;
    int rev_pos = 0;
    int jpeg_len;
    char *begin=NULL;
    ret = connet_camera(config_info.camera_ip);
    if(ret != ret_ok)
     {
        printf_ret_msg(ret);
        return ret;
     }
    httpauth_get_response(auth,cmd,url);
    request(sock_sd,auth,1);
    while(rs)
            {
                buflen = recv(sock_sd, &rcv_buf[rev_pos],len - rev_pos , 0);
                
                if(buflen < 0)
                {
                    // 由于是非阻塞的模式,所以当buflen为EAGAIN时,表示当前缓冲区已无数据可读
                    // 在这里就当作是该次事件已处理
                    if(errno == EINTR)
                        continue;
                    else
                        break;
                }
                else if(buflen == 0)
                {
                    // 这里表示对端的socket已正常关闭.
                    
                     begin = strstr(rcv_buf,"Content-Length:");
                     jpeg_len = atoi(begin+15);
                     begin = strstr(rcv_buf,"\r\n\r\n");
                     //fp = fopen(jpeg_name, "w+");
                     //fwrite(begin+4,jpeg_len,1, fp);
                     //fclose(fp);
                     memcpy(sys_info.jpeg,begin+4,jpeg_len);
                     // bindata待编码数据buffer  base64 编码后数据buffer  binlength 待编码数据大小
                     // base64_encode( jpeg, json_jpeg, jpeg_len);
                     printf("capture picture success\nthe picture size is %d\r\n",jpeg_len);
                     sys_info.jpeg_len=jpeg_len;
                    //memset(jpeg,0,sizeof(jpeg));
                    //base64编码字符串 bindata 解码后buffer
                    //base64_decode( json_jpeg, jpeg );                            
                    //fp = fopen("again.jpeg", "w+");
                    //fwrite(jpeg,jpeg_len,1, fp);
                    //fclose(fp);
                  
                    return ret_ok;
                }

                if(buflen != sizeof(rcv_buf))
                    rs = 1;
                else
                    rs = 0;
                // 需要再次读取
                rev_pos += buflen;
            }
            
        return camera_capture_faild;			
}


//void* capture_thread1 (void *arg)
int capture_pic (void )
{
    int ret ;
    char rcv_buf[256*1024];
	ret = first_request(&auth , rcv_buf);
	if(ret == ret_ok)
	{	
		memset(rcv_buf,0,sizeof(rcv_buf));//收到401 相应 发送第二次请求
		return second_request(&auth, rcv_buf, sizeof(rcv_buf));
	}
	else 
	{
        return ret;
	}
    
}


void  read_xml(char * pathname)
{
    FILE* fp = fopen(pathname,"r");
    if(fp == NULL)
    {
     printf("open sysconfig.xml falid\r\n");
     exit(0);
    } 
    // read xml
    mxml_node_t* xml = mxmlLoadFile(NULL,fp,MXML_NO_CALLBACK);
    mxml_node_t* xml_t = NULL;
    mxml_node_t* mqtt_ip = NULL;
    mxml_node_t* mqtt_topic = NULL;
    mxml_node_t* mqtt_usr_name = NULL;
    mxml_node_t* mqtt_usr_passwd = NULL;
    mxml_node_t* camera_ip = NULL;
    mxml_node_t* address_name = NULL;
    mxml_node_t* equip_id = NULL;
    char* ftp_ip  = NULL;
    char* ftp_port  = NULL;
    char* ftp_user  = NULL;
    char* ftp_passwd  = NULL;
    char* ftp_path  = NULL;    
    //mqtt 
    xml_t = mxmlFindElement(xml,xml,"face_check",NULL,NULL,MXML_DESCEND);
    mqtt_ip = mxmlFindElement(xml_t,xml,"mqtt_ip",NULL,NULL,MXML_DESCEND);
    mqtt_topic = mxmlFindElement(xml_t,xml,"mqtt_topic",NULL,NULL,MXML_DESCEND);
    mqtt_usr_name = mxmlFindElement(xml_t,xml,"mqtt_usr_name",NULL,NULL,MXML_DESCEND);
    mqtt_usr_passwd = mxmlFindElement(xml_t,xml,"mqtt_usr_passwd",NULL,NULL,MXML_DESCEND);
    camera_ip = mxmlFindElement(xml_t,xml,"camera_ip",NULL,NULL,MXML_DESCEND);
    //equipment info
    xml_t  = mxmlFindElement(xml,xml,"equipment",NULL,NULL,MXML_DESCEND);
    equip_id  = mxmlFindElement(xml_t,xml,"EquipID",NULL,NULL,MXML_DESCEND);
    address_name = mxmlFindElement(xml_t,xml,"EquipName",NULL,NULL,MXML_DESCEND);
    //ftp
    xml_t  = mxmlFindElement(xml,xml,"ftp",NULL,NULL,MXML_DESCEND);
    ftp_ip  = mxmlElementGetAttr(xml_t,"server_ip");
    ftp_port = mxmlElementGetAttr(xml_t,"port");
    ftp_user = mxmlElementGetAttr(xml_t,"user");
    ftp_passwd =mxmlElementGetAttr(xml_t,"password");
    ftp_path =mxmlElementGetAttr(xml_t,"savepath");

    memcpy(config_info.address_name,mxmlGetText(address_name,NULL),sizeof(config_info.address_name));
    memcpy(config_info.equip_id,mxmlGetText(equip_id,NULL),sizeof(config_info.equip_id));
    memcpy(config_info.camera_ip,mxmlGetText(camera_ip,NULL),sizeof(config_info.camera_ip));
    memcpy(config_info.mqtt_ip,mxmlGetText(mqtt_ip,NULL),sizeof(config_info.mqtt_ip));
    memcpy(config_info.mqtt_topic,mxmlGetText(mqtt_topic,NULL),sizeof(config_info.mqtt_topic));
    memcpy(config_info.mqtt_usr_name,mxmlGetText(mqtt_usr_name,NULL),sizeof(config_info.mqtt_usr_name));
    memcpy(config_info.mqtt_usr_passwd,mxmlGetText(mqtt_usr_passwd,NULL),sizeof(config_info.mqtt_usr_passwd));
   
    memcpy(config_info.ftp_ip,ftp_ip,strlen(ftp_ip));
    memcpy(config_info.ftp_port,ftp_port,strlen(ftp_port));
    memcpy(config_info.ftp_user,ftp_user,strlen(ftp_user));
    memcpy(config_info.ftp_passwd,ftp_passwd,strlen(ftp_passwd));
    memcpy(config_info.ftp_path,ftp_path,strlen(ftp_path));
/*
    printf("%s\n",config_info.ftp_ip);
    printf("%s\n",config_info.ftp_port);
    printf("%s\n",config_info.ftp_user);
    printf("%s\n",config_info.ftp_passwd);
    printf("%s\n",config_info.ftp_path);
    * */
    mxmlDelete(xml);
    fclose(fp);
}

int key_read(int fd)
{
    int num;
	INPUT_EVENT event;  
    num = read(fd, &event, sizeof(INPUT_EVENT));
    
    if (sizeof(INPUT_EVENT) != num)
		{
			printf("read key error\n");
			return 0;
		}
    if (event.type == EV_KEY)
		{	
			// keybutton status
			if ((!event.value) && (event.code == 102))
                {
                   return 1 ;
                }
                else
                   return 0;
		}   
    else 
         return 0 ;
}

int key_thread(void)
{
    int fd; 
    fd = open( KEY_DEVICE_NAME , O_RDONLY, 0);				
	if (fd < 0)
	{
		perror("Can't open button device...\n");
		exit(0);
	}  
 
    while(1)
    {
        if (key_read(fd) == 1)
        { 
            key_event = 1; 
            sys_info.play_sounds = 1;
            if(sys_info.read_xml_flag == 1)
            {   
                sys_info.read_xml_flag = 0 ;
                read_xml(XML_PATH_NAME);
            }
        }   
    }  
}


int capture_thread (void)
{
	int ret=2;
    //read the configure file
    sys_info.read_xml_flag = 1;
    //sys_info.start_capture = 1;
    //open the key device 
	while(1)
	{
        //if((key_event == 1)||(sys_info.start_capture == 1))
        if(key_event == 1)
        {
            if (sys_info.play_sounds == 1)
            {
                system("madplay 1.mp3"); 
                sys_info.play_sounds =0;
            }
            /*
            if (sys_info.start_capture == 1)
            {
                key_event  = 1;
                sys_info.start_capture = 0;
                read_xml(XML_PATH_NAME);
            }
            * */
            
           ret = capture_pic();
           
           if (ret == ret_ok)//capture success
           {
                ret = ftp_put_file(sys_info.jpeg,sys_info.jpeg_len);
                if(ret == ret_ok)//ftp  put file success
                {
                       ret = mqtt_push(); 
                       
                       if(ret != ret_ok)//mqtt push msg success
                       {
                            printf_ret_msg(ret);
                            //if mqtt push faild ,then delete the ftp file from the ftp service
                            delete_ftp_file(sys_info.jpeg_name);
                            
                        if(sys_info.mqtt_faild_times++>2)
                           {
                            sys_info.mqtt_faild_times=0;
                            key_event = 0;
                            sys_info.read_xml_flag = 1 ;
                            system("madplay 3.mp3");
                          
                           }
                            continue;  
                       }
                       
                       system("madplay 2.mp3");
                       
                       usleep(20000);
                }
                else
                {
                   printf_ret_msg(ret);
                   
                   if (sys_info.ftp_faild_times++ > 2)
                   {
                    sys_info.ftp_faild_times = 0 ;
                    key_event = 0;
                    sys_info.read_xml_flag = 1;
                    system("madplay 3.mp3");
                   }
                    continue;   
                }
           }
           else
           {
               printf_ret_msg(ret);
                
               if(sys_info.capture_faild_times++>2)
               {
                sys_info.capture_faild_times=0;
                key_event = 0;
                sys_info.read_xml_flag = 1 ;
                system("madplay 3.mp3");
               }
               continue; 
           }
        }
 
         key_event = 0;
         usleep(50000);
	}
}

int main(int argc , char * argv[])
{
    pthread_t tid1,tid2; 
    int ret;
    int test = 10;
    srand( (unsigned)time( NULL ) );  
     
    ret = pthread_create(&tid1, NULL, capture_thread, (void *)&test);//线程创建函数
    if(ret)  //主线程
    {
        perror("pthread create error");
        return -1;
    }  
    
    ret = pthread_create(&tid2, NULL, key_thread, (void *)&test);//线程创建函数
    if(ret)  //主线程
    {
        perror("pthread create error");
        return -1;
    }  
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
}
