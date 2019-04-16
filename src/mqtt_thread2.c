
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
//#define ADDRESS     "tcp://m2m.eclipse.org:1883"
//#define ADDRESS     "192.168.3.88:1883"
#define ADDRESS     "193.112.87.125:1883"
#define CLIENTID    "by_smart_cabinet"
#define TOPIC       "INSPECT_TOPIC"
#define PAYLOAD     "by_smart_test !"
#define QOS         1
#define TIMEOUT     100000L
#define USERNAME   "admin"
#define PASSWORD   "admin"
/*
#define ADDRESS     "tcp://m2m.eclipse.org:1883"
#define CLIENTID    "ExampleClientPub123"
#define TOPIC       "MQTT Examples"
#define PAYLOAD     "Hello World! can you see me?"
#define QOS         1
#define TIMEOUT     10000L
*/
char  * json_str=NULL;
cJSON * root;
void pack_to_json(void)
{

   time_t rawtime;
   struct tm *info;
   char buffer[80];
   time( &rawtime );
   info = localtime( &rawtime );
   strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", info);
   
    root =  cJSON_CreateObject();
    cJSON_AddItemToObject(root, "EquipID", cJSON_CreateString(config_info.equip_id));
    cJSON_AddItemToObject(root, "Time", cJSON_CreateString(buffer));
    cJSON_AddItemToObject(root, "Position", cJSON_CreateString(config_info.address_name));
    cJSON_AddItemToObject(root, "sign", cJSON_CreateString("inspect"));
    //cJSON_AddItemToObject(root, "jpeg", cJSON_CreateString(json_jpeg));
    json_str=cJSON_Print(root);
    //printf("%s\n", cJSON_Print(root));
}
int mqtt_thread2(void)
{
    
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;
        /*
        MQTTClient_create(&client, config_info.mqtt_ip, CLIENTID , MQTTCLIENT_PERSISTENCE_NONE, NULL);
        conn_opts.keepAliveInterval = 200;
        conn_opts.cleansession = 1;
        conn_opts.username = USERNAME;
        conn_opts.password = PASSWORD;
        */
while(1)
    {
        if(sem)
        {
            sem = 0;
            MQTTClient_create(&client, config_info.mqtt_ip, CLIENTID , MQTTCLIENT_PERSISTENCE_NONE, NULL);
            conn_opts.keepAliveInterval = 200;
            conn_opts.cleansession = 1;
            conn_opts.username = config_info.mqtt_usr_name;
            conn_opts.password = config_info.mqtt_usr_passwd;
              
            if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
            {
                printf("Failed to connect, return code %d\n", rc);
                exit(EXIT_FAILURE);
            }
            pubmsg.payload = PAYLOAD;
            pubmsg.payloadlen = 160*1024;
            pubmsg.qos = QOS;
            pubmsg.retained = 0;
            
            pack_to_json();
            pubmsg.payload =  json_str;
            pubmsg.payloadlen = (int)strlen(json_str);
            printf("payloadlen is %d\r\n",pubmsg.payloadlen);
            rc=MQTTClient_publishMessage(client, config_info.mqtt_topic, &pubmsg, &token);
            if(rc == 0)
            printf("MQTTClient_publishMessage sucessfully\r\n");
            printf("Waiting for up to %d seconds for publication of %s\n"
                    "on topic %s for client with ClientID: %s\n",
                    (int)(TIMEOUT/1000), PAYLOAD, config_info.mqtt_topic, CLIENTID);
            rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
            if(rc == 0)
            printf("Message with delivery token %d delivered\n", token);
            else
            printf("delivery error return %d\r\n",rc);
            //MQTTClient_unsubscribe(client, TOPIC);
            MQTTClient_disconnect(client, 10000);
        }
        usleep(300000);
    }
   // MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return rc;
}
