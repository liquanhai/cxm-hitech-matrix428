// HeadFrameThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "HeadFrameThread.h"
#include "Parameter.h"

// CHeadFrameThread

IMPLEMENT_DYNCREATE(CHeadFrameThread, CWinThread)

CHeadFrameThread::CHeadFrameThread()
: m_bclose(false)
, m_uiSN(0)
, m_uiHeadFrameTime(0)
, m_uiRoutAddress(0)
, m_uiIPAddress(0)
, m_csIPSource(_T(""))
, m_uiSendPort(0)
, m_pwnd(NULL)
{
}

CHeadFrameThread::~CHeadFrameThread()
{
}

BOOL CHeadFrameThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CHeadFrameThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CHeadFrameThread, CWinThread)
END_MESSAGE_MAP()


// ��ʼ��

void CHeadFrameThread::OnInit(void)
{
	m_hHeadFrameThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	::ResetEvent(m_hHeadFrameThreadClose);	// �����¼�����Ϊ���ź�״̬
}
// �̺߳�����Run��ִ��
int CHeadFrameThread::Run()
{
	DWORD dwHeadFrameCount = 0;
	int iHeadcount = 0;
	DWORD dwIPSetReturnFrameCount = 0;
	int iIPSetReturncount = 0;
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		if(m_bclose == true)
		{
			break;
		}
		// �õ�������ջ����������ֽ���
		m_HeadFrameSocket.IOCtl(FIONREAD, &dwHeadFrameCount);
		dwHeadFrameCount = dwHeadFrameCount/256;
		if(0 != dwHeadFrameCount)	
		{
			for(unsigned int i = 0; i < dwHeadFrameCount; i++)	// ���μ��ÿ������IP����Ӧ��֡
			{
				iHeadcount = m_HeadFrameSocket.Receive(m_pHeadFrameData,256);
				if (iHeadcount == 256)
				{
					// �����װ�����
					ProcHeadFrameOne();
				}
				else
				{
					break;
				}
			}
		}

		// �õ�������ջ����������ֽ���
		m_IPSetSocket.IOCtl(FIONREAD, &dwIPSetReturnFrameCount);
		dwIPSetReturnFrameCount = dwIPSetReturnFrameCount/256;
		if(0 != dwIPSetReturnFrameCount)	
		{
			for(unsigned int i = 0; i < dwIPSetReturnFrameCount; i++)	// ���μ��ÿ������IP����Ӧ��֡
			{
				iIPSetReturncount = m_IPSetSocket.Receive(m_pIPSetReturnFrameData,256);
				if (iIPSetReturncount == 256)
				{
					// ����IP��ַ����Ӧ��֡����
					ProcIPSetReturnFrameOne();
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
	::SetEvent(m_hHeadFrameThreadClose);	// �����¼�����Ϊ���ź�״̬
	// ����
	return CWinThread::Run();
}


// �رղ������߳�
void CHeadFrameThread::OnClose(void)
{
//	m_HeadFrameSocket.ShutDown(2);
//	m_IPSetSocket.ShutDown(2);
	m_HeadFrameSocket.Close();
	m_IPSetSocket.Close();
	m_bclose = true;
}

// ���������װ�
void CHeadFrameThread::ProcHeadFrameOne()
{
	if (ParseHeadFrame() == FALSE)
	{
		return;
	}
	// ������ָ��Ϊ��
	CInstrument* pInstrument = NULL;
	// �������������û�ҵ�������
	if (TRUE != m_oInstrumentList->IfIndexExistInMap(m_uiSN))
	{
		// �õ�������
		pInstrument = m_oInstrumentList->GetFreeInstrument();

		// ������������SN
		pInstrument->m_uiSN = m_uiSN;
		// ������������·��IP��ַ
		pInstrument->m_uiRoutAddress = m_uiRoutAddress;

		if (m_uiRoutAddress == 0)
		{
			// ��������������������
			pInstrument->m_uiInstrumentType = 1;
		}
		else
		{
			pInstrument->m_uiInstrumentType = 3;
		}
		// �������������װ�ʱ��
		pInstrument->m_uiHeadFrameTime = m_uiHeadFrameTime;
		// �װ���������һ
		pInstrument->m_iHeadFrameCount++;

		// ����������SN������
		m_oInstrumentList->AddInstrumentToMap(pInstrument->m_uiSN, pInstrument);
	}
	else
	{
		// �������������ҵ�������,�õ�������ָ��
		if (TRUE == m_oInstrumentList->GetInstrumentFromMap(m_uiSN, pInstrument))
		{
			// �װ���������һ
			pInstrument->m_iHeadFrameCount++;
		}
	}
	
	// ��������IP��ַ������ǽ���վ��������·�ɵ�ַ
	if (pInstrument->m_iHeadFrameCount == HeadFrameCount)
	{
		pInstrument->m_iHeadFrameCount = 0;
		MakeIPSetFrame(pInstrument);
		SendIPSetFrame();
	}
}

// �����װ�
BOOL CHeadFrameThread::ParseHeadFrame(void)
{
	byte	usCommand = 0;

	// ����SN��
	memcpy(&usCommand, &m_pHeadFrameData[28], 1);
	if (usCommand != 0x01)
	{
		return FALSE;
	}
	memcpy(&m_uiSN, &m_pHeadFrameData[29], 4);
	// �����װ�ʱ��
	memcpy(&usCommand, &m_pHeadFrameData[33], 1);
	if (usCommand != 0x02)
	{
		return FALSE;
	}
	memcpy(&m_uiHeadFrameTime, &m_pHeadFrameData[34], 4);
	// ·��IP��ַ
	memcpy(&usCommand, &m_pHeadFrameData[38], 1);
	if (usCommand == 0x00)
	{
		m_uiRoutAddress = 0;
	}
	else if (usCommand == 0x3F)
	{
		memcpy(&m_uiRoutAddress, &m_pHeadFrameData[39], 4);
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

// ����IP��ַ����֡
void CHeadFrameThread::MakeIPSetFrame(CInstrument* pInstrument)
{
	unsigned int	uiIPSource;
	unsigned int	uiIPAim;
	unsigned short	usPortAim;
	unsigned short	usCommand;
	unsigned int	uiRoutIPTop;
	unsigned int	uiRoutIPDown;
	unsigned int	uiRoutIPLeft;
	unsigned int	uiRoutIPRight;
	unsigned int	uiADCBroadcastPort;
	m_pIPSetFrameData[0] = 0x11;
	m_pIPSetFrameData[1] = 0x22;
	m_pIPSetFrameData[2] = 0x33;
	m_pIPSetFrameData[3] = 0x44;
	m_pIPSetFrameData[4] = 0x00;
	m_pIPSetFrameData[5] = 0x00;
	m_pIPSetFrameData[6] = 0x00;
	m_pIPSetFrameData[7] = 0x00;
	m_pIPSetFrameData[8] = 0x00;
	m_pIPSetFrameData[9] = 0x00;
	m_pIPSetFrameData[10] = 0x00;
	m_pIPSetFrameData[11] = 0x00;
	m_pIPSetFrameData[12] = 0x00;
	m_pIPSetFrameData[13] = 0x00;
	m_pIPSetFrameData[14] = 0x00;
	m_pIPSetFrameData[15] = 0x00;

	// ԴIP��ַ

	uiIPSource	=	inet_addr(m_csIPSource);
	// Ŀ��IP��ַ
	uiIPAim		=	0xFFFFFFFF;
	// Ŀ��˿ں�
	usPortAim	=	IPSetPort;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	usCommand	=	1;

	uiRoutIPTop		=	5;
	uiRoutIPDown	=	6;
	uiRoutIPLeft	=	7;
	uiRoutIPRight	=	8;
	// ԴIP��ַ
	memcpy(&m_pIPSetFrameData[16], &uiIPSource, 4);
	// Ŀ��IP��ַ
	memcpy(&m_pIPSetFrameData[20], &uiIPAim, 4);
	// Ŀ��˿ں�
	memcpy(&m_pIPSetFrameData[24], &usPortAim, 2);
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_pIPSetFrameData[26], &usCommand, 2);

	int iPos = 32;
	// ������������������
	m_pIPSetFrameData[iPos] = 0x01;
	iPos++;
	// ����SN��
	memcpy(&m_pIPSetFrameData[iPos], &m_uiSN, 4);
	iPos = iPos + 4;

	// ��������վ��IP��ַ����������
	m_pIPSetFrameData[iPos] = 0x03;
	iPos++;
	// ��������IP
	memcpy(&m_pIPSetFrameData[iPos], &pInstrument->m_uiIPAddress, 4);
	iPos = iPos + 4;
	if(1 != pInstrument->m_uiInstrumentType)	// �������� 1-����վ��2-��Դվ��3-�ɼ�վ
	{
		// ���ù㲥�˿�
		m_pIPSetFrameData[iPos] = 0x0A;
		iPos++;
		// �㲥����˿�6666
		uiADCBroadcastPort = ADCSetBroadcastPort;     
		memcpy(&m_pIPSetFrameData[iPos], &uiADCBroadcastPort, 4);
		iPos = iPos + 4;
		// ���������ֽ���
		m_pIPSetFrameData[iPos] = 0x00;
	}
	else	// ��Ҫ����·��IP��ַ
	{
		// ��������վ��IP��ַ����������
		m_pIPSetFrameData[iPos] = 0x1F;
		iPos++;
		// ·��IP��ַ��·�ɷ��� 1-��
		memcpy(&m_pIPSetFrameData[iPos], &uiRoutIPTop, 4);
		iPos = iPos + 4;
		// ��������վ��IP��ַ����������
		m_pIPSetFrameData[iPos] = 0x1F;
		iPos++;
		// ·��IP��ַ��·�ɷ��� 2-��
		memcpy(&m_pIPSetFrameData[iPos], &uiRoutIPDown, 4);
		iPos = iPos + 4;
		// ��������վ��IP��ַ����������
		m_pIPSetFrameData[iPos] = 0x1F;
		iPos++;
		// ·��IP��ַ��·�ɷ��� 3-��
		memcpy(&m_pIPSetFrameData[iPos], &uiRoutIPLeft, 4);
		iPos = iPos + 4;
		// ��������վ��IP��ַ����������
		m_pIPSetFrameData[iPos] = 0x1F;
		iPos++;
		// ·��IP��ַ��·�ɷ��� 4-��
		memcpy(&m_pIPSetFrameData[iPos], &uiRoutIPRight, 4);
		iPos = iPos + 4;
		// ���������ֽ���
		m_pIPSetFrameData[iPos] = 0x00;
	}
}

// ����IP��ַ����֡
void CHeadFrameThread::SendIPSetFrame(void)
{
	// ����֡
	// ��Ҫ�����㲥�˿�
	int iCount = m_IPSetSocket.SendTo(m_pIPSetFrameData, 128, m_uiSendPort, IPBroadcastAddr);
}

// ����IP��ַ����Ӧ��֡����
void CHeadFrameThread::ProcIPSetReturnFrameOne(void)
{
	if (ParseIPSetReturnFrame() == FALSE)
	{
		return;
	}
	// �����������ҵ�������
	if (TRUE == m_oInstrumentList->IfIndexExistInMap(m_uiSN))
	{
		// �����������ҵ�������,�õ�������ָ��
		CInstrument* pInstrument = NULL;
		if (TRUE == m_oInstrumentList->GetInstrumentFromMap(m_uiSN, pInstrument))
		{
			if (m_uiIPAddress == pInstrument->m_uiIPAddress)
			{
				pInstrument->m_bIPSetOK = true;
				CStatic* icon;
				if(m_uiIPAddress == 111)
				{
					icon =(CStatic*)m_pwnd->GetDlgItem(IDC_STATIC_INSTRUMENT1);
					icon->SetIcon(m_iconConnected);
				}
				else if(m_uiIPAddress == 101)
				{
					icon =(CStatic*)m_pwnd->GetDlgItem(IDC_STATIC_INSTRUMENT2);
					icon->SetIcon(m_iconConnected);
				}
				else if(m_uiIPAddress == 91)
				{
					icon =(CStatic*)m_pwnd->GetDlgItem(IDC_STATIC_INSTRUMENT3);
					icon->SetIcon(m_iconConnected);
				}
				else if(m_uiIPAddress == 81)
				{
					icon =(CStatic*)m_pwnd->GetDlgItem(IDC_STATIC_INSTRUMENT4);
					icon->SetIcon(m_iconConnected);
				}
			}
		}
	}

}

// ����IP��ַ����Ӧ��֡
BOOL CHeadFrameThread::ParseIPSetReturnFrame(void)
{
	byte	usCommand = 0;

	// ����SN��
	memcpy(&usCommand, &m_pIPSetReturnFrameData[28], 1);
	if (usCommand != 0x01)
	{
		return FALSE;
	}
	memcpy(&m_uiSN, &m_pIPSetReturnFrameData[29], 4);
	// ���������õ�IP��ַ
	memcpy(&usCommand, &m_pIPSetReturnFrameData[33], 1);
	if (usCommand != 0x03)
	{
		return FALSE;
	}
	memcpy(&m_uiIPAddress, &m_pIPSetReturnFrameData[34], 4);
	return TRUE;
}

// ��
void CHeadFrameThread::OnOpen(void)
{
	m_HeadFrameSocket.Close();
	m_IPSetSocket.Close();
	BOOL flag = FALSE; 
	flag =  m_HeadFrameSocket.Create(HeadFramePort,SOCK_DGRAM);
	if (flag == FALSE)
	{
		AfxMessageBox(_T("���ն˿ڴ���ʧ�ܣ�"));
	}
	BOOL bReturn = FALSE;
	// ��������˿ڣ����շ�������Ӧ��֡��create����д�����������IP��ַ����չ̶�IP��ַ���͵�֡����д��ȫ������
	bReturn = m_IPSetSocket.Create(IPSetPort, SOCK_DGRAM);
	if (bReturn == FALSE)
	{
		AfxMessageBox(_T("����㲥�˿ڴ���ʧ�ܣ�"));
	}

	//���ù㲥ģʽ
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	m_IPSetSocket.SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);
}

// ֹͣ
void CHeadFrameThread::OnStop(void)
{
//	m_HeadFrameSocket.ShutDown(2);
//	m_IPSetSocket.ShutDown(2);
	m_HeadFrameSocket.Close();
	m_IPSetSocket.Close();
}