#include <stdio.h>
#include "cJSON.h"

int main()
{
    cJSON * root =  cJSON_CreateObject();
   // cJSON * item =  cJSON_CreateObject();
    //cJSON * next =  cJSON_CreateObject();
    char buf[384*1024]="hello world";
    
    
    cJSON_AddItemToObject(root, "CardNumber", cJSON_CreateString("10001001"));//根节点下添加
    cJSON_AddItemToObject(root, "Time", cJSON_CreateString("2019-4-8 14:10:50"));
    cJSON_AddItemToObject(root, "Position", cJSON_CreateString("莲花路彩田路路口"));
    cJSON_AddItemToObject(root, "jpeg", cJSON_CreateString(buf));
    //cJSON_AddItemToObject(root, "semantic", item);//root节点下添加semantic节点
    //cJSON_AddItemToObject(item, "slots", next);//semantic节点下添加item节点
    //cJSON_AddItemToObject(next, "name", cJSON_CreateString("张三"));//添加name节点

    printf("%s\n", cJSON_Print(root));

    return 0;
}
