// SocketInterface.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestSiteManage.h"
#include "SocketInterfaceCmdRev.h"

// CSocketInterface

CSocketInterfaceCmdRev::CSocketInterfaceCmdRev()
{
	// �յ�����֡��֡����������󳤶�
	m_iFrameCountListLengthMaxReceive = 100;
}

CSocketInterfaceCmdRev::~CSocketInterfaceCmdRev()
{
}

// CSocketInterface ��Ա����

/**
* ��Ӧ���ݵ�����Ϣ��������������
* @param int nErrorCode
* @return void
*/
void CSocketInterfaceCmdRev::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	int iCount = ReceiveFrom(m_oFrameInterface.m_pFrameData, 65536, m_strIPSource, m_uiPortSource);
	if(iCount > 0)
	{
		// ֡�ֽ���
		m_iFrameSize = iCount;
		// ����֡ͷ
		m_oFrameInterface.ParseFrameHead();
		// ���ͻ���֡
		SendReplyFrame();
		// ����Ƿ����ظ����յ�������֡
		if(true == CheckIfRepeatFrameCommand())
		{
			return;
		}
		// ����������
		m_oFrameInterface.ParseCommandWord();
		// �����ڲ���������֡
		m_pNetProcInterface->OnProcInterFaceCommand(&m_oFrameInterface);
	}

	CSocket::OnReceive(nErrorCode);
}

/**
* ��ʼ��
* @param CString strIPForInterface ����IP��ַ
* @param UINT uiPortForCommandReceive ���ն˿ں�
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CSocketInterfaceCmdRev::OnInit(CString strIPForInterface, UINT uiPortForCommandReceive)
{
	BOOL bReturn = false;

	// ���ڲ�ͨѶ�ı���IP��ַ
	m_strIPForInterface = strIPForInterface;
	// ��������֡�Ķ˿ں�
	m_uiPortForCommandReceive = uiPortForCommandReceive;
	// ��������˿�
	bReturn = Create(m_uiPortForCommandReceive, SOCK_DGRAM, m_strIPForInterface);
	Bind(uiPortForCommandReceive,m_strIPForInterface);
	//���ù㲥ģʽ
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);

	return bReturn;	
}

/**
* ���ý��ջ�������С
* @param int iBufferSize ��������С
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CSocketInterfaceCmdRev::SetBufferSize(int iBufferSize)
{
	BOOL bReturn = false;

	int iOptionValue = iBufferSize;
	int iOptionLen = sizeof(int);
	bReturn = SetSockOpt(SO_RCVBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);

	return bReturn;
}

/**
* ���ͻ���֡
* @param void
* @return void
*/
void CSocketInterfaceCmdRev::SendReplyFrame()
{
	// 0x02-����֡��Ҫ�����֡
	if(2 == m_oFrameInterface.m_byFrameType)
	{
		m_oFrameReply.MakeReplyFrame(&m_oFrameInterface);
		SendTo(m_oFrameReply.m_pFrameData, m_oFrameReply.m_usFrameSize, m_uiPortSource, m_strIPSource);
	}
}

/**
* ����Ƿ����ظ����յ���֡
* @param int iBufferSize ��������С
* @return bool true���ǣ�false����
*/
bool CSocketInterfaceCmdRev::CheckIfRepeatFrameCommand()
{
	bool bReturn = false;
	UINT uiFrameCount;
	// ��ǰ�յ���
	if(TRUE == m_oFrameCountMapReceive.Lookup(m_oFrameInterface.m_uiFrameCount, uiFrameCount))
	{
		return true;
	}
	else	// ��һ���յ�
	{
		// ����������
		m_oFrameCountMapReceive.SetAt(m_oFrameInterface.m_uiFrameCount, m_oFrameInterface.m_uiFrameCount);
		// �������
		m_oFrameCountListReceive.AddTail(m_oFrameInterface.m_uiFrameCount);
		// ���й���
		if(m_iFrameCountListLengthMaxReceive < m_oFrameCountListReceive.GetCount())
		{
			// �Ƴ�����
			uiFrameCount = m_oFrameCountListReceive.RemoveHead();
			// �Ƴ�������
			m_oFrameCountMapReceive.RemoveKey(uiFrameCount);
		}
	}
	return bReturn;
}