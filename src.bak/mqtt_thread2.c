
/*******************************************************************************
 * Copyright (c) 2012, 2017 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution. 
 *
 * The Eclipse Public License is available at 
 *   http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at 
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Ian Craggs - initial contribution
 *******************************************************************************/
#include <time.h>
#include "MQTTClient.h"
#include "config.h"
#include "cJSON.h"

//#define ADDRESS     "193.112.87.125:1883"
#define CLIENTID    "by_smart_cabinet"
//#define TOPIC       "INSPECT_TOPIC"
#define PAYLOAD     "by_smart_cabinet !"
#define QOS         1
#define TIMEOUT     100000L

char  * json_str=NULL;
cJSON * root;
void pack_to_json(void)
{
    root =  cJSON_CreateObject();
    cJSON_AddItemToObject(root, "EquipID", cJSON_CreateString(config_info.equip_id));
    cJSON_AddItemToObject(root, "Time", cJSON_CreateString(sys_info.jpeg_time));
    cJSON_AddItemToObject(root, "Position", cJSON_CreateString(config_info.address_name));
    cJSON_AddItemToObject(root, "Jpeg_Name", cJSON_CreateString(sys_info.jpeg_name));
    cJSON_AddItemToObject(root, "sign", cJSON_CreateString("inspect"));
    json_str=cJSON_Print(root);
   
}
int mqtt_push(void)
{
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    MQTTClient_create(&client, config_info.mqtt_ip, CLIENTID , MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 200;
    conn_opts.cleansession = 1;
    conn_opts.username = config_info.mqtt_usr_name;
    conn_opts.password = config_info.mqtt_usr_passwd;
      
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        return mqtt_connect_faild;
    }
    pubmsg.payload = PAYLOAD;
    pubmsg.payloadlen = 160*1024;
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    pack_to_json();
    pubmsg.payload =  json_str;
    pubmsg.payloadlen = (int)strlen(json_str);
    rc=MQTTClient_publishMessage(client, config_info.mqtt_topic, &pubmsg, &token);
    if(rc != 0)
     {
         printf("MQTTClient_publishMessage falid\r\n");
         return mqtt_push_faild;
     }
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    if(rc != 0)
    {
        printf("MQTTClient_publishMessage falid\r\n");
        return mqtt_push_faild;
    }
    printf("mqtt push msg success\n");
    memset(sys_info.jpeg_name,0,32);
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
     
    return ret_ok;
}