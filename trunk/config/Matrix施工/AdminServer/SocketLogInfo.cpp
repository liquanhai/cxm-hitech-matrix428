// SocketLogInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AdminServer.h"
#include "SocketLogInfo.h"


// CSocketLogInfo

CSocketLogInfo::CSocketLogInfo()
{
}

CSocketLogInfo::~CSocketLogInfo()
{
}


// CSocketLogInfo ��Ա����
/**
 * @brief ����Socket
 * @note  ����Socket�˿�
 * @param  UINT wPort,socket�˿�
 * @param  LPCTSTR strHostIP������IP��ַ
 * @return �����ɹ��򷵻�true��ʧ���򷵻�false
 */
bool CSocketLogInfo::CreateSocket(UINT wPort, LPCTSTR strHostIP)
{
	// ����socket
	if(!this->Create(wPort,SOCK_DGRAM,strHostIP))
	{		
		return false;
	}
	// ���ý��ջ�������С
	int RevBuf = 512*1024;
	if (this->SetSockOpt( SO_RCVBUF, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		this->Close();		
		return false;
	}
	// ���÷��ͻ�������С
	if (this->SetSockOpt(SO_SNDBUF, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		this->Close();		
		return false;
	}
	// ����������ܹ㲥��Ϣ
	RevBuf = 1;
	if (this->SetSockOpt(SO_BROADCAST, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		this->Close();		
		return false;
	}
	return true;
}
void CSocketLogInfo::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	static unsigned char	pBuf[SOCKET_LOGFRM_MAXLEN];	// ���ݻ�������󳤶��Ƿ�����־����֡��󳤶�
	WORD			wFrmLen = SOCKET_LOGFRM_MAXLEN;		// ֡��: ��ʼ��Ϊ�������Ĵ�С����ReceiveFrom����ʹ��
	WORD			wFrmCmdCode;						// ������
	DWORD			dwFrmIndex;							// ֡����	
	int				nSize,nReadSize;
	sockaddr_in		sockClient;
	sockClient.sin_family = AF_INET;
	nSize = sizeof(sockClient);
	
	// �������Կͻ��˵�����
	nReadSize = ReceiveFrom( pBuf, wFrmLen, (SOCKADDR*)&sockClient , &nSize );
	switch (nReadSize)
	{
	case 0:		// û���յ����� 
		return;
		break;
	case SOCKET_ERROR:	// �������󣬼�¼��־
		if (GetLastError() != WSAEWOULDBLOCK) 
		{  
			TRACE0("CSocketLog's ReceiveFrom error ��");
			return;
		}
		break;
	default:
		break;
	}
	// -----------����֡��ʽ---------------------------------------------------------
	// �ж�֡ͷ�Ƿ�0xEB, 0x90
	if (pBuf[0]!=0xEB || pBuf[1]!=0x90)
	{
		TRACE2("CSocketLog's ReceiveFrom��Frame head(%d,%d)is wrong��",pBuf[0],pBuf[1]);		
		return;
	}
	// ����֡����
	wFrmLen = MAKEWORD(pBuf[2],pBuf[3]);	
	// ����֡����
	memcpy_s(&dwFrmIndex,sizeof(dwFrmIndex),pBuf+4 , 4);
	// ֡β
	if(pBuf[wFrmLen-2]!=0x14 || pBuf[wFrmLen-1]!=0x6F)
	{
		// ֡β������Ҫ���¶�λ֡ͷ,֡���ȳ��������������¼��־		
		TRACE2("CSocketLog's ReceiveFrom��Frame end(%d,%d)is wrong��",pBuf[wFrmLen-2],pBuf[wFrmLen-1]);		
		return;
	}
	// -------------------���������룬���������������Ӧ����-------------------------------
	// ������
	wFrmCmdCode=MAKEWORD(pBuf[9],pBuf[10]);
	if(wFrmCmdCode==0xFFFF)
	{
		// ��־��¼֡
		if(theApp.m_Log.ReadFromSocketFrame(pBuf)>0)
		{
			theApp.m_LogFile.WriteLog(&(theApp.m_Log));
			if(theApp.m_Log.IsShowed())
				SendTo(pBuf,nReadSize,START_USERANDLOGPORT,_T("255.255.255.255"));
		}
	}
	CSocket::OnReceive(nErrorCode);
}
