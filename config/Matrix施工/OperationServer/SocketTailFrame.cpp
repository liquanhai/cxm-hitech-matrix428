// SocketTailFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OperationServer.h"
#include "SocketTailFrame.h"


// CSocketTailFrame
/**
 * @brief CSocketTailFrame���캯��
 */
CSocketTailFrame::CSocketTailFrame()
{
}
/**
 * @brief CSocketTailFrame��������
 */
CSocketTailFrame::~CSocketTailFrame()
{
}
// CSocketTailFrame ��Ա����
/**
 * @brief ��������β����Socket�˿�
 * @note  ��������β����Socket�˿ڣ��ö˿ڽ���β������β��֡�н�����������ǰ��ϵͳʱ�䡣
 * @param  UINT wPort, Socket�˿ڣ�
 * @param  LPCTSTR strHostIP,����IP��ַ
 * @return �ɹ��򷵻�true��ʧ�ܷ���false
 */
bool CSocketTailFrame::CreateTailFrameSocket(UINT wPort, LPCTSTR strHostIP)
{
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
 * @brief β�����մ�����
 * @note  ����β������β��֡�н�����������ǰ��ϵͳʱ�䡣
 * @param  int nErrorCode��socket������
 * @return void
 */
void CSocketTailFrame::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	unsigned char pBuf[256];
	DWORD    dwTemp;
	int nReadSize = Receive( pBuf, 256);
	if(nReadSize>0)
	{
		// �������ݰ�
		// memcpy_s(&dwTemp,4,pBuf+16,4);
		// ������վ
		//if(dwTemp==MAINCROSS_LOGICIP)
		{
			// ����ϵͳʱ��
			for(int i=0;i<8;i++)
			{		
				switch(pBuf[28+i*5])	// ������
				{
				case 0x00:
					i=10;  // ����֡����,�˳�
					break;
				case 0x04:// �õ�ϵͳʱ��
					memcpy_s(&dwTemp, 4,pBuf+29 + i* 5, 4);					
					theApp.SetFDULocalTime(dwTemp);
					TRACE1("0 FDU Time:%d\n",dwTemp);
					// return;
					i=10;	// �ҵ�������˳�
					break;
				default:
					break;
				}
			}
		}

	}
	CSocket::OnReceive(nErrorCode);
}
