// MySocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OnReceive����.h"
#include "MySocket.h"


// CMySocket

CMySocket::CMySocket()
: m_uiRcvByteNum(0)
{
}

CMySocket::~CMySocket()
{
}


// CMySocket ��Ա����

void CMySocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	CSocket::OnReceive(nErrorCode);
// 	DWORD dwReceived;
 	unsigned char ucUdpBuf[51200];
 	int iCount = 0;
// 	if (IOCtl(FIONREAD, &dwReceived))
// 	{
// 		if (dwReceived > 0)   // Process only if you have enough data
// 		{
			iCount = Receive(ucUdpBuf,51200);
			m_uiRcvByteNum += 256;
		//	SendTo(ucUdpBuf, 256, 0x9800, _T("192.168.0.19"));
// 		}
// 	}
// 	else
// 	{
// 		// Error handling here
// 	}

}
