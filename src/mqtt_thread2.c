
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
#include "MQTTClient.h"
#include "config.h"
#include "cJSON.h"
#define ADDRESS     "tcp://m2m.eclipse.org:1883"
#define CLIENTID    "ExampleClientPub"
#define TOPIC       "MQTT Examples"
#define PAYLOAD     "Hello World!"
#define QOS         1
#define TIMEOUT     10000L

/*
#define ADDRESS     "tcp://m2m.eclipse.org:1883"
#define CLIENTID    "ExampleClientPub123"
#define TOPIC       "MQTT Examples"
#define PAYLOAD     "Hello World! can you see me?"
#define QOS         1
#define TIMEOUT     10000L
*/
char * json_str;
cJSON * root;
void pack_to_json(void)
{
    root =  cJSON_CreateObject();
    cJSON_AddItemToObject(root, "CardNumber", cJSON_CreateString("10001001"));//根节点下添加
    cJSON_AddItemToObject(root, "Time", cJSON_CreateString("2019-4-8 14:10:50"));
    cJSON_AddItemToObject(root, "Position", cJSON_CreateString("莲花路彩田路路口"));
    cJSON_AddItemToObject(root, "jpeg", cJSON_CreateString(json_jpeg));
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

    MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }
    pubmsg.payload = PAYLOAD;
    pubmsg.payloadlen = (int)strlen(PAYLOAD);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;

    while(1)
    {
        if(sem)
        {
            sem = 0;
           // pubmsg.payload =  json_str;
       
            MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
   
            printf("Waiting for up to %d seconds for publication of %s\n"
                    "on topic %s for client with ClientID: %s\n",
                    (int)(TIMEOUT/1000), PAYLOAD, TOPIC, CLIENTID);
            rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
            printf("Message with delivery token %d delivered\n", token);
          
        }
        usleep(300000);
    }
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return rc;
    
   
    
}
