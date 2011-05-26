// TailFrameThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "TailFrameThread.h"
#include "Parameter.h"

// CTailFrameThread

IMPLEMENT_DYNCREATE(CTailFrameThread, CWinThread)

CTailFrameThread::CTailFrameThread()
: m_bclose(false)
, m_uiSN(0)
, m_uiNetTime(0)
, m_uiSystemTime(0)
, m_usTailRecTime(0)
, m_usTailSendTime(0)
, m_uiSendTailTimeFrameCount(0)
, m_uiRecTailTimeFrameCount(0)
, m_iTimeHigh(0)
, m_iTimeLow(0)
, m_uiDelayTimeCount(0)
, m_csIPSource(_T(""))
, m_uiSendPort(0)
{
}

CTailFrameThread::~CTailFrameThread()
{
}

BOOL CTailFrameThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CTailFrameThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CTailFrameThread, CWinThread)
END_MESSAGE_MAP()


// ��ʼ��

void CTailFrameThread::OnInit(void)
{
	m_hTailFrameThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	::ResetEvent(m_hTailFrameThreadClose);	// �����¼�����Ϊ���ź�״̬
}
// �̺߳�����Run��ִ��
int CTailFrameThread::Run()
{
	DWORD dwTailFrameCount = 0;
	int iTailcount = 0;
	DWORD dwTailTimeFrameCount = 0;
	int iTailTimecount = 0;
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		if(m_bclose == true)
		{
			break;
		}
		// �õ�������ջ����������ֽ���
		m_TailFrameSocket.IOCtl(FIONREAD, &dwTailFrameCount);
		dwTailFrameCount = dwTailFrameCount/256;
		if(0 != dwTailFrameCount)	
		{
			for(unsigned int i = 0; i < dwTailFrameCount; i++)	
			{
				iTailcount = m_TailFrameSocket.Receive(m_pTailFrameData,256);
				if (iTailcount == 256)
				{
					// ����β������
					ProcTailFrameOne();
				}
				else
				{
					break;
				}
			}
		}
		// �õ�������ջ����������ֽ���
		m_TailTimeFrameSocket.IOCtl(FIONREAD, &dwTailTimeFrameCount);
		dwTailTimeFrameCount = dwTailTimeFrameCount/256;
		if(0 != dwTailTimeFrameCount)	
		{
			for(unsigned int i = 0; i < dwTailTimeFrameCount; i++)
			{
				iTailTimecount = m_TailTimeFrameSocket.Receive(m_pTailTimeRecData,256);
				if (iTailTimecount == 256)
				{
					// ����β��ʱ�̲�ѯ����
					ProcTailTimeFrameOne();
				}
				else
				{
					break;
				}
			}
		}
		if (m_bclose == true)
		{
			break;
		}
		Sleep(250);
	}
	::SetEvent(m_hTailFrameThreadClose);	// �����¼�����Ϊ���ź�״̬
	// ����
	return CWinThread::Run();
}
// �رղ������߳�
void CTailFrameThread::OnClose(void)
{
//	m_TailFrameSocket.ShutDown(2);
//	m_TailTimeFrameSocket.ShutDown(2);
	m_TailFrameSocket.Close();
	m_TailTimeFrameSocket.Close();
	m_bclose = true;
}

// ������β��
void CTailFrameThread::ProcTailFrameOne(void)
{
	if (ParseTailFrame() == FALSE)
	{
		return;
	}
	CInstrument* pInstrument = NULL;
	// �������������ҵ�������,�õ�������ָ��
	if (TRUE == m_oInstrumentList->GetInstrumentFromMap(m_uiSN, pInstrument))
	{
		// ����ǽ���վβ���򲻴�������ǲɼ�վβ��
		if (pInstrument->m_uiInstrumentType == 3)
		{
			// β����������һ
			pInstrument->m_iTailFrameCount++;
			// ���β��ʱ�̲�ѯ����һ��β������֮�ʻ�δ��ȫ��������ϴβ�ѯ�������δ�յ�β��ʱ�̲�ѯ��������Ϊ���ڱ�־
			if (m_uiSendTailTimeFrameCount != m_uiRecTailTimeFrameCount)
			{
				m_uiRecTailTimeFrameCount = 0;
				m_uiSendTailTimeFrameCount = 0;
				m_oInstrumentList->ClearExperiedTailTimeResult();
			}
		}
	}
	else
	{
		return;
	}
	// �ж�β���������ﵽ�趨ֵ
	if (pInstrument->m_iTailFrameCount == TailFrameCount)
	{
		pInstrument->m_iTailFrameCount = 0;
		// �жϲɼ�վλ�ú����Ƿ�������������ɾ��
		m_oInstrumentList->TailFrameDeleteInstrument(pInstrument);

		// ����β��ʱ�̲�ѯ֡
		SendTailTimeFrame();
	}
}

// ����β��
BOOL CTailFrameThread::ParseTailFrame(void)
{
	byte	usCommand = 0;

	// ����SN��
	memcpy(&usCommand, &m_pTailFrameData[33], 1);
	if (usCommand != 0x01)
	{
		return FALSE;
	}
	memcpy(&m_uiSN, &m_pTailFrameData[34], 4);
	
	return TRUE;
}

// ����������β��ʱ�̲�ѯ֡
void CTailFrameThread::SendTailTimeFrame(void)
{
	CInstrument* pInstrument = NULL;	// ����	
	POSITION pos = NULL;	// λ��	
	unsigned int uiKey;	// ������

	// �õ���������ʼ����λ��
	pos = m_oInstrumentList->m_oInstrumentMap.GetStartPosition();
	// ��ǰλ��������
	while(NULL != pos)
	{
		pInstrument = NULL;
		// �õ�����
		m_oInstrumentList->m_oInstrumentMap.GetNextAssoc(pos, uiKey, pInstrument);
		if(NULL != pInstrument)	// �õ�����
		{
			if (pInstrument->m_bIPSetOK == true)
			{
				// ��������β��ʱ�̲�ѯ֡
				MakeTailTimeFrameData(pInstrument);
				// ��������β��ʱ�̲�ѯ֡
				SendTailTimeFrameToSocket();
				m_uiSendTailTimeFrameCount++;
				pInstrument->m_bSendTailTimeFrame = true;
			}
		}
	}
}

// ����β��ʱ�̲�ѯ֡
void CTailFrameThread::MakeTailTimeFrameData(CInstrument* pInstrument)
{
	unsigned int uiIPSource =	0;
	unsigned int uiIPAim	=	0;
	unsigned int usPortAim	=	0;
	unsigned int usCommand	=	0;
	m_pTailTimeSendData[0] = 0x11;
	m_pTailTimeSendData[1] = 0x22;
	m_pTailTimeSendData[2] = 0x33;
	m_pTailTimeSendData[3] = 0x44;
	m_pTailTimeSendData[4] = 0x00;
	m_pTailTimeSendData[5] = 0x00;
	m_pTailTimeSendData[6] = 0x00;
	m_pTailTimeSendData[7] = 0x00;
	m_pTailTimeSendData[8] = 0x00;
	m_pTailTimeSendData[9] = 0x00;
	m_pTailTimeSendData[10] = 0x00;
	m_pTailTimeSendData[11] = 0x00;
	m_pTailTimeSendData[12] = 0x00;
	m_pTailTimeSendData[13] = 0x00;
	m_pTailTimeSendData[14] = 0x00;
	m_pTailTimeSendData[15] = 0x00;

	uiIPSource	=	inet_addr(m_csIPSource);
	uiIPAim		=	pInstrument->m_uiIPAddress;
	usPortAim	=	TailTimeFramePort;
	usCommand	=	2;
	// ԴIP��ַ
	memcpy(&m_pTailTimeSendData[16], &uiIPSource, 4);
	// Ŀ��IP��ַ
	memcpy(&m_pTailTimeSendData[20], &uiIPAim, 4);
	TRACE1("β��ʱ�̲�ѯ֡-����IP��ַ��%d\r\n", uiIPAim);
	// Ŀ��˿ں�
	memcpy(&m_pTailTimeSendData[24], &usPortAim, 2);
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_pTailTimeSendData[26], &usCommand, 2);

	int iPos = 32;
	// ������0x01��ȡ�豸SN
	m_pTailTimeSendData[iPos] = 0x01;
	iPos++;
	memset(&m_pTailTimeSendData[iPos], 0, 4);
	iPos = iPos + 4;

	// ������0x19��ȡ����ʱ��
	m_pTailTimeSendData[iPos] = 0x19;
	iPos++;
	memset(&m_pTailTimeSendData[iPos], 0, 4);
	iPos = iPos + 4;

	// ������0x04��ȡ����ϵͳʱ��
	m_pTailTimeSendData[iPos] = 0x04;
	iPos++;
	memset(&m_pTailTimeSendData[iPos], 0, 4);
	iPos = iPos + 4;

	// ��������	1-����վ
	if(1 == pInstrument->m_uiInstrumentType)
	{
		// ������0x1B  ����վ����β������ʱ��
		m_pTailTimeSendData[iPos] = 0x1B;
		iPos++;
		memset(&m_pTailTimeSendData[iPos], 0, 4);
		iPos = iPos + 4;
	}
	else
	{
		// ������0x16���ա�����ʱ�̵�λ
		m_pTailTimeSendData[iPos] = 0x16;
		iPos++;
		memset(&m_pTailTimeSendData[iPos], 0, 4);
		iPos = iPos + 4;
	}

	// ���������ֽ���
	m_pTailTimeSendData[iPos] = 0x00;

}

// ����β��ʱ�̲�ѯ֡
void CTailFrameThread::SendTailTimeFrameToSocket(void)
{
	// ����֡
	int iCount = m_TailTimeFrameSocket.SendTo(m_pTailTimeSendData, 128, m_uiSendPort, IPBroadcastAddr);
}

// ����β��ʱ�̲�ѯ����
void CTailFrameThread::ProcTailTimeFrameOne(void)
{
	if (PraseTailTimeFrame() == FALSE)
	{
		return;
	}
	if (m_uiRecTailTimeFrameCount == m_uiSendTailTimeFrameCount)
	{
		m_uiSendTailTimeFrameCount = 0;
		m_uiRecTailTimeFrameCount = 0;
		// ���ʱͳ
		TimeDelayCalculation();
	}
}

// ����β��ʱ�̲�ѯ֡
BOOL CTailFrameThread::PraseTailTimeFrame(void)
{
	byte	usCommand = 0;
	int iPos = 28;
	// ����SN��
	memcpy(&usCommand, &m_pTailTimeRecData[iPos], 1);
	iPos++;
	if (usCommand != 0x01)
	{
		return FALSE;
	}
	memcpy(&m_uiSN, &m_pTailTimeRecData[iPos], 4);
	iPos = iPos + 4;

	// ������ָ��Ϊ��
	CInstrument* pInstrument = NULL;
	// �������������ҵ�������,�õ�������ָ��
	if (TRUE == m_oInstrumentList->GetInstrumentFromMap(m_uiSN, pInstrument))
	{	
		// û�й���β����ֻ�ж�ʧ֡
		// ����ǹ��ڵ�β��ʱ�̲�ѯ֡
// 		if (pInstrument->m_bTailTimeExpired == true)
// 		{
// 			pInstrument->m_bTailTimeExpired = false;
// 			return FALSE;
//		}
		// ��������ʱ��
		memcpy(&usCommand, &m_pTailTimeRecData[iPos], 1);
		iPos++;
		if (usCommand != 0x19)
		{
			return FALSE;
		}
		memcpy(&m_uiNetTime, &m_pTailTimeRecData[iPos], 4);
		iPos = iPos + 4;

		// ��������ϵͳʱ��
		memcpy(&usCommand, &m_pTailTimeRecData[iPos], 1);
		iPos++;
		if (usCommand != 0x04)
		{
			return FALSE;
		}
		memcpy(&m_uiSystemTime, &m_pTailTimeRecData[iPos], 4);
		iPos = iPos + 4;

		// ��������	1-����վ
		if(1 == pInstrument->m_uiInstrumentType)
		{
			// ������0x1B  ����վ����β������ʱ��
			memcpy(&usCommand, &m_pTailTimeRecData[iPos], 1);
			iPos++;
			if (usCommand != 0x1B)
			{
				return FALSE;
			}
			memcpy(&m_usTailRecTime, &m_pTailTimeRecData[iPos], 2);
			iPos = iPos + 2;
			memcpy(&m_usTailSendTime, &m_pTailTimeRecData[iPos], 2);
			iPos = iPos + 2;
		}
		else
		{
			// ������0x16���ա�����ʱ�̵�λ
			memcpy(&usCommand, &m_pTailTimeRecData[iPos], 1);
			iPos++;
			if (usCommand != 0x16)
			{
				return FALSE;
			}
			memcpy(&m_usTailRecTime, &m_pTailTimeRecData[iPos], 2);
			iPos = iPos + 2;
			memcpy(&m_usTailSendTime, &m_pTailTimeRecData[iPos], 2);
			iPos = iPos + 2;
		}
		pInstrument->m_uiNetTime = m_uiNetTime;
		pInstrument->m_uiSystemTime = m_uiSystemTime;
		// ��14λΪ֡��ʱ��
		pInstrument->m_usTailRecTime = m_usTailRecTime & 0x3fff;
		pInstrument->m_usTailSendTime = m_usTailSendTime & 0x3fff;
		pInstrument->m_bTailTimeReturnOK = true;
		m_uiRecTailTimeFrameCount++;
	}
	else
	{
		return FALSE;
	}
	
	return TRUE;
}

// ʱ��ͬ������
void CTailFrameThread::TimeDelayCalculation(void)
{
	CInstrument* pInstrument = NULL;	// ����	
	POSITION pos = NULL;	// λ��	
	unsigned int uiKey;	// ������
	unsigned int uiInstrumentCount = 0;
	unsigned short usSendTailTime = 0;
	unsigned short usRecTailTime = 0;
	unsigned int uiNetTime = 0;
	// �õ���������ʼ����λ��
	pos = m_oInstrumentList->m_oInstrumentMap.GetStartPosition();
	// ��ǰλ��������
	while(NULL != pos)
	{
		pInstrument = NULL;
		// �õ�����
		m_oInstrumentList->m_oInstrumentMap.GetNextAssoc(pos, uiKey, pInstrument);
		if(NULL != pInstrument)	// �õ�����
		{
			if (pInstrument->m_bTailTimeReturnOK == true)
			{
				m_oInstrumentLocationMap.SetAt(pInstrument->m_uiLocation, pInstrument);
			}
			pInstrument->m_bSendTailTimeFrame = false;
			pInstrument->m_bTailTimeReturnOK = false;
		}
	}
	uiInstrumentCount = m_oInstrumentLocationMap.GetCount();
	// ֻ�н���վ������ʱ������
	if (uiInstrumentCount == 1)
	{
		m_oInstrumentLocationMap.RemoveAll();
		return;
	}
	// ��¼����վ���մ��߷���β���Ľ���ʱ��
	m_oInstrumentLocationMap.Lookup(0, pInstrument);
	usRecTailTime = pInstrument->m_usTailRecTime;
	uiNetTime = pInstrument->m_uiNetTime;
	m_iTimeLow = 0;
	m_iTimeHigh = 0;
	for (unsigned int i=1; i<uiInstrumentCount;i++)
	{
		if (m_oInstrumentLocationMap.Lookup(i, pInstrument) == FALSE)
		{
			break;
		}
		// ��λ������Ҳֻ������һ�Σ��Ͼ��ǲ�ѯ֡�����ϴ��������������λ������׼
		if (m_uiDelayTimeCount == 0)
		{
			m_iTimeHigh = m_iTimeHigh + uiNetTime - pInstrument->m_uiNetTime;
		}
		else
		{
			m_iTimeHigh = 0;
		}
		m_iTimeHigh = 0;
//		m_iTimeLow = m_iTimeLow - (usRecTailTime - pInstrument->m_usTailSendTime)/2 - 10;
		int temp = usRecTailTime - pInstrument->m_usTailSendTime;
		if (temp<0)
		{
			temp += 0x4000;
		}
		// �ž����㷨
		m_iTimeLow = m_iTimeLow -(temp- 4112);
		// �����㷨
//		m_iTimeLow = m_iTimeLow - temp/2 - 10;
		usRecTailTime = pInstrument->m_usTailRecTime;
		// ����ʱͳ��������֡
		MakeTimeDelayFrameData(pInstrument);
		// ����ʱͳ��������֡
		SendTimeDelayFrameData();
	}
	m_oInstrumentLocationMap.RemoveAll();
	m_uiDelayTimeCount++; 
}

// ����ʱͳ��������֡
void CTailFrameThread::MakeTimeDelayFrameData(CInstrument* pInstrument)
{
	unsigned int uiIPSource =	0;
	unsigned int uiIPAim	=	0;
	unsigned int usPortAim	=	0;
	unsigned int usCommand	=	0;
	m_pTimeDelayData[0] = 0x11;
	m_pTimeDelayData[1] = 0x22;
	m_pTimeDelayData[2] = 0x33;
	m_pTimeDelayData[3] = 0x44;
	m_pTimeDelayData[4] = 0x00;
	m_pTimeDelayData[5] = 0x00;
	m_pTimeDelayData[6] = 0x00;
	m_pTimeDelayData[7] = 0x00;
	m_pTimeDelayData[8] = 0x00;
	m_pTimeDelayData[9] = 0x00;
	m_pTimeDelayData[10] = 0x00;
	m_pTimeDelayData[11] = 0x00;
	m_pTimeDelayData[12] = 0x00;
	m_pTimeDelayData[13] = 0x00;
	m_pTimeDelayData[14] = 0x00;
	m_pTimeDelayData[15] = 0x00;

	uiIPSource	=	inet_addr(m_csIPSource);
	uiIPAim		=	pInstrument->m_uiIPAddress;
	usPortAim	=	TimeSetPort;
	usCommand	=	1;
	// ԴIP��ַ
	memcpy(&m_pTimeDelayData[16], &uiIPSource, 4);
	// Ŀ��IP��ַ
	memcpy(&m_pTimeDelayData[20], &uiIPAim, 4);
	TRACE1("β��ʱ�̲�ѯ֡-����IP��ַ��%d\r\n", uiIPAim);
	// Ŀ��˿ں�
	memcpy(&m_pTimeDelayData[24], &usPortAim, 2);
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_pTimeDelayData[26], &usCommand, 2);

	int iPos = 32;
	// ������0x05����ʱ�Ӹ�λ
	m_pTimeDelayData[iPos] = 0x05;
	iPos++;
	memcpy(&m_pTimeDelayData[iPos], &m_iTimeHigh, 4);
	iPos = iPos + 4;

	// ������0x06����ʱ�ӵ�λ
	m_pTimeDelayData[iPos] = 0x06;
	iPos++;
	memcpy(&m_pTimeDelayData[iPos], &m_iTimeLow, 4);
	iPos = iPos + 4;

	// ���������ֽ���
	m_pTimeDelayData[iPos] = 0x00;
}

// ����ʱͳ��������֡
void CTailFrameThread::SendTimeDelayFrameData(void)
{
	int iCount = m_TailTimeFrameSocket.SendTo(m_pTimeDelayData, 128, m_uiSendPort, IPBroadcastAddr);
}

// ��
void CTailFrameThread::OnOpen(void)
{
	m_TailFrameSocket.Close();
	m_TailTimeFrameSocket.Close();
	BOOL flag = FALSE; 
	flag =  m_TailFrameSocket.Create(TailFramePort,SOCK_DGRAM);
	if (flag == FALSE)
	{
		AfxMessageBox(_T("���ն˿ڴ���ʧ�ܣ�"));
	}

	BOOL bReturn = FALSE;
	// ��������˿ڣ����շ�������Ӧ��֡��create����д�����������IP��ַ����չ̶�IP��ַ���͵�֡����д��ȫ������
	bReturn = m_TailTimeFrameSocket.Create(TailTimeFramePort, SOCK_DGRAM);
	if (bReturn == FALSE)
	{
		AfxMessageBox(_T("����㲥�˿ڴ���ʧ�ܣ�"));
	}

	//���ù㲥ģʽ
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	m_TailTimeFrameSocket.SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);
}

// ֹͣ
void CTailFrameThread::OnStop(void)
{
//	m_TailFrameSocket.ShutDown(2);
//	m_TailTimeFrameSocket.ShutDown(2);
	m_TailFrameSocket.Close();
	m_TailTimeFrameSocket.Close();
}
