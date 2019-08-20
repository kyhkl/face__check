#include <stdio.h>
#include "cJSON.h"
#include "cJSON.h"
int main()
{
    cJSON * root =  cJSON_CreateObject();
    cJSON_AddItemToObject(root, "CardNumber", cJSON_CreateString("10001001"));//根节点下添加
    cJSON_AddItemToObject(root, "Time", cJSON_CreateString("2019-4-8 14:10:50"));
    cJSON_AddItemToObject(root, "Position", cJSON_CreateString("莲花路彩田路路口"));
    cJSON_AddItemToObject(root, "jpeg", cJSON_CreateString("fdagd ojgasdfsamfd"));

    printf("%s\n", cJSON_Print(root));

    return 0;
}
