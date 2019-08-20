// TCPCustom.cpp: implementation of the CTCPCustom class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/un.h>
#include <time.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "TCPCustom.h"
#include "TCPServer.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//���캯��
CTCPCustom::CTCPCustom()
{
   m_SocketEnable = 0;
   m_ExitThreadFlag = 0;
}


//��������
CTCPCustom::~CTCPCustom()
{
   //�ر��߳��˳��¼�
}

/*--------------------------------------------------------------------
���������ܡ�: ���߳����ڼ�����ͻ������ӵ�socketͨѶ���¼������統���յ����ݡ�
			   ���ӶϿ���ͨѶ���̷���������¼�
����ڲ�����: lparam:������ָ�룬����ͨ���˲��������߳��д�����Ҫ�õ�����Դ��
			   ���������ǽ�CTCPCustom��ʵ��ָ�봫����
�����ڲ�����:  (��)
������  ֵ��:   ��
---------------------------------------------------------------------*/
void* CTCPCustom::SocketDataThread(void* lparam)
{
	CTCPCustom *pSocket;
	char		TxBuf[2000];
	int			TxLen;
	//�õ�CTCPCustom��ʵ��ָ��
	pSocket = (CTCPCustom*)lparam;

	//������¼�����
	fd_set fdRead;  
	int ret;
	struct timeval	aTime;
	aTime.tv_sec = 1;
	aTime.tv_usec = 0;

	while( 1 )
	{
        //�յ��˳��¼��������߳�
		if( pSocket->m_ExitThreadFlag )
		{
			break;
		}

		//�ÿն��¼�����
		FD_ZERO(&fdRead);

		//��pSocket���ö��¼�
		FD_SET(pSocket->m_socketfd, &fdRead );
		//����select�������ж��Ƿ��ж��¼�����
		aTime.tv_sec = 1;
		aTime.tv_usec = 0;
		ret = select(0, &fdRead, NULL, NULL, &aTime);
		
		if( ret<0 )
		{
			//�ر�socket
			close( pSocket->m_socketfd );
			break;
		}
		
		else
		{
			//�ж��Ƿ���¼�
			if(FD_ISSET(pSocket->m_socketfd,&fdRead))
			{
				pSocket->RecvLen = recv(pSocket->m_socketfd, pSocket->RecvBuf, 1024,0);
				if (pSocket->RecvLen < 0 )
				{
					//��ͻ��˶����ӵ�Socket����
					printf( "Socket error\n");
					//�ر�socket
					close(pSocket->m_socketfd);
					break;

				}
				//��ʾ�����Ѿ����ݹر�
				else if( pSocket->RecvLen == 0)
				{
					printf( "Close socket %d\n", pSocket->m_socketfd );
					//�ر�socket
					close(pSocket->m_socketfd);
					break;
				}
				else
				{
					//�Խ��յ����ݽ��д���������Ϊ�򵥴������ݻط�
					pSocket->RecvBuf[pSocket->RecvLen]=0;
					printf( "RCV:%s\n", pSocket->RecvBuf);
					TxLen = pSocket->DataPro( TxBuf );
					if( TxLen>0 )
					{
						pSocket->SendData( TxBuf, TxLen );
					}
					//�������
				}
			}
		}
	}

	printf( "SocketDataThread finished\n");
	pthread_exit( NULL );
	//�ͷ�TCPCustomָ��
	pSocket->m_pTCPServer->RemoveClientSocketObject( (void*)pSocket );
}


int CTCPCustom::DataPro( char* OutDatBuf )
{
	int         len=0;
	time_t      t;
	struct tm   *p;
	char        str[80];

	if( RecvLen<=0 )
		return 0;

	switch( RecvBuf[0] )
	{
	case 0x10:     //����ϵͳʱ��
		sprintf(str, "date -s %s", &RecvBuf[1] );
		system( str );
		system( "hwclock --systohc");
		time( &t );
		p = localtime ( &t );
		sprintf( OutDatBuf, "date %d.%d.%d-%d:%d:%d\n", p->tm_year + 1900, p->tm_mon+1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec );
		len = strlen( OutDatBuf );
		break;
	case 0x11:     //��ȡϵͳʱ��
		time( &t );
		p = localtime ( &t );
		sprintf( OutDatBuf, "date %d.%d.%d-%d:%d:%d\n", p->tm_year + 1900, p->tm_mon+1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec );
		len = strlen( OutDatBuf );
		break;
	default:
		memcpy( OutDatBuf, RecvBuf, RecvLen );
		len = RecvLen;
		break;
	}
	return len;
}



/*--------------------------------------------------------------------
���������ܡ�: ��socket������ͨѶ�߳�
����ڲ�����:  pTCPServerָ��������˼���socket
�����ڲ�����:  (��)
������  ֵ��:  1:�򿪳ɹ�;0:��ʧ��
---------------------------------------------------------------------*/
int CTCPCustom::Open(void* lparam)
{
	int					res, flags;
	pthread_attr_t 		attr;

	m_pTCPServer = (CTCPServer*)lparam;

	//����ͨѶ�߳�, ��������������ָ������߳�
	res = pthread_attr_init(&attr);
	if( res!=0 )
	{
		printf("Create attribute failed\n" );
	}
	// �����̰߳�����
	res = pthread_attr_setscope( &attr, PTHREAD_SCOPE_SYSTEM );
	// �����̷߳�������
	res += pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED );
	if( res!=0 )
	{
		printf( "Setting attribute failed\n" );
	}

	res = pthread_create( &m_thread, &attr, SocketDataThread, this );
	if( res!=0 )
	{
		close( m_socketfd );
		return 0;
	}
	pthread_attr_destroy( &attr );


	//����ͨѶģʽΪ�첽ģʽ
	flags = fcntl(m_socketfd, F_GETFL);
	if( (flags<0)||((fcntl(m_socketfd, F_SETFL, flags |O_ASYNC))<0) )
	{
		perror("fcntl");
	}

	m_SocketEnable = 1;
	return 1;
}

/*--------------------------------------------------------------------
���������ܡ�: �ر�socket���ر��̣߳��ͷ�Socket��Դ
����ڲ�����:  (��)
�����ڲ�����:  (��)
������  ֵ��:  1:�ɹ��ر�;0:�ر�ʧ��
---------------------------------------------------------------------*/
int CTCPCustom::Close()
{
	m_ExitThreadFlag = 1;

   //�ر�Socket���ͷ���Դ
   int err = close(m_socketfd);
   if( err<0 )
   {
	   return 0;
   }
   return 1;
}


/*-----------------------------------------------------------------
���������ܡ�: ��ͻ��˷�������
����ڲ�����: buf: �����͵�����
              len: �����͵����ݳ���
�����ڲ�����: (��)
������  ֵ��: >0: �������ݳɹ�, ���������͵����ݳ���; 
              <0: ��������ʧ�ܡ�
------------------------------------------------------------------*/
int CTCPCustom::SendData( const char *buf , int len )
{
	int nBytes = 0;
	int nSendBytes=0;

	while(nSendBytes < len)
	{
	    nBytes = send(m_socketfd,buf+nSendBytes,len-nSendBytes,0);
		if (nBytes<0 )
		{
			return nBytes;
		}

		nSendBytes = nSendBytes + nBytes;
		
		if (nSendBytes < len)
		{
		    sleep(1);
		}
	} 
	return nSendBytes; 
}