// SocketInterfaceCmdSend.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SocketInterfaceCmdSend.h"


// CSocketInterfaceCmdSend

CSocketInterfaceCmdSend::CSocketInterfaceCmdSend()
{
	// �յ�Ӧ��֡��֡����������󳤶�
	m_iFrameCountListLengthMaxReply = 100;
	// �ͻ���Ŀ��IP��ַ
	m_strIPAim = "255.255.255.255";
}

CSocketInterfaceCmdSend::~CSocketInterfaceCmdSend()
{
}


// CSocketInterfaceCmdSend ��Ա����

void CSocketInterfaceCmdSend::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	int iCount = Receive(m_oFrameInterface.m_pFrameData, 65536);
	if(iCount > 0)
	{
		// ֡�ֽ���
		m_iFrameSize = iCount;
		// ����֡ͷ
		m_oFrameInterface.ParseFrameHead();
		// �����յ���Ӧ��֡
		SaveReplyFrame();
	}
	CSocket::OnReceive(nErrorCode);
}

// ��ʼ��
BOOL CSocketInterfaceCmdSend::OnInit(CString strIPForInterface, UINT uiPortForCommandSend, UINT uiPortAimToServer, UINT uiPortAimToOperation)
{
	BOOL bReturn = false;

	// ���ڲ�ͨѶ�ı���IP��ַ
	m_strIPForInterface = strIPForInterface;
	// ��������֡�Ķ˿ں�
	m_uiPortForCommandSend = uiPortForCommandSend;
	// �ͻ���Ŀ��IP�˿ںţ����߷�����
	m_uiPortAimToServer = uiPortAimToServer;
	// �ͻ���Ŀ��IP�˿ںţ�ʩ���ͻ���
	m_uiPortAimToOperation = uiPortAimToOperation;
	// ��������˿�
	bReturn = Create(m_uiPortForCommandSend, SOCK_DGRAM, m_strIPForInterface);

	//���ù㲥ģʽ
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);

	return bReturn;	
}

// ���û�������С
BOOL CSocketInterfaceCmdSend::SetBufferSize(int iBufferSize)
{
	BOOL bReturn = false;

	int iOptionValue = iBufferSize;
	int iOptionLen = sizeof(int);
	bReturn = SetSockOpt(SO_SNDBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);

	iOptionValue = iBufferSize;
	iOptionLen = sizeof(int);
	bReturn = SetSockOpt(SO_RCVBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);

	return bReturn;
}

// ��������֡
void CSocketInterfaceCmdSend::SendCommandFrame()
{
	int iCount = 0;
	iCount = SendTo(m_oFrameInterface.m_pFrameData, m_oFrameInterface.m_usFrameSize, m_uiPortAimToServer, m_strIPAim);
	iCount = SendTo(m_oFrameInterface.m_pFrameData, m_oFrameInterface.m_usFrameSize, m_uiPortAimToOperation, m_strIPAim);
}

// �����յ���Ӧ��֡
void CSocketInterfaceCmdSend::SaveReplyFrame()
{
	UINT uiFrameCount;
	// ��ǰ�յ���
	if(TRUE == m_oFrameCountMapReply.Lookup(m_oFrameInterface.m_uiFrameCount, uiFrameCount))
	{
		return;
	}
	else	// ��һ���յ�
	{
		// ����������
		m_oFrameCountMapReply.SetAt(m_oFrameInterface.m_uiFrameCount, m_oFrameInterface.m_uiFrameCount);
		// �������
		m_oFrameCountListReply.AddTail(m_oFrameInterface.m_uiFrameCount);
		// ���й���
		if(m_iFrameCountListLengthMaxReply < m_oFrameCountListReply.GetCount())
		{
			// �Ƴ�����
			uiFrameCount = m_oFrameCountListReply.RemoveHead();
			// �Ƴ�������
			m_oFrameCountMapReply.RemoveKey(uiFrameCount);
		}
	}
}
