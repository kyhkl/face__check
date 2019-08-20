/*
 * step3_tcptest.cpp
 *
 *  Created on: 2010-3-18
 *      Author: zhl
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "TCPServer.h"


class CTCPServer  m_TCPServer;

int main()
{
	int i1;

	printf( "Step3_TCPTest V1.0\n" );

	// 给TCP服务器端口赋值
	m_TCPServer.m_LocalPort = 5555;
	// 创建Socket，启动TCP服务器侦听线程
	i1 = m_TCPServer.Open( );
	if( i1<0 )
	{
		printf( "TCP Server start fail\n");
		return -1;
	}

	// 进入主循环，主要是负责管理工作
	for( i1=0; i1<10000;i1++)
	{
		sleep(1);
		printf( "%d \n", i1+1);
	}
	m_TCPServer.Close( );
	return 0;
}
