/*
 * step4_tcpclient.cpp
 *
 *  Created on: 2010-3-29
 *      Author: zhl
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "TCPClientManager.h"

class CTCPClientManager		TCPClntManager;

int main()
{
	int    i1, i2, i3;
	char   ServerIP[20];

	strcpy( ServerIP, "192.168.1.230" );
	//strcpy( ServerIP, "182.151.205.36" );
	//添加一个TCP客户端连接对象
	TCPClntManager.AddTCPClientObject( ServerIP, 5555 );
	//启动TCPClient连接管理操作，并创建TCPClient连接管理线程
	TCPClntManager.Start();

	for( i1=0; i1<TCPClntManager.m_nTCPClientNum; i1++ )
	{
		//设置TCP客户端连接对象为csINIT初始状态，连接管理线程将自动进行TCP的连接操作
		TCPClntManager.Open(i1);
	}

	//for(i1=0; i1<10000; i1++)
	for( ; ; )
	{
		sleep(1);
		for( i2=0; i2<TCPClntManager.m_nTCPClientNum; i2++ )
		{
			// 查询TCP客户端连接状态
			i3 = TCPClntManager.GetTCPClientState(i2);
			printf( "TCP Connect%d State: %d \n", i2+1, i3 );
			if( i3==0 )
			{
				//设置TCP客户端连接对象为csINIT初始状态，连接管理线程将自动进行TCP的连接操作
				TCPClntManager.Open( i2 );
			}
		}
	}
	return 0;
}
