#include "StdAfx.h"
#include "OperationServerDlg.h"
#include "ClientSocket.h"
#include "..//common/OperaStruct.h"
/**
 * @brief CSocketShotClient���캯��
 */
CSocketShotClient::CSocketShotClient(void)
: m_pDlg(NULL)
{
}
/**
 * @brief CSocketShotClient��������
 */
CSocketShotClient::~CSocketShotClient(void)
{
}
bool CSocketShotClient::CreateClientSocket(UINT wPort, LPCTSTR strHostIP,COperationServerDlg* pDlg)
{
	
	this->m_pDlg = pDlg;
	// ����socket
	if(!this->Create(wPort,SOCK_DGRAM,strHostIP))
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
	return true;
}
/**
 * @brief ��������
 * @note  ���ղ��������Կͻ��˵����ݡ�
 * @param  int nErrorCode��socketͨ�Ŵ�����
 * @return void
 */
void CSocketShotClient::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���	
	if(m_pDlg)
	{
		m_pDlg->AnalysisProtocolOfClientSock();
	}
	CSocket::OnReceive(nErrorCode);
}

/******************************************************************************
    ��    ����SendDataToClient
    
    ��    �룺sockaddr_in* lpSockAddr      -- �ͻ���socket��ַ
	          unsigned char* lpBuf         -- ���ݻ�����
			  int nSize                    -- ���ݻ�������Ҫ���͵��ֽ���
    
    ��    ����
  
    �� �� ֵ�� ���͵��ֽ���
    
    ��    �ܣ� ��ͻ��˷�������

    �޸���ʷ��

******************************************************************************
int CSocketShotClient::SendDataToClient(sockaddr_in* lpSockAddr,unsigned char* lpBuf ,int nSize)
{
	return  SendTo(lpBuf,nSize,(SOCKADDR*)lpSockAddr,sizeof(sockaddr_in));
}*/
/**
 * @brief ��������
 * @note  ��ͻ��˷������ݣ��ú�����Ҫ��װIP��ַ������˿ڵ�ת�����������������״̬���ͺ������á�
 * @param  DWORD dwSockAddr�����ն������ַ
 * @param  WORD wClientPort�����ն˶˿�
 * @param  unsigned char* lpBuf����Ҫ���͵����ݻ�����
 * @param  int nSize�����������ݴ�С
 * @return �ѷ��͵��ֽ���
 */
int CSocketShotClient::SendDataToClient(DWORD dwSockAddr,WORD wClientPort,unsigned char* lpBuf ,int nSize)
{
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = dwSockAddr;
	service.sin_port = htons(wClientPort);
	return  SendTo(lpBuf,nSize,(SOCKADDR*)&service,sizeof(sockaddr_in));
}


/******************************************************************************
    ��    ����SendAckOfRequest
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ�ʩ���ͻ����ڷ���ǰ�������������ڷ��񡣷��������յ���������
	          ��ͻ��˷��ص�ǰ�����߳���״̬��Ϣ��

			  ����֡��ʽ��
			  ֡ͷ��2Byte����֡���ȣ�2Byte��  ��֡������4Byte����֡���ͣ�1Byte��			   
			  ������(2Byte)�����ݸ�����2Byte�������������䳤�� ��У��λ��1Byte����֡β��2Byte��

    �޸���ʷ��

******************************************************************************
int CSocketShotClient::SendAckOfRequest(sockaddr_in* lpSockAddr,DWORD dwFrmIndex,DWORD dwShotNb,DWORD dwSourceNb, int nThreadIndex)
{
	unsigned char   pBuf[21];

	pBuf[0] = 0xEB;
	pBuf[1] = 0x90;

	// ֡��
	pBuf[2] = 28;
	pBuf[3] = 0;
	// ֡����
	memcpy_s(pBuf+4,4,&dwFrmIndex,4);
	// ֡����
	pBuf[8] = 0xFF;
	// ������
	pBuf[9]  = LOBYTE(OPERATION_CMD_REQUEST);
	pBuf[10] = HIBYTE(OPERATION_CMD_REQUEST);
	// ���ݸ���
	pBuf[11] =12;
	pBuf[12] =0;
	// �����߳�������
	memcpy_s(pBuf+13,4,&dwShotNb,4);
	memcpy_s(pBuf+17,4,&dwSourceNb,4);
	memcpy_s(pBuf+21,4,&nThreadIndex,4);
	// ֡У��
	pBuf[25]=0;
	// ֡β
	pBuf[26] = 0x14;
	pBuf[27] = 0x6F;

	return  SendTo(pBuf,28,(SOCKADDR*)lpSockAddr,sizeof(sockaddr_in));
}*/