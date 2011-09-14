// SocketTailTimeFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
// CSocketTailTimeFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestSiteManage.h"
#include "SocketTailTimeFrame.h"


// CSocketTailTimeFrame

CSocketTailTimeFrame::CSocketTailTimeFrame()
{
	// ֡�ֽ���
	m_iFrameSize = 256;
}

CSocketTailTimeFrame::~CSocketTailTimeFrame()
{
}

/**
* ��ʼ��
* @param CString strIPForInstrument ��ԴIP��ַ
* @param UINT uiIPForInstrument ��ԴIP��ַ
* @param UINT uiPortForTailTime	��Դ�˿ں�
* @param CString strIPLCI ����IP��ַ
* @param UINT uiPortLCI	���޶˿ں�
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CSocketTailTimeFrame::OnInit(CString strIPForInstrument, UINT uiIPForInstrument, UINT uiPortForTailTime, CString strIPLCI, UINT uiPortLCI)
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
	// ��������β��ʱ�̲�ѯ�Ķ˿ں�
	m_uiPortForTailTime = uiPortForTailTime;
	// ��������˿�
	bReturn = Create(m_uiPortForTailTime, SOCK_DGRAM, m_strIPForInstrument);

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
DWORD CSocketTailTimeFrame::GetFrameCount()
{
	DWORD dwFrameCount = 0;

	// �õ�������ջ����������ֽ���
	IOCtl(FIONREAD, &dwFrameCount);
	// �õ�֡����
	dwFrameCount = dwFrameCount / m_iFrameSize;

	return dwFrameCount;
}

/**
* ���û����������շ���֡����
* @param int iFrameCount IP֡����
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CSocketTailTimeFrame::SetBufferSize(int iFrameCount)
{
	BOOL bReturn = false;

	int iOptionValue = iFrameCount * m_iFrameSize;
	int iOptionLen = sizeof(int);
	bReturn = SetSockOpt(SO_RCVBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);

	iOptionValue = iFrameCount * m_iFrameSize;
	iOptionLen = sizeof(int);
	bReturn = SetSockOpt(SO_SNDBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
	return bReturn;
}

/**
* �õ�֡����
* @param void
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CSocketTailTimeFrame::GetFrameData()
{
	BOOL bReturn = false;

	// �õ�֡����
	m_oFrameTailTime.Reset();
	int iCount = Receive(m_oFrameTailTime.m_pFrameData, m_iFrameSize);
	if(iCount == m_iFrameSize)	//֡��С��ȷ
	{
		// ����֡����
		bReturn = m_oFrameTailTime.ParseFrame();
	}
	return bReturn;
}

/**
* ��������β��ʱ�̲�ѯ֡
* @param CInstrument* pInstrument ����ָ��
* @return void
*/
void CSocketTailTimeFrame::MakeFrameData(CInstrument* pInstrument)
{
	m_oFrameTailTime.Reset();
	// ԴIP��ַ
	m_oFrameTailTime.m_uiIPSource = m_uiIPForInstrument;
	// Ŀ��IP��ַ
	//m_oFrameTailTime.m_uiIPAim = pInstrument->m_uiIP;
	if(pInstrument->m_uiInstrumentType==1)
		m_oFrameTailTime.m_uiIPAim = pInstrument->m_uiIP;
	else
		m_oFrameTailTime.m_uiIPAim = 0xFFFFFFFF;

	// �������� 1-����վ��2-��Դվ��3-�ɼ�վ
	m_oFrameTailTime.m_uiInstrumentType = pInstrument->m_uiInstrumentType;
	// Ŀ��˿ں�
	m_oFrameTailTime.m_usPortAim = m_uiPortForTailTime;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	m_oFrameTailTime.m_usCommand = 2;
	// ����֡
	m_oFrameTailTime.MakeFrameData();
}

/**
* ��������β��ʱ�̲�ѯ֡
* @param void
* @return void
*/
void CSocketTailTimeFrame::SendTailTimeFrame()
{
	// ����֡
	int iCount = SendTo(m_oFrameTailTime.m_pFrameData, 128, m_uiPortLCI, m_strIPLCI);
}

/**
* ����������ջ�����
* @param void
* @return void
*/
void CSocketTailTimeFrame::RemoveFrameDataAll()
{
	int iFrameCount = 0;
	iFrameCount = GetFrameCount();
	if(iFrameCount > 0)
	{
		for(int i = 0; i < iFrameCount; i++)
		{
			GetFrameData();
		}		
	}
}

