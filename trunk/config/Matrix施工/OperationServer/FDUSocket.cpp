#include "StdAfx.h"
#include "OperationServer.h"
#include "FDUSocket.h"
/**
 * @brief CSocketFDU���캯��
 */
CSocketFDU::CSocketFDU(void)
: m_FDUSocket(0)
{
	memset(m_pBuf,0xAA,16);
	m_pBuf[0]=0x11;
	m_pBuf[1]=0x22;
	m_pBuf[2]=0x33;
	m_pBuf[3]=0x44;
}
/**
 * @brief CSocketFDU��������
 */
CSocketFDU::~CSocketFDU(void)
{
}

/**
 * @brief ������ɼ�վͨ�ŵ�socket
 * @note  ������ɼ�վͨ�ŵ�Socket
 * @param  DWORD dwLocalIP������IP
 * @param  WORD  wLocalPort�������˿�
 * @param  DWORD dwMainCrossIP��������վIP
 * @param  WORD wMainCrossPort��������վ�˿�
 * @return �ɹ��򷵻�true����֮�򷵻�false��
 */
bool CSocketFDU::CreateSocket(DWORD dwLocalIP,WORD wLocalPort)
{
	if(m_FDUSocket)
		return false;
	m_dwLocalIP = dwLocalIP;
	m_wLocalPort = wLocalPort;
	//m_dwMainCrossIP=dwMainCrossIP;
	//m_wMainCrossPort = wMainCrossPort;

	m_FDUSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_FDUSocket == INVALID_SOCKET) 
	{
		return false;
	}
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = m_dwLocalIP;
	service.sin_port = htons(m_wLocalPort);

	if (bind( m_FDUSocket, (SOCKADDR*) &service,sizeof(service)) == SOCKET_ERROR)
	{
		closesocket(m_FDUSocket);
		m_FDUSocket = NULL;
		return false;
	}
	// ���ý��ջ�������С
	int RevBuf = 2048*1024;
	if (setsockopt(m_FDUSocket, SOL_SOCKET, SO_RCVBUF, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		closesocket(m_FDUSocket);
		m_FDUSocket = NULL;
		return false;
	}
	// ���÷��ͻ�������С
	if (setsockopt(m_FDUSocket, SOL_SOCKET, SO_SNDBUF, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		closesocket(m_FDUSocket);
		m_FDUSocket = NULL;
		return false;
	}
	// ����������ܹ㲥��Ϣ
	RevBuf = 1;
	if (setsockopt(m_FDUSocket, SOL_SOCKET, SO_BROADCAST, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		closesocket(m_FDUSocket);
		m_FDUSocket = NULL;
		return false;
	}
	return true;

}

/**
 * @brief �ر�socket
 * @note  �ر���ɼ�վͨ�ŵ�Socket
 * @param  void
 * @return �ɹ��򷵻�true����֮�򷵻�false��
 */
bool CSocketFDU::CloseSocket(void)
{
	if(m_FDUSocket)
	{
		closesocket(m_FDUSocket);
		m_FDUSocket = NULL;
	}
	return true;

}
/**
 * @brief ��ս��ջ�����
 * @note  ������ɼ�վͨ�ŵ�Socket���������ɼ�վ�������·���ָ��Զ��ظ������ڲ���Ҫ����Ļظ���
 ���øú�������ս��ջ�����
 * @param  void
 * @return �ɹ��򷵻�true����֮�򷵻�false��
 */
bool CSocketFDU::ClearRevBufOfSocket()
{
	char  byBuf[256];
	if(m_FDUSocket==NULL)
		return false;
// 	fd_set    readfs;
// 	timeval  timeout;
// 	timeout.tv_sec = 0;
// 	timeout.tv_usec =0;		// �ȴ���ʱ��300ms

	ULONG	dwRevBufSize;
	// ���ջ�����
	while(1)
	{
// 		readfs.fd_count =1;
// 	//	FD_SET(readfs,&m_FDUSocket);
// 		readfs.fd_array[0]=m_FDUSocket;
		// �жϽ��ջ������Ƿ�������
		if(ioctlsocket(m_FDUSocket,FIONREAD,&dwRevBufSize))
		{
			return true;
		}
		if(dwRevBufSize==0)
			return true;	
		// ��������
		if(recvfrom(m_FDUSocket, byBuf, 256, 0,NULL,NULL)<=0)
			return true;		
	}
	return true;

}

/**
 * @brief ���������ݰ��������ɼ�վIP
 * @note  ���������ݰ�֡��ʽ�н������ɼ�վ��IP��ַ���ɼ�վIP��ַλ��֡��ʽ�й̶���λ�á�
 * @param  pBuf������ָ�룬ָ��������ݰ��������׵�ַ����Ӧ֡��ʽ��ͬ����λ��
 * @param  nSize�����ݻ������Ĵ�С 
 * @return �ɹ�IP��ַ��
 */
DWORD  CSocketFDU::GetFDUIPFromUplinkPack(unsigned char* pBuf,int  nSize)
{
	DWORD  dwIP=0;
	if(nSize<19)
		return 0;
	memcpy_s(&dwIP,4,pBuf+16,4);
	return dwIP;
}
/**
 * @brief ��ɼ�վ��������
 * @note  �����ķ��ͺ�������Ҫ��װIP��ַ�Ͷ˿ڵ�ת����
 * @param  pBuf���������ݻ�����ָ��
 * @param  nSize�����ݻ������Ĵ�С 
 * @return �����ѷ��͵��ֽ���
 */
int  CSocketFDU::SendToFDU(unsigned char* pBuf,int nSize)
{
	sockaddr_in MainCrsAddr;
	MainCrsAddr.sin_family = AF_INET;
	MainCrsAddr.sin_port = htons(theApp.m_wMainCrossPort);
	MainCrsAddr.sin_addr.s_addr = theApp.m_dwMainCrossIP;
	return sendto(m_FDUSocket,(char*)pBuf,nSize,0,(sockaddr*)&MainCrsAddr,sizeof(sockaddr_in));	

}

/**
 * @brief ��ɼ�վ���������ش�ָ��
 * @note  �򵥸��ɼ�վ���������ش�ָ�
 * @param DWORD dwFDUIP����Ҫ�ش��Ĳɼ�վIP��ַ 
 * @param WORD wHostPort�������ش����ݵ������˿� 
 * @param WORD wFrmIndex����Ҫ�ش���AD�����������ɼ�վ����2KByte�Ļ�������ÿ֡��74*24Byte�����ݡ�
 * @return �����ѷ��͵��ֽ���
 */
int CSocketFDU::SendRetranCmdToFDU(DWORD dwFDUIP, WORD wHostPort, WORD wFrmIndex)
{
	unsigned char*   pBuf = m_pBuf;	
	memcpy_s(pBuf+16,4,&m_dwLocalIP,sizeof(DWORD));
	memcpy_s(pBuf+20,4,&dwFDUIP,sizeof(DWORD));
	memcpy_s(pBuf+24,2,&wHostPort,sizeof(WORD));
	// ���ݲ�ѯ����
	pBuf[26]=0x03;
	pBuf[27]=0;
	// ��ʱ��
	memset(pBuf+28,0,4);
	// AD����ָ��
	memcpy_s(pBuf+32,2,&wFrmIndex,sizeof(WORD));
	return SendToFDU(pBuf,128);
}
/**
 * @brief ��ɼ�վ������������
 * @note  ��ɼ�վ������������,��Ϊ����������õ��������������
 * @note  ����ȴ��˿ں�����,������Ϊ0x0A�������ʽΪ16bits�˿�+16bits���
				16λ�˿�Ϊ������λ���㲥����Ķ˿ڣ���λ��ǰ����λ�ں�
				16λ������Ĭ��Ϊ0x0003,˳��Ϊ03 00��
 * @note  ����������������,������Ϊ0x3d��
 * @note  �˲�����������,������Ϊ0x17,0x18�� 
 * @param  DWORD dwFDUIP, �ɼ�վIP��ַ
 * @param  WORD wBroadcastPort,����վ�����㲥����Ķ˿�
 * @param  DWORD dwConfig, ������������
 * @param  DWORD dwFilter17, �˲���
 * @param  DWORD dwFilter18, �˲���
 * @return �ɹ�����true��ʧ���򷵻�false��
 */
int CSocketFDU::SendConfigCmdToFDU(DWORD dwFDUIP,WORD wBroadcastPort,DWORD dwConfig,DWORD dwFilter17,DWORD dwFilter18)
{
	BYTE* pBuf = m_pBuf;
	int		nIndex;

	memcpy_s(pBuf+16,4,&m_dwLocalIP,sizeof(DWORD));
	memcpy_s(pBuf+20,4,&dwFDUIP,sizeof(DWORD));
	memcpy_s(pBuf+24,2,&m_wLocalPort,sizeof(WORD));
	pBuf[26]=0x01;
	pBuf[27]=0;		// ��������

	pBuf[32]=0x0A;  // �����룺 ����ȴ��˿ں�����
	pBuf[33]=LOBYTE(m_wLocalPort);
	pBuf[34]=HIBYTE(m_wLocalPort);
	pBuf[35]=0x03;
	pBuf[36]=0x00;
	
	nIndex = 37;
	
	pBuf[nIndex++]=0x3d;  // �����룺 ������������
	memcpy_s(pBuf+nIndex,4,&dwConfig,sizeof(DWORD));
	nIndex+=4;

	pBuf[nIndex++]=0x17;  // �����룺 �˲�����������0
	memcpy_s(pBuf+nIndex,4,&dwFilter17,sizeof(DWORD));
	nIndex+=4;

	pBuf[nIndex++]=0x18;  // �����룺 �˲�����������1
	memcpy_s(pBuf+nIndex,4,&dwFilter18,sizeof(DWORD));
	nIndex+=4;

	pBuf[nIndex++]=0x00;	// ֹͣ��ʶ
	return SendToFDU(pBuf,128);
}
/**
 * @brief ��ɼ�վ����0x0A����
 * @note  �򵥸��ɼ�վ��������ȴ��˿ں����������Ϊ0x0A��
 �����ʽΪ16bits�˿�+16bits���
 16λ�˿�Ϊ������λ���㲥����Ķ˿ڣ���λ��ǰ����λ�ں�
 16λ������Ĭ��Ϊ0x0003,˳��Ϊ03 00��
 * @note �ڲɼ�������ɲɼ��󣬷��͸��������ڸı�òɼ����еĹ㲥�˿ڡ���������һ�εķ��ڲɼ���ͻ��
 * @param DWORD dwFDUIP���ɼ�վIP��ַ 
 * @param WORD wBroadcastPort���ɼ�վ�ȴ���λ���㲥����Ķ˿� 
 * @return �����ѷ��͵��ֽ���
 */
int CSocketFDU::SendBroadcastPortCmdToFDU(DWORD dwFDUIP,WORD wBroadcastPort)
{
	BYTE* pBuf = m_pBuf;
	memcpy_s(pBuf+16,4,&m_dwLocalIP,sizeof(DWORD));
	memcpy_s(pBuf+20,4,&dwFDUIP,sizeof(DWORD));
	memcpy_s(pBuf+24,2,&m_wLocalPort,sizeof(WORD));
	pBuf[26]=0x01;
	pBuf[27]=0;		// ��������
	
	pBuf[32]=0x0A;  // �����룺 ����ȴ��˿ں�����
	pBuf[33]=LOBYTE(wBroadcastPort);
	pBuf[34]=HIBYTE(wBroadcastPort);
	pBuf[35]=0x03;
	pBuf[36]=0x00;

	pBuf[37]=0x00;	// ֹͣ��ʶ
	return SendToFDU(pBuf,128);
}
/**
 * @brief ��ɼ�վ���͵���ָ��
 * @note  �򵥸��ɼ�վ���͵���ָ�����ָ��͵�����������ĸ�:0x07,0x08,0x09,0x0A��
 * @param DWORD dwFDUIP���ɼ�վIP��ַ 
 * @param WORD wMinPort�����ݷ��ض˿ڵ���Сֵ
 * @param WORD wMaxPort�����ݷ��ض˿ڵ����ֵ
 * @return �����ѷ��͵��ֽ���

int  CSocketFDU::SendCallCmdToFDU(DWORD dwFDUIP,WORD wMinPort,WORD wMaxPort)
{
	unsigned char*   pBuf = m_pBuf;	
	memcpy_s(pBuf+16,4,&m_dwLocalIP,sizeof(DWORD));
	memcpy_s(pBuf+20,4,&dwFDUIP,sizeof(DWORD));
	memcpy_s(pBuf+24,2,&m_wLocalPort,sizeof(WORD));
	pBuf[26]=0x01;
	pBuf[27]=0;	// ��������

	pBuf[32]=0x07; // ������:�Զ����ݷ��ص�ַ
	memcpy_s(pBuf+33,4,&m_dwLocalIP,sizeof(DWORD));

	pBuf[37]=0x08; // ������
	pBuf[38]=0x00; // �Զ����ݷ��ض˿�(SOCKET_REV8PORT: 0xB000)
	pBuf[39]=0xB0;
	pBuf[40]=0x03;//  ����2Byte,( �������λΪ1ʱ��ʶ����ѭ���˿�,��λ��0x03��ʾ������������)
	pBuf[41]=0x80;

	pBuf[42]=0x09;  // �����룺 �˿ڵ������޺�����
 	pBuf[43]=LOBYTE(wMinPort);
	pBuf[44]=HIBYTE(wMinPort);
	pBuf[45]=LOBYTE(wMaxPort);
	pBuf[46]=HIBYTE(wMaxPort);

	pBuf[47]=0x0A;  // �����룺 ����ȴ��˿ں�����
	pBuf[48]=LOBYTE(m_wLocalPort);
	pBuf[49]=HIBYTE(m_wLocalPort);
	pBuf[50]=0x03;
	pBuf[51]=0x00;

	pBuf[52] = 0;

	return SendToFDU(pBuf,128);

} */

/**
 * @brief ���Ͳ�ѯϵͳʱ������
 * @note  ��ָ���Ĳɼ�վ��IP��ַ�����Ͳ�ѯ����ϵͳʱ�����
 * @param  DWORD dwFDUIP���ɼ�վIP��ַ 
 * @return �����ѷ��͵��ֽ���
 */
int CSocketFDU::SendQueryTimeCmd(DWORD dwFDUIP)
{
	unsigned char*   pBuf = m_pBuf;		
	// Դ��ַ
	memcpy_s(pBuf+16,4,&m_dwLocalIP,sizeof(DWORD));
	// Ŀ�ĵ�ַ
	memcpy_s(pBuf+20,4,&dwFDUIP,sizeof(DWORD));
	// Դ��ַ�˿�
	pBuf[24] = LOBYTE(OPERATION_LOCALTIMEPORT);
	pBuf[25] = HIBYTE(OPERATION_LOCALTIMEPORT);
	//memcpy_s(pBuf+24,2,&m_wLocalPort,sizeof(WORD));
	// ��ѯ����
	pBuf[26]=0x02;
	pBuf[27]=0;
	// ������0x04��ʾ����ϵͳʱ��
	pBuf[32] = 0x04;	
	memset(pBuf+33,0,4);
	pBuf[37] = 0x3D;	
	memset(pBuf+38,0,5);
	return SendToFDU(pBuf,128);
}
/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ�� 0: û�н��յ�����
	           >0 : ��ǰϵͳʱ��
    
    ��    �ܣ� ����ϵͳʱ�䣬�ȴ�500ms�����ݣ�����0

    �޸���ʷ��

******************************************************************************
DWORD CSocketFDU::RevSystemTime(void)
{	
	if(m_FDUSocket==NULL)
		return false;

	char  byBuf[256];
	fd_set    readfs;
	timeval  timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec =500;		// �ȴ���ʱ
	DWORD    dwTime;
	
	readfs.fd_count =1;
	FD_SET(m_FDUSocket,&readfs);
	//	readfs.fd_array[0]=m_FDUSocket;
	if(select(0,&readfs,NULL,NULL,&timeout)<=0)			
	{
		// û���յ�����
		return 0;
	}
	if(FD_ISSET(m_FDUSocket,&readfs))
	{
		if(recvfrom(m_FDUSocket, byBuf, 256, 0,NULL,NULL)<=0)
			return 0;
		// �ж��Ƿ�Ϊ��ѯ�룬��������Ϊ0x04
		if(byBuf[26]!=0x02 || byBuf[27]!=0x00 || byBuf[28]!=0x04 )
			return 0;
		// ��������ϵͳʱ��
		memcpy_s(&dwTime,4,byBuf+29,4);
		return dwTime;
	}
	return 0;
}*/

/**
 * @brief ��ɼ�վ����ֹͣ����ָ��TE
 * @note  �ù㲥��ַ����ֹͣ���ݲ���������������㲥��ַ���ͣ��ɼ�վ�˿�Ϊ0x0Aָ����ָ���Ķ˿ڣ�
 �ɼ�ָ��ΪTB��TE��0x17��0x18��������ɼ�վ�����ݲ�����
 һ���ڲɼ�����׼����ʼ���ں��������ݲɼ�֮ǰ����ֹͣ�����ɼ���
 * @param DWORD dwTEH��TEʱ�̸�λ
 * @param DWORD dwTEL��TEʱ�̵�λ
 * @return �����ѷ��͵��ֽ���
 */

int CSocketFDU::SendTEBroadcastCmdToFDU(DWORD dwTEH, DWORD dwTEL)
{
	BYTE* pBuf = m_pBuf;
	DWORD nIndex;
	// Դ��ַ������IP
	memcpy_s(pBuf+16,4,&m_dwLocalIP,sizeof(DWORD));
	// �ɼ�վ�㲥��ַ0XFFFFFFFF
	//memcpy_s(pBuf+20,4,&dwIP,sizeof(DWORD));
	memset(pBuf+20,0xFF,sizeof(DWORD));	
	// Դ��ַ�Ķ˿�
	memcpy_s(pBuf+24,2,&m_wLocalPort,sizeof(WORD));
	pBuf[26]=0x01;
	pBuf[27]=0;	// ��������
	
	nIndex = 32;
	pBuf[nIndex++]=0x3E; // ������:�㲥�˿�ƥ��,������Ϊ16λ�˿�+16λ���� 
	pBuf[nIndex++]=LOBYTE(m_wLocalPort);
	pBuf[nIndex++]=HIBYTE(m_wLocalPort);
	pBuf[nIndex++]=0x03;
	pBuf[nIndex++]=00;
	
	pBuf[nIndex++]=0x10;  // �����룺TE_H				
	memcpy_s(pBuf+nIndex,4,&dwTEH,sizeof(DWORD));
	nIndex+=4;

	pBuf[nIndex++]=0x11;  // �����룺TE_L				
	memcpy_s(pBuf+nIndex,4,&dwTEL,sizeof(DWORD));
	nIndex+=4;

	pBuf[nIndex++] = 0;
	return SendToFDU(pBuf,128);
}

/**
 * @brief ��ɼ�վ���Ͳ���ָ��
 * @note  ��ɼ�վ���Ͳ���ָ�����������㲥��ַ���ͣ��ɼ�վ�˿�Ϊ0x0Aָ����ָ���Ķ˿ڣ�
 �ɼ������������ѭ���㲥�˿����0x07/0x08/0x09�����ɼ�ָ��TB��TE��0x0C��0x0D��0x10��0x11)���
 * @param DWORD dwIP��IP��ַ
 * @param WORD wMinPort����С�˿�
 * @param WORD wMaxPort�����˿�
 * @param DWORD dwTBH��TBʱ�̸�λ
 * @param DWORD dwTBL��TBʱ�̵�λ
 * @param DWORD dwTEH��TEʱ�̸�λ
 * @param DWORD dwTEL��TEʱ�̵�λ
 * @return �����ѷ��͵��ֽ���
 */
int CSocketFDU::SendSampParamCmdToFDU(DWORD dwIP,WORD wMinPort,WORD wMaxPort,DWORD dwTBH,DWORD dwTBL,
									  DWORD dwTEH,DWORD dwTEL)
{
	BYTE* pBuf = m_pBuf;
	DWORD nIndex;
	// Դ��ַ������IP
	memcpy_s(pBuf+16,4,&m_dwLocalIP,sizeof(DWORD));
	// �ɼ�վ�㲥��ַ0XFFFFFFFF
	memcpy_s(pBuf+20,4,&dwIP,sizeof(DWORD));
	// memset(pBuf+20,0xFF,sizeof(DWORD));
	// Դ��ַ�Ķ˿�
	memcpy_s(pBuf+24,2,&m_wLocalPort,sizeof(WORD));
	pBuf[26]=0x01;
	pBuf[27]=0;	// ��������

	nIndex = 32;
	pBuf[nIndex++]=0x3E; // ������:�㲥�˿�ƥ��,������Ϊ16λ�˿�+16λ���� 
	pBuf[nIndex++]=LOBYTE(m_wLocalPort);
	pBuf[nIndex++]=HIBYTE(m_wLocalPort);
	pBuf[nIndex++]=0x03;
	pBuf[nIndex++]=00;

	pBuf[nIndex++]=0x07; // ������:�Զ����ݷ��ص�ַ
	memcpy_s(pBuf+nIndex,4,&m_dwLocalIP,sizeof(DWORD));
	nIndex+=4;

	pBuf[nIndex++]=0x08; // pBuf[42]������
	pBuf[nIndex++]=LOBYTE(wMinPort); // �Զ����ݷ��ض˿�(SOCKET_REV8PORT: 0xB000)
	pBuf[nIndex++]=HIBYTE(wMinPort);
	pBuf[nIndex++]=0x03;//  ����2Byte,( �������λΪ1ʱ��ʶ����ѭ���˿�,��λ��0x03��ʾ������������)
	pBuf[nIndex++]=0x80;

	pBuf[nIndex++]=0x09;  // pBuf[47] �����룺 �˿ڵ������޺�����
	pBuf[nIndex++]=LOBYTE(wMinPort);
	pBuf[nIndex++]=HIBYTE(wMinPort);
	pBuf[nIndex++]=LOBYTE(wMaxPort);
	pBuf[nIndex++]=HIBYTE(wMaxPort);

	pBuf[nIndex++]=0x0C; // ������: TB_H				
	memcpy_s(pBuf+nIndex,4,&dwTBH,sizeof(DWORD));
	nIndex+=4;

	pBuf[nIndex++]=0x0D; // ������: TB_L				
	memcpy_s(pBuf+nIndex,4,&dwTBL,sizeof(DWORD));
	nIndex+=4;
	
	// pBuf[nIndex-2] = 0x80;// ���Դ���
	// pBuf[nIndex-1] = 0x92;// ���Դ���

	pBuf[nIndex++]=0x10;  // �����룺TE_H				
	memcpy_s(pBuf+nIndex,4,&dwTEH,sizeof(DWORD));
	nIndex+=4;
	
	pBuf[nIndex++]=0x11;  // �����룺TE_L				
	memcpy_s(pBuf+nIndex,4,&dwTEL,sizeof(DWORD));
	nIndex+=4;
	
	pBuf[nIndex++] = 0;
	return SendToFDU(pBuf,128);

}