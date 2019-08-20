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
	//���һ��TCP�ͻ������Ӷ���
	TCPClntManager.AddTCPClientObject( ServerIP, 5555 );
	//����TCPClient���ӹ��������������TCPClient���ӹ����߳�
	TCPClntManager.Start();

	for( i1=0; i1<TCPClntManager.m_nTCPClientNum; i1++ )
	{
		//����TCP�ͻ������Ӷ���ΪcsINIT��ʼ״̬�����ӹ����߳̽��Զ�����TCP�����Ӳ���
		TCPClntManager.Open(i1);
	}

	//for(i1=0; i1<10000; i1++)
	for( ; ; )
	{
		sleep(1);
		for( i2=0; i2<TCPClntManager.m_nTCPClientNum; i2++ )
		{
			// ��ѯTCP�ͻ�������״̬
			i3 = TCPClntManager.GetTCPClientState(i2);
			printf( "TCP Connect%d State: %d \n", i2+1, i3 );
			if( i3==0 )
			{
				//����TCP�ͻ������Ӷ���ΪcsINIT��ʼ״̬�����ӹ����߳̽��Զ�����TCP�����Ӳ���
				TCPClntManager.Open( i2 );
			}
		}
	}
	return 0;
}
