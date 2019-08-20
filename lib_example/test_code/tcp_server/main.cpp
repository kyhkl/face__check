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

	// ��TCP�������˿ڸ�ֵ
	m_TCPServer.m_LocalPort = 5555;
	// ����Socket������TCP�����������߳�
	i1 = m_TCPServer.Open( );
	if( i1<0 )
	{
		printf( "TCP Server start fail\n");
		return -1;
	}

	// ������ѭ������Ҫ�Ǹ��������
	for( i1=0; i1<10000;i1++)
	{
		sleep(1);
		printf( "%d \n", i1+1);
	}
	m_TCPServer.Close( );
	return 0;
}
