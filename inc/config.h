#ifndef _CONFIG_H_
#define _CONFIG_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define ISspace(x) isspace((int)(x)) 
#define USERLEN 33
#define REALMLEN 64
#define QOPLEN   16
// 系统配置信息数据结构
typedef struct 
{
	char mqtt_ip[32];
	char mqtt_topic[64];
	char mqtt_usr_name[32];
	char mqtt_usr_passwd[32];
	char camera_ip[32];
	char address_name[64];
	
}config_info_t;
config_info_t config_info;
// 系统运行状态信息数据结构
typedef struct 
{
	char key_event ;//为1表明按键事件到来
	char get_picture ;//为1表明取到图片数据
	char pack_over;//为1 表明打包完成
	char send_over;//为1 表明发送完成

}sys_info_t;
sys_info_t sys_info;

typedef struct {
    char username[USERLEN],password[USERLEN];
    char qop[QOPLEN],realm[QOPLEN],nc[QOPLEN];
    char cnonce[REALMLEN],response[REALMLEN],nonce[REALMLEN];
}httpauth_t;

httpauth_t  auth;


// 图片信息数据
char jpeg[512*1024];

void to_hex(char *in,int len,unsigned char *out);
void md5(const uint8_t *initial_msg, size_t initial_len, uint8_t *digest);
int  httpauth_set_auth(httpauth_t *auth,const char* username,const char* password,const char* realm,const char* nonce,const char* nc,const char* cnonce,const char* response,const char* qop);
int  httpauth_get_response(httpauth_t *auth,char *cmd,char *url);
void request(int socket_fd,httpauth_t *auth,int flag);
int  prase_response(char * response_buf ,httpauth_t *auth);

#endif
