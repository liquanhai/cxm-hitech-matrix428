// SocketTimeSetFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestSiteManage.h"
#include "SocketTimeSetFrame.h"


// CSocketTimeSetFrame

CSocketTimeSetFrame::CSocketTimeSetFrame()
{
	// ֡�ֽ���
	m_iFrameSize = 256;
}

CSocketTimeSetFrame::~CSocketTimeSetFrame()
{
}

/**
* ��ʼ��
* @param CString strIPForInstrument ��ԴIP��ַ
* @param UINT uiIPForInstrument ��ԴIP��ַ
* @param UINT uiPortForTimeSet	��Դ�˿ں�
* @param CString strIPLCI ����IP��ַ
* @param UINT uiPortLCI	���޶˿ں�
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CSocketTimeSetFrame::OnInit(CString strIPForInstrument, UINT uiIPForInstrument, UINT uiPortForTimeSet, CString strIPLCI, UINT uiPortLCI)
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
	// ��������ʱ�����õĶ˿ں�
	m_uiPortForTimeSet = uiPortForTimeSet;
	// ��������˿�
	bReturn = Create(m_uiPortForTimeSet, SOCK_DGRAM, m_strIPForInstrument);
	Bind(m_uiPortForTimeSet,m_strIPForInstrument);
	//���ù㲥ģʽ
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);

	return bReturn;
}

/**
* ���û��������Է��͵�֡����
* @param void
* @return DWORD ֡����
*/
BOOL CSocketTimeSetFrame::SetBufferSize(int iFrameCount)
{
	BOOL bReturn = false;

	int iOptionValue = iFrameCount * m_iFrameSize;
	int iOptionLen = sizeof(int);
	bReturn = SetSockOpt(SO_SNDBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);

	return bReturn;
}

/**
* ��������ʱ������֡
* @param CInstrument* pInstrument ����ָ��
* @return void
*/
void CSocketTimeSetFrame::MakeFrameData(CInstrument* pInstrument)
{
	// ԴIP��ַ
	m_oFrameTimeSet.m_uiIPSource = m_uiIPForInstrument;
	// Ŀ��IP��ַ
	m_oFrameTimeSet.m_uiIPAim = pInstrument->m_uiIP;
	// Ŀ��˿ں�
	m_oFrameTimeSet.m_usPortAim = (unsigned short)m_uiPortForTimeSet;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	m_oFrameTimeSet.m_usCommand = 1;

	// ��������ʱ����Ϣ
	// ����ʱ��������λ
	m_oFrameTimeSet.m_uiTimeHigh = pInstrument->m_uiTimeHigh;
	// ����ʱ��������λIP
	m_oFrameTimeSet.m_uiTimeLow = pInstrument->m_uiTimeLow;
	// ����֡
	m_oFrameTimeSet.MakeFrameData();
}

/**
* ��������ʱ������֡
* @param void
* @return void
*/
void CSocketTimeSetFrame::SendTimeSetFrame()
{
	// ����֡
	int iCount = SendTo(m_oFrameTimeSet.m_pFrameData, 128, m_uiPortLCI, m_strIPLCI);
}
