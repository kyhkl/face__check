#ifndef _CONFIG_H_
#define _CONFIG_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
//#include <semaphore.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TRUE 1
#define FALSE 0

#define SOCKET_TIME_OUT   100
#define XML_PATH_NAME "/etc/sysconf.xml"
#define ISspace(x) isspace((int)(x)) 
#define USERLEN 33
#define REALMLEN 64
#define QOPLEN   16

// ÏµÍ³ÔËÐÐ×´Ì¬ÐÅÏ¢Êý¾Ý½á¹¹
typedef struct 
{
	char key_event ;//Îª1±íÃ÷°´¼üÊÂ¼þµ½À´
   // char start_capture;
    char play_sounds;
    char capture_faild_times;
    char ftp_faild_times;
    char mqtt_faild_times;
    char read_xml_flag;
    char jpeg_name[32];
    char jpeg_time[32];
    char jpeg[256*1024];
    char json_string[2048];
    int  jpeg_len;
}sys_info_t;
sys_info_t sys_info;


// ÏµÍ³ÅäÖÃÐÅÏ¢Êý¾Ý½á¹¹
typedef struct 
{
	char mqtt_ip[32];
	char mqtt_topic[64];
	char mqtt_usr_name[32];
	char mqtt_usr_passwd[32];
	char camera_ip[32];
	char address_name[64];
    char equip_id[32];
    char ftp_ip[32];
    char ftp_port[6];
    char ftp_user[32];
    char ftp_passwd[32];
    char ftp_path[32];
	
}config_info_t;
config_info_t config_info;

typedef struct {
    char username[USERLEN],password[USERLEN];
    char qop[QOPLEN],realm[QOPLEN],nc[QOPLEN];
    char cnonce[REALMLEN],response[REALMLEN],nonce[REALMLEN];
}httpauth_t;
httpauth_t  auth;

enum ret_code
{
    ret_ok = 0,
    ret_error ,
    camera_connect_faild ,
    camera_capture_faild,
    ftp_connect_faild,
    create_dir_faild,
    change_dir_faild,
    put_file_faild,
    delete_file_faild,
    mqtt_connect_faild,
    mqtt_push_faild,
    re_capture
};

// Í¼Æ¬ÐÅÏ¢Êý¾Ý


void to_hex(char *in,int len,unsigned char *out);
void md5(const uint8_t *initial_msg, size_t initial_len, uint8_t *digest);
int  httpauth_set_auth(httpauth_t *auth,const char* username,const char* password,const char* realm,const char* nonce,const char* nc,const char* cnonce,const char* response,const char* qop);
int  httpauth_get_response(httpauth_t *auth,char *cmd,char *url);
void request(int socket_fd,httpauth_t *auth,int flag);
int  prase_response(char * response_buf ,httpauth_t *auth);
int capture_thread1 (void);
int mqtt_thread2(void);

//登录
int login();
//上传文件
int put(char * buf,int len);
//发送命令
int send_cmd(char *cmd ,char *argv);
//接收返回值并判断
int read_ret(char *cmd,char * ret_code );
//切换目录
int change_dir(char * dirname);
//创建目录
int makedir(char * dirname);

int ftp_put_file(char * file_buf,int len);

int delete_ftp_file(char *  filename);

int connect_timeout(int fd,struct sockaddr_in *addr,unsigned int wait_seconds);
#endif
