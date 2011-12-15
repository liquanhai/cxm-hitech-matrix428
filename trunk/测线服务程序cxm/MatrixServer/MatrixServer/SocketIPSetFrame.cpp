// SocketIPSetFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixServer.h"
#include "SocketIPSetFrame.h"
#include "..\\parameter\\Parameter.h"

// CSocketIPSetFrame

CSocketIPSetFrame::CSocketIPSetFrame()
{
}

CSocketIPSetFrame::~CSocketIPSetFrame()
{
}

/**
* ��ʼ��
* @param CString strIPForInstrument ��ԴIP��ַ
* @param UINT uiIPForInstrument ��ԴIP��ַ
* @param UINT uiPortForIPSet	��Դ�˿ں�
* @param CString strIPLCI ����IP��ַ
* @param UINT uiPortLCI	���޶˿ں�
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CSocketIPSetFrame::OnInit(CString strIPForInstrument, UINT uiIPForInstrument, UINT uiPortForIPSet, CString strIPLCI, UINT uiPortLCI)
{
	BOOL bReturn = false;

	// LCI�豸IP��ַ
	m_strIPLCI = strIPLCI;
	//  LCI�豸IP��ַ�˿ں�
	m_uiPortLCI = uiPortLCI;

	// ���ֳ�����ͨѶ�ı���IP��ַ
	m_strIPForInstrument = strIPForInstrument;
	// ���ֳ�����ͨѶ�ı���IP��ַ
	m_uiIPForInstrument = uiIPForInstrument;
	// ��������IP��ַ���õĶ˿ں�
	m_uiPortForIPSet = uiPortForIPSet;
	// ��������˿�
	bReturn = Create(m_uiPortForIPSet, SOCK_DGRAM, m_strIPForInstrument);
	Bind(m_uiPortForIPSet,m_strIPForInstrument);
	//���ù㲥ģʽ
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);

	return bReturn;
}

/**
* �õ�������ջ������յ���֡����
* @param void
* @return DWORD ֡����
*/
DWORD CSocketIPSetFrame::GetFrameCount()
{
	DWORD dwFrameCount = 0;

	// �õ�������ջ����������ֽ���
	IOCtl(FIONREAD, &dwFrameCount);
	// �õ�֡����
	dwFrameCount = dwFrameCount / RcvFrameSize;

	return dwFrameCount;
}

/**
* ���û����������շ���֡����
* @param int iFrameCount IP֡����
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CSocketIPSetFrame::SetBufferSize(int iFrameCount)
{
	BOOL bReturn = false;

	int iOptionValue = iFrameCount * RcvFrameSize;
	int iOptionLen = sizeof(int);
	bReturn = SetSockOpt(SO_RCVBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);

	iOptionValue = iFrameCount * SndFrameSize;
	iOptionLen = sizeof(int);
	bReturn = SetSockOpt(SO_SNDBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);

	return bReturn;
}

/**
* �õ�֡����
* @param void
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CSocketIPSetFrame::GetFrameData()
{
	BOOL bReturn = false;

	// �õ�֡����
	int iCount = Receive(m_oFrameIPSet.m_pRcvFrameData, RcvFrameSize);
	if(iCount == RcvFrameSize)	//֡��С��ȷ
	{
		// ����֡����
		bReturn = m_oFrameIPSet.ParseFrame();
	}
	return bReturn;
}

/**
* ��������IP��ַ����֡
* @param CInstrument* pInstrument ����ָ��
* @return void
*/
void CSocketIPSetFrame::MakeFrameData(CInstrument* pInstrument, unsigned short usCommand)
{
	// ԴIP��ַ
	m_oFrameIPSet.m_uiIPSource = m_uiIPForInstrument;
	// Ŀ��IP��ַ
	if (usCommand == SendSetCmd)
	{
		m_oFrameIPSet.m_uiIPAim = IPBroadcastAddr;
	}
	else if (usCommand == SendQueryCmd)
	{
		m_oFrameIPSet.m_uiIPAim = pInstrument->m_uiIP;
	}
	// Ŀ��˿ں�
	m_oFrameIPSet.m_usPortAim = (unsigned short)m_uiPortForIPSet;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	m_oFrameIPSet.m_usCommand = usCommand;
	// ��������IP��ַ��Ϣ
	// �������� 1-����վ��2-��Դվ��3-�ɼ�վ
	m_oFrameIPSet.m_uiInstrumentType = pInstrument->m_uiInstrumentType;
	// ����SN��
	m_oFrameIPSet.m_uiSN = pInstrument->m_uiSN;
	// ��������IP
	m_oFrameIPSet.m_uiIPInstrument = pInstrument->m_uiIP;
	// ·��IP��ַ��·�ɷ��� 1-��
	m_oFrameIPSet.m_uiRoutIPTop = pInstrument->m_uiRoutIPTop;
	// ·��IP��ַ��·�ɷ��� 2-��
	m_oFrameIPSet.m_uiRoutIPDown = pInstrument->m_uiRoutIPDown;
	// ·��IP��ַ��·�ɷ��� 3-��
	m_oFrameIPSet.m_uiRoutIPLeft = pInstrument->m_uiRoutIPLeft;
	// ·��IP��ַ��·�ɷ��� 4-��
	m_oFrameIPSet.m_uiRoutIPRight = pInstrument->m_uiRoutIPRight;
	// �㲥�˿�
	m_oFrameIPSet.m_uiBroadCastPort = pInstrument->m_uiBroadCastPort;
	// ����֡
	m_oFrameIPSet.MakeFrameData();
}

/**
* ��������IP��ַ����֡
* @param void
* @return void
*/
void CSocketIPSetFrame::SendIPSetFrame()
{
	// ����֡
	SendTo(m_oFrameIPSet.m_pSndFrameData, SndFrameSize, m_uiPortLCI, m_strIPLCI);
}