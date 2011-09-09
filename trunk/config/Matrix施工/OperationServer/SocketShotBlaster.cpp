// SocketShotBlaster.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OperationServer.h"
#include "OperationServerDlg.h"
#include "SocketShotBlaster.h"
#include "OperationServerParseXML.h"

// CSocketShotBlaster

CSocketShotBlaster::CSocketShotBlaster()
: m_pDlg(NULL)
{
}

CSocketShotBlaster::~CSocketShotBlaster()
{
}

// CSocketShotBlaster ��Ա����
bool CSocketShotBlaster::CreateSocket(WORD wPort,LPCTSTR strIP,COperationServerDlg* pDlg)
{
	m_pDlg = pDlg;
	// ����socket
	if(!this->Create(wPort,SOCK_DGRAM,strIP))	//,strHostIP
	{	
		return false;
	}
	// ���ý��ջ�������С
	int RevBuf = 2048*1024;
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
	CString   strHostIP = strIP;
	m_dwHostIP = COperationServerParseXML::StringIPToDWORDIP(strHostIP);
	m_wBlasterPort = wPort;
	return true;	
}

/**
 * @brief ��ɼ�վ��������
 * @note  �����ķ��ͺ�������Ҫ��װIP��ַ�Ͷ˿ڵ�ת����
 * @param  pBuf���������ݻ�����ָ��
 * @param  nSize�����ݻ������Ĵ�С 
 * @return �����ѷ��͵��ֽ���
 */
int  CSocketShotBlaster::SendToFDU(unsigned char* pBuf,int nSize)
{
	sockaddr_in MainCrsAddr;
	MainCrsAddr.sin_family = AF_INET;
	// ������վ�˿�
	MainCrsAddr.sin_port = htons(theApp.m_wMainCrossPort);
	// ������վ��ַ
	MainCrsAddr.sin_addr.s_addr = theApp.m_dwMainCrossIP;
	return SendTo((char*)pBuf,nSize,(sockaddr*)&MainCrsAddr,sizeof(sockaddr_in));	
}
/**
 * @brief �������ݴ�����
 * @note  ���ؽ��պ���
 * @param  int nErrorCode,������ 
 * @return void
 */
void CSocketShotBlaster::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	
	if(m_pDlg)
	{
		m_pDlg->AnalysisProtocolOfBlasterSock();
	}
	CSocket::OnReceive(nErrorCode);
}