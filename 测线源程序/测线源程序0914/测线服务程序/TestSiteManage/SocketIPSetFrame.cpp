// SocketIPSetFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestSiteManage.h"
#include "SocketIPSetFrame.h"
#include "Matrixline.h"

// CSocketIPSetFrame

CSocketIPSetFrame::CSocketIPSetFrame()
{
	// ֡�ֽ���
	m_iFrameSize = FrameLength;
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
	dwFrameCount = dwFrameCount / m_iFrameSize;

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
BOOL CSocketIPSetFrame::GetFrameData()
{
	BOOL bReturn = false;

	// �õ�֡����
	int iCount = Receive(m_oFrameIPSet.m_pFrameData, m_iFrameSize);
	if(iCount == m_iFrameSize)	//֡��С��ȷ
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
void CSocketIPSetFrame::MakeFrameData(CInstrument* pInstrument)
{
	// ԴIP��ַ
	m_oFrameIPSet.m_uiIPSource = m_uiIPForInstrument;
	// Ŀ��IP��ַ
	m_oFrameIPSet.m_uiIPAim = 0xFFFFFFFF;
	// Ŀ��˿ں�
	m_oFrameIPSet.m_usPortAim = m_uiPortForIPSet;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	m_oFrameIPSet.m_usCommand = 1;

	// ��������IP��ַ��Ϣ
	// �������� 1-����վ��2-��Դվ��3-�ɼ�վ
	m_oFrameIPSet.m_uiInstrumentType = pInstrument->m_uiInstrumentType;
	// �жϣ�����Ϊ����վ
	if(1 == pInstrument->m_uiInstrumentType)
	{
		// �жϣ�������վ
		if((0 == pInstrument->m_uiRoutIP) && (0 == pInstrument->m_uiRoutDirection))
		{
			// �жϣ�����Ҫ����·�ɵ�ַ
			if((0 == pInstrument->m_uiRoutIPLeft) && (0 == pInstrument->m_uiRoutIPRight) && (0 == pInstrument->m_uiRoutIPTop) && (0 == pInstrument->m_uiRoutIPDown))
			{
				// ������·�ɵ�ַ
				m_oFrameIPSet.m_uiInstrumentType = 3;
			}
		}
		// �жϣ�����վ�����Խ���վ�Ϸ�
		if((0 < pInstrument->m_uiRoutIP) && (1 == pInstrument->m_uiRoutDirection))
		{
			// �жϣ�����Ҫ����·�ɵ�ַ
			if((0 == pInstrument->m_uiRoutIPLeft) && (0 == pInstrument->m_uiRoutIPRight) && (0 == pInstrument->m_uiRoutIPTop) && (0xFFFF == pInstrument->m_uiRoutIPDown))
			{
				// ������·�ɵ�ַ
				m_oFrameIPSet.m_uiInstrumentType = 3;
			}
		}
		// �жϣ�����վ�����Խ���վ�·�
		if((0 < pInstrument->m_uiRoutIP) && (2 == pInstrument->m_uiRoutDirection))
		{
			// �жϣ�����Ҫ����·�ɵ�ַ
			if((0 == pInstrument->m_uiRoutIPLeft) && (0 == pInstrument->m_uiRoutIPRight) && (0xFFFF == pInstrument->m_uiRoutIPTop) && (0 == pInstrument->m_uiRoutIPDown))
			{
				// ������·�ɵ�ַ
				m_oFrameIPSet.m_uiInstrumentType = 3;
			}
		}
		// �жϣ�����վ�����Խ���վ��
		if((0 < pInstrument->m_uiRoutIP) && (3 == pInstrument->m_uiRoutDirection))
		{
			// �жϣ�����Ҫ����·�ɵ�ַ
			if((0 == pInstrument->m_uiRoutIPLeft) && (0xFFFF == pInstrument->m_uiRoutIPRight) && (0 == pInstrument->m_uiRoutIPTop) && (0 == pInstrument->m_uiRoutIPDown))
			{
				// ������·�ɵ�ַ
				m_oFrameIPSet.m_uiInstrumentType = 3;
			}
		}
		// �жϣ�����վ�����Խ���վ�ҷ�
		if((0 < pInstrument->m_uiRoutIP) && (4 == pInstrument->m_uiRoutDirection))
		{
			// �жϣ�����Ҫ����·�ɵ�ַ
			if((0xFFFF == pInstrument->m_uiRoutIPLeft) && (0 == pInstrument->m_uiRoutIPRight) && (0 == pInstrument->m_uiRoutIPTop) && (0 == pInstrument->m_uiRoutIPDown))
			{
				// ������·�ɵ�ַ
				m_oFrameIPSet.m_uiInstrumentType = 3;
			}
		}
	}
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
	int iCount = SendTo(m_oFrameIPSet.m_pFrameData, 128, m_uiPortLCI, m_strIPLCI);
}