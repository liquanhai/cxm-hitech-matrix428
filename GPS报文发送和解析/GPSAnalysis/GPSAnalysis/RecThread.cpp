// RecThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GPSAnalysis.h"
#include "RecThread.h"


// CRecThread

IMPLEMENT_DYNCREATE(CRecThread, CWinThread)

CRecThread::CRecThread()
: m_bclose(false)
, m_csHeadFrame(_T(""))
, m_dUTCTime(0)
, m_csStatus(_T(""))
, m_dLatitudeValue(0)
, m_csLatitude(_T(""))
, m_dLongitudeValue(0)
, m_csLongitude(_T(""))
, m_dSpeed(0)
, m_dAzimuth(0)
, m_csUTCData(_T(""))
, m_dMagneticdeclination(0)
, m_csMagneticdeclination_Direction(_T(""))
, m_csMode(_T(""))
, m_cCheckSum(0)
{
}

CRecThread::~CRecThread()
{
}

BOOL CRecThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CRecThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CRecThread, CWinThread)
END_MESSAGE_MAP()


// CRecThread ��Ϣ�������
// �̺߳�����Run��ִ��
int CRecThread::Run()
{
	DWORD dwFrameCount = 0;
	int iCount = 0;
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		if(m_bclose == true)
		{
			break;
		}
		// �õ�������ջ����������ֽ���
		m_Socket.IOCtl(FIONREAD, &dwFrameCount);
		dwFrameCount = dwFrameCount/256;
		if(0 != dwFrameCount)	
		{
			for(unsigned int i = 0; i < dwFrameCount; i++)	// ���μ��ÿ������IP����Ӧ��֡
			{
				iCount = m_Socket.Receive(m_pRecFrameData,256);
				if (iCount == 256)
				{
					// ����GPS֡����
					ProcGPSFrameOne();
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
		Sleep(50);
	}
	::SetEvent(m_hRecThreadClose);	// �����¼�����Ϊ���ź�״̬
	// ����
	return CWinThread::Run();
}
// �̳߳�ʼ��
void CRecThread::Init(void)
{
	// ����Socket�˿�
	BOOL flag = FALSE; 
	flag =  m_Socket.Create(RecGPSPort,SOCK_DGRAM);
	if (flag == FALSE)
	{
		AfxMessageBox(_T("���ն˿ڴ���ʧ�ܣ�"));
	}
	m_hRecThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	::ResetEvent(m_hRecThreadClose);	// �����¼�����Ϊ���ź�״̬
}

// �̹߳ر�
void CRecThread::OnClose(void)
{
	m_Socket.Close();
	m_bclose = true;
}

// ������GPS֡
void CRecThread::ProcGPSFrameOne(void)
{
	DWORD dwHeadFrame = 0;
	memcpy(&dwHeadFrame, &m_pRecFrameData[0], 4);
	if (dwHeadFrame != 0x44332211)
	{
		return;
	}
	OnReset();
	byte checksum = 0;
	CString str = _T("");
	CString strtemp = _T("");
	CWnd* pWnd = AfxGetMainWnd();
	int iPos  = 0;
	int iPos0 = 0;
	int iPos1 = 0;
	int iPos2 = 0;
	str = &m_pRecFrameData[28];
	iPos = str.Find(_T("\r\n"), 0);
	str = str.Mid(0, iPos);
	// У��ͣ�$��*֮�������ַ������У��ͣ����ֽ���������㣬�õ�У��ͺ���ת��16���Ƹ�ʽ��ASCII�ַ���
	for (int i=0; i<(str.GetLength()-4); i++)
	{
		checksum ^= m_pRecFrameData[29+i];
	}
	iPos0 = str.Find(_T(","), 0);
	strtemp = str.Mid(0, iPos0);
	m_csHeadFrame = strtemp;
	pWnd->GetDlgItem(IDC_EDIT_HEADFRAME)->SetWindowText(strtemp);
	if (m_csHeadFrame == _T("$GPRMC"))
	{
		// UTCʱ��
		iPos1 = str.Find(_T(","), iPos0+1);
		strtemp = str.Mid(iPos0+1, iPos1-iPos0-1);
		m_dUTCTime = atof(strtemp);
		pWnd->GetDlgItem(IDC_EDIT_UTCTIME)->SetWindowText(strtemp);

		// ״̬
		iPos2 = str.Find(_T(","), iPos1+1);
		strtemp = str.Mid(iPos1+1, iPos2-iPos1-1);
		m_csStatus = strtemp;
		pWnd->GetDlgItem(IDC_EDIT_STATUS)->SetWindowText(strtemp);
		
		// γ��ֵ
		iPos0 = str.Find(_T(","), iPos2+1);
		strtemp = str.Mid(iPos2+1, iPos0-iPos2-1);
		m_dLatitudeValue = atof(strtemp);
		pWnd->GetDlgItem(IDC_EDIT_LATITUDEVALUE)->SetWindowText(strtemp);

		// γ��
		iPos1 = str.Find(_T(","), iPos0+1);
		strtemp = str.Mid(iPos0+1, iPos1-iPos0-1);
		m_csLatitude = strtemp;
		pWnd->GetDlgItem(IDC_EDIT_LATITUDE)->SetWindowText(strtemp);

		// ����ֵ
		iPos2 = str.Find(_T(","), iPos1+1);
		strtemp = str.Mid(iPos1+1, iPos2-iPos1-1);
		m_dLongitudeValue = atof(strtemp);
		pWnd->GetDlgItem(IDC_EDIT_LONGITUDEVALUE)->SetWindowText(strtemp);

		// ����
		iPos0 = str.Find(_T(","), iPos2+1);
		strtemp = str.Mid(iPos2+1, iPos0-iPos2-1);
		m_csLongitude = strtemp;
		pWnd->GetDlgItem(IDC_EDIT_LONGITUDE)->SetWindowText(strtemp);
		
		// �ٶ�
		iPos1 = str.Find(_T(","), iPos0+1);
		strtemp = str.Mid(iPos0+1, iPos1-iPos0-1);
		m_dSpeed = atof(strtemp);
		pWnd->GetDlgItem(IDC_EDIT_SPEED)->SetWindowText(strtemp);

		// ��λ��
		iPos2 = str.Find(_T(","), iPos1+1);
		strtemp = str.Mid(iPos1+1, iPos2-iPos1-1);
		m_dAzimuth = atof(strtemp);
		pWnd->GetDlgItem(IDC_EDIT_AZIMUTH)->SetWindowText(strtemp);

		// UTC����
		iPos0 = str.Find(_T(","), iPos2+1);
		strtemp = str.Mid(iPos2+1, iPos0-iPos2-1);
		m_csUTCData = strtemp;
		pWnd->GetDlgItem(IDC_EDIT_UTCDATA)->SetWindowText(strtemp);

		// ��ƫ��
		iPos1 = str.Find(_T(","), iPos0+1);
		strtemp = str.Mid(iPos0+1, iPos1-iPos0-1);
		m_dMagneticdeclination = atof(strtemp);
		pWnd->GetDlgItem(IDC_EDIT_MAGNETICDECLINATION)->SetWindowText(strtemp);

		// ��ƫ�Ƿ���
		iPos2 = str.Find(_T(","), iPos1+1);
		strtemp = str.Mid(iPos1+1, iPos2-iPos1-1);
		m_csMagneticdeclination_Direction = strtemp;
		pWnd->GetDlgItem(IDC_EDIT_MAGNETICDECLINATION_DIRECTION)->SetWindowText(strtemp);

		// ģʽָʾ
		iPos0 = str.Find(_T("*"), iPos2+1);
		strtemp = str.Mid(iPos2+1, iPos0-iPos2-1);
		m_csMode = strtemp;
		pWnd->GetDlgItem(IDC_EDIT_MODE)->SetWindowText(strtemp);

		// У���
		strtemp = str.Mid(iPos0+1, 2);
		sscanf_s(strtemp, _T("%x"), &m_cCheckSum);
		if (checksum == m_cCheckSum)
		{
			pWnd->GetDlgItem(IDC_EDIT_CHECKSUM)->SetWindowText(strtemp);
		}
		else
		{
			OnReset();
		}
	}
	if (m_csHeadFrame == _T("$GPGLL"))
	{
		// γ��ֵ
		iPos1 = str.Find(_T(","), iPos0+1);
		strtemp = str.Mid(iPos0+1, iPos1-iPos0-1);
		m_dLatitudeValue = atof(strtemp);
		pWnd->GetDlgItem(IDC_EDIT_LATITUDEVALUE)->SetWindowText(strtemp);

		// γ��
		iPos2 = str.Find(_T(","), iPos1+1);
		strtemp = str.Mid(iPos1+1, iPos2-iPos1-1);
		m_csLatitude = strtemp;
		pWnd->GetDlgItem(IDC_EDIT_LATITUDE)->SetWindowText(strtemp);

		// ����ֵ
		iPos0 = str.Find(_T(","), iPos2+1);
		strtemp = str.Mid(iPos2+1, iPos0-iPos2-1);
		m_dLongitudeValue = atof(strtemp);
		pWnd->GetDlgItem(IDC_EDIT_LONGITUDEVALUE)->SetWindowText(strtemp);

		// ����
		iPos1 = str.Find(_T(","), iPos0+1);
		strtemp = str.Mid(iPos0+1, iPos1-iPos0-1);
		m_csLongitude = strtemp;
		pWnd->GetDlgItem(IDC_EDIT_LONGITUDE)->SetWindowText(strtemp);

		// UTCʱ��
		iPos2 = str.Find(_T(","), iPos1+1);
		strtemp = str.Mid(iPos1+1, iPos2-iPos1-1);
		m_dUTCTime = atof(strtemp);
		pWnd->GetDlgItem(IDC_EDIT_UTCTIME)->SetWindowText(strtemp);

		// ״̬
		iPos0 = str.Find(_T("*"), iPos2+1);
		strtemp = str.Mid(iPos2+1, iPos0-iPos2-1);
		m_csStatus = strtemp;
		pWnd->GetDlgItem(IDC_EDIT_STATUS)->SetWindowText(strtemp);

		// У���
		strtemp = str.Mid(iPos0+1, 2);
		sscanf_s(strtemp, _T("%x"), &m_cCheckSum);
		if (checksum == m_cCheckSum)
		{
			pWnd->GetDlgItem(IDC_EDIT_CHECKSUM)->SetWindowText(strtemp);
		}
		else
		{
			OnReset();
		}
	}
}

// ����
void CRecThread::OnReset(void)
{
	m_csHeadFrame = _T("");
	m_dUTCTime = 0.0;
	m_csStatus = _T("");
	m_dLatitudeValue = 0;
	m_csLatitude = _T("");
	m_dLongitudeValue = 0;
	m_csLongitude = _T("");
	m_dSpeed = 0;
	m_dAzimuth = 0;
	m_csUTCData = _T("");
	m_dMagneticdeclination = 0;
	m_csMagneticdeclination_Direction = _T("");
	m_csMode = _T("");
	m_cCheckSum = 0;

	CString strtemp = _T("");
	CWnd* pWnd = AfxGetMainWnd();
	// ֡ͷ
	pWnd->GetDlgItem(IDC_EDIT_HEADFRAME)->SetWindowText(strtemp);

	// UTCʱ��
	pWnd->GetDlgItem(IDC_EDIT_UTCTIME)->SetWindowText(strtemp);

	// ״̬
	pWnd->GetDlgItem(IDC_EDIT_STATUS)->SetWindowText(strtemp);

	// γ��ֵ
	pWnd->GetDlgItem(IDC_EDIT_LATITUDEVALUE)->SetWindowText(strtemp);

	// γ��
	pWnd->GetDlgItem(IDC_EDIT_LATITUDE)->SetWindowText(strtemp);

	// ����ֵ
	pWnd->GetDlgItem(IDC_EDIT_LONGITUDEVALUE)->SetWindowText(strtemp);

	// ����
	pWnd->GetDlgItem(IDC_EDIT_LONGITUDE)->SetWindowText(strtemp);

	// �ٶ�
	pWnd->GetDlgItem(IDC_EDIT_SPEED)->SetWindowText(strtemp);

	// ��λ��
	pWnd->GetDlgItem(IDC_EDIT_AZIMUTH)->SetWindowText(strtemp);

	// UTC����
	pWnd->GetDlgItem(IDC_EDIT_UTCDATA)->SetWindowText(strtemp);

	// ��ƫ��
	pWnd->GetDlgItem(IDC_EDIT_MAGNETICDECLINATION)->SetWindowText(strtemp);

	// ��ƫ�Ƿ���
	pWnd->GetDlgItem(IDC_EDIT_MAGNETICDECLINATION_DIRECTION)->SetWindowText(strtemp);

	// ģʽָʾ
	pWnd->GetDlgItem(IDC_EDIT_MODE)->SetWindowText(strtemp);

	// У���
	pWnd->GetDlgItem(IDC_EDIT_CHECKSUM)->SetWindowText(strtemp);
}
