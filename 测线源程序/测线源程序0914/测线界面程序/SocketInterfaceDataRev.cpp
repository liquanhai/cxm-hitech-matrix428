// CSocketInterfaceDataRev.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SocketInterfaceDataRev.h"
#include "MainFrm.h"


// CSocketInterfaceDataRev

CSocketInterfaceDataRev::CSocketInterfaceDataRev()
{
}

CSocketInterfaceDataRev::~CSocketInterfaceDataRev()
{
}

// CSocketInterfaceDataRev ��Ա����

void CSocketInterfaceDataRev::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	int iCount = ReceiveFrom(m_oFrameInterface.m_pFrameData, 65536, m_strIPSource, m_uiPortSource);
	if(iCount > 0)
	{
		// ֡�ֽ���
		m_iFrameSize = iCount;
		// ����֡ͷ
		m_oFrameInterface.ParseFrameHead();
		// �����ڲ���������֡
		CMainFrame* pMainFrame = NULL;
		pMainFrame = (CMainFrame*)AfxGetMainWnd();		
		pMainFrame->OnProcInterFaceCommand(&m_oFrameInterface);
	}

	CSocket::OnReceive(nErrorCode);
}

// ��ʼ��
BOOL CSocketInterfaceDataRev::OnInit(CString strIPForInterface, UINT uiPortForDataReceive)
{
	BOOL bReturn = false;

	// ���ڲ�ͨѶ�ı���IP��ַ
	m_strIPForInterface = strIPForInterface;
	// ��������֡�Ķ˿ں�
	m_uiPortForDataReceive = uiPortForDataReceive;
	// ��������˿�
	bReturn = Create(m_uiPortForDataReceive, SOCK_DGRAM, m_strIPForInterface);

	//���ù㲥ģʽ
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);

	return bReturn;	
}

// ���ý��ջ�������С
BOOL CSocketInterfaceDataRev::SetBufferSize(int iBufferSize)
{
	BOOL bReturn = false;

	int iOptionValue = iBufferSize;
	int iOptionLen = sizeof(int);
	bReturn = SetSockOpt(SO_RCVBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);

	return bReturn;
}
