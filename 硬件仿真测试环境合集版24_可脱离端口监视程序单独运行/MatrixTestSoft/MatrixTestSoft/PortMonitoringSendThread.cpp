// PortMonitoringSendThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "PortMonitoringSendThread.h"


// CPortMonitoringSendThread

IMPLEMENT_DYNCREATE(CPortMonitoringSendThread, CWinThread)

CPortMonitoringSendThread::CPortMonitoringSendThread()
: m_usudp_count(0)
, m_iRecPort(0)
, m_iSendPort(0)
, m_csIP(_T(""))
, m_uiHeadFrameNum(0)
, m_uiIPSetReturnNum(0)
, m_uiTailFrameNum(0)
, m_uiTailTimeReturnNum(0)
, m_uiDelayTimeReturnNum(0)
, m_uiADCSetReturnNum(0)
, m_csHeadFrameShow(_T(""))
, m_csIPSetReturnShow(_T(""))
, m_csTailFrameShow(_T(""))
, m_csTailTimeReturnShow(_T(""))
, m_csDelayTimeReturnShow(_T(""))
, m_csADCDataRecShow(_T(""))
, m_uiRecFrameNum(0)
, m_pwnd(NULL)
, m_pWndTab(NULL)
, m_pSaveFile(NULL)
, m_bPortDistribution(FALSE)
, m_bclose(false)
{
}

CPortMonitoringSendThread::~CPortMonitoringSendThread()
{
}

BOOL CPortMonitoringSendThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CPortMonitoringSendThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CPortMonitoringSendThread, CWinThread)
END_MESSAGE_MAP()


// CPortMonitoringSendThread ��Ϣ�������

int CPortMonitoringSendThread::Run()
{
	// TODO: �ڴ����ר�ô����/����û���

	unsigned short uiPort = 0;
	DWORD dwFrameCount = 0;
	int icount = 0;
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		if (m_bclose == true)
		{
			break;
		}

		// �õ�������ջ����������ֽ���
		m_SendSocket.IOCtl(FIONREAD, &dwFrameCount);
		dwFrameCount = dwFrameCount/RcvFrameSize;
		if(0 != dwFrameCount)	
		{
			for(unsigned int i = 0; i < dwFrameCount; i++)	// ���μ��ÿ������IP����Ӧ��֡
			{
				ProcessMessages();
				icount = m_SendSocket.Receive(m_ucudp_buf[m_usudp_count],RcvFrameSize);
				if (icount == RcvFrameSize)
				{
					CString strTemp = _T("");
					unsigned int uiCommand = 0;
					// ����˿ڷַ�����
					memcpy(&uiPort, &m_ucudp_buf[m_usudp_count][24], 2);
					if (uiPort == HeadFramePort)
					{
						memcpy(&uiCommand, &m_ucudp_buf[m_usudp_count][28], 1);
						if (uiCommand == 0x01)
						{
							// ��ʾSN
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][29]);
							m_csHeadFrameShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][30]);
							m_csHeadFrameShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][31]);
							m_csHeadFrameShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][32]);
							m_csHeadFrameShow += strTemp;
							m_csHeadFrameShow += _T("\t");
							// ��ʾ�װ�ʱ��
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][34]);
							m_csHeadFrameShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][35]);
							m_csHeadFrameShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][36]);
							m_csHeadFrameShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][37]);
							m_csHeadFrameShow += strTemp;
							m_csHeadFrameShow += _T("\r\n");

							m_pwnd->GetDlgItem(IDC_EDIT_HEADFRAMESHOW)->SetWindowText(m_csHeadFrameShow);
							m_uiHeadFrameNum++;
							strTemp.Format(_T("%d"),m_uiHeadFrameNum);
							m_pwnd->GetDlgItem(IDC_STATIC_HEADFRAMENUM)->SetWindowText(strTemp);
						}
					}
					else if (uiPort == IPSetPort)
					{
						memcpy(&uiCommand, &m_ucudp_buf[m_usudp_count][28], 1);
						if (uiCommand == 0x01)
						{
							// ��ʾSN
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][29]);
							m_csIPSetReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][30]);
							m_csIPSetReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][31]);
							m_csIPSetReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][32]);
							m_csIPSetReturnShow += strTemp;
							m_csIPSetReturnShow += _T("\t");
							// ��ʾIP
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][34]);
							m_csIPSetReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][35]);
							m_csIPSetReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][36]);
							m_csIPSetReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][37]);
							m_csIPSetReturnShow += strTemp;
							m_csIPSetReturnShow += _T("\r\n");
							m_pwnd->GetDlgItem(IDC_EDIT_IPSETRETURNSHOW)->SetWindowText(m_csIPSetReturnShow);
							m_uiIPSetReturnNum++;
							strTemp.Format(_T("%d"),m_uiIPSetReturnNum);
							m_pwnd->GetDlgItem(IDC_STATIC_IPSETRETURNNUM)->SetWindowText(strTemp);
						}
					}
					else if (uiPort == TailFramePort)
					{
						memcpy(&uiCommand, &m_ucudp_buf[m_usudp_count][33], 1);
						if (uiCommand == 0x01)
						{
							// ��ʾSN
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][34]);
							m_csTailFrameShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][35]);
							m_csTailFrameShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][36]);
							m_csTailFrameShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][37]);
							m_csTailFrameShow += strTemp;
							m_csTailFrameShow += _T("\t");

							// ��ʾIP
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][29]);
							m_csTailFrameShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][30]);
							m_csTailFrameShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][31]);
							m_csTailFrameShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][32]);
							m_csTailFrameShow += strTemp;
							m_csTailFrameShow += _T("\r\n");

							m_pwnd->GetDlgItem(IDC_EDIT_TAILFRAMESHOW)->SetWindowText(m_csTailFrameShow);
							m_uiTailFrameNum++;
							strTemp.Format(_T("%d"),m_uiTailFrameNum);
							m_pwnd->GetDlgItem(IDC_STATIC_TAILFRAMENUM)->SetWindowText(strTemp);
						}
					}
					else if (uiPort == TailTimeFramePort)
					{
						memcpy(&uiCommand, &m_ucudp_buf[m_usudp_count][28], 1);
						if (uiCommand == 0x01)
						{	// ��ʾSN
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][29]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][30]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][31]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][32]);
							m_csTailTimeReturnShow += strTemp;
							m_csTailTimeReturnShow += _T(" ");
							// ��ʾ����ʱ��
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][34]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][35]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][36]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][37]);
							m_csTailTimeReturnShow += strTemp;
							m_csTailTimeReturnShow += _T(" ");
							// ��ʾ����ʱ��
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][39]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][40]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][41]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][42]);
							m_csTailTimeReturnShow += strTemp;
					
							m_csTailTimeReturnShow += _T("\r\n");
							m_pwnd->GetDlgItem(IDC_EDIT_TAILTIMERETURNSHOW)->SetWindowText(m_csTailTimeReturnShow);
							m_uiTailTimeReturnNum++;
							strTemp.Format(_T("%d"),m_uiTailTimeReturnNum);
							m_pwnd->GetDlgItem(IDC_STATIC_TAILTIMERETURNNUM)->SetWindowText(strTemp);
						}
					}
					else if (uiPort == TimeSetPort)
					{
						memcpy(&uiCommand, &m_ucudp_buf[m_usudp_count][28], 1);
						if (uiCommand == 0x05)
						{
							// ��ʾIP
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][16]);
							m_csDelayTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][17]);
							m_csDelayTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][18]);
							m_csDelayTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][19]);
							m_csDelayTimeReturnShow += strTemp;
							m_csDelayTimeReturnShow += _T(" ");

							// ��ʾ��ʱ������λ
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][29]);
							m_csDelayTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][30]);
							m_csDelayTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][31]);
							m_csDelayTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][32]);
							m_csDelayTimeReturnShow += strTemp;
							m_csDelayTimeReturnShow += _T(" ");

							// ��ʾ��ʱ������λ
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][34]);
							m_csDelayTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][35]);
							m_csDelayTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][36]);
							m_csDelayTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][37]);
							m_csDelayTimeReturnShow += strTemp;
							m_csDelayTimeReturnShow += _T("\r\n");

							m_pwnd->GetDlgItem(IDC_EDIT_DELAYTIMERETURNSHOW)->SetWindowText(m_csDelayTimeReturnShow);
							m_uiDelayTimeReturnNum++;
							strTemp.Format(_T("%d"),m_uiDelayTimeReturnNum);
							m_pwnd->GetDlgItem(IDC_STATIC_DELAYTIMERETURNNUM)->SetWindowText(strTemp);
						}
					}
					else if (uiPort == ADSetReturnPort)
					{
						// ÿ�βɼ�ֻ��һ��ADC����Ӧ��֡
						m_uiADCSetReturnNum++;
						strTemp.Format(_T("%d"),m_uiADCSetReturnNum);
						m_pwnd->GetDlgItem(IDC_STATIC_ADCSETRETURNNUM)->SetWindowText(strTemp);
					}

					m_uiRecFrameNum++;
// 					strTemp.Format(_T("%d"),m_uiRecFrameNum);
// 					m_pWndTab->GetDlgItem(IDC_STATIC_RECFRAMENUM)->SetWindowText(strTemp);
					if (m_bPortDistribution == TRUE)
					{
						// �����˿ڷַ�����
						m_SendSocket.SendTo(m_ucudp_buf[m_usudp_count],RcvFrameSize,uiPort,m_csIP);
					}
					else
					{
						m_SendSocket.SendTo(m_ucudp_buf[m_usudp_count],RcvFrameSize,m_iSendPort,m_csIP);
					}

					m_pSaveFile->OnSaveSendData(m_ucudp_buf[m_usudp_count],RcvFrameSize);
					m_usudp_count +=1;
					m_usudp_count = m_usudp_count%8;
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
		Sleep(1);
	}
	::SetEvent(m_hPortMonitoringSendThreadClose);	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	return CWinThread::Run();
}

// ��ʼ��
void CPortMonitoringSendThread::OnInit(void)
{
	m_hPortMonitoringSendThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	::ResetEvent(m_hPortMonitoringSendThreadClose);	// �����¼�����Ϊ���ź�״̬
}

// ��
void CPortMonitoringSendThread::OnOpen(void)
{
	m_SendSocket.Close();
	int flag =  m_SendSocket.Create(m_iRecPort,SOCK_DGRAM);
	m_SendSocket.SetSockOpt(SO_RCVBUF,&m_SendSocket,PortMonitoringBufSize,SOL_SOCKET);
	m_SendSocket.SetSockOpt(SO_SNDBUF,&m_SendSocket,PortMonitoringBufSize,SOL_SOCKET);
}

// ֹͣ
void CPortMonitoringSendThread::OnStop(void)
{
	m_SendSocket.Close();
}

// �ر�
void CPortMonitoringSendThread::OnClose(void)
{
	m_SendSocket.Close();
	m_bclose = true;
}
// ���ý���
void CPortMonitoringSendThread::OnReset(void)
{
	CString strTemp;
	// �װ�����
	m_uiHeadFrameNum = 0;
	strTemp.Format(_T("%d"),m_uiHeadFrameNum);

	m_pwnd->GetDlgItem(IDC_STATIC_HEADFRAMENUM)->SetWindowText(strTemp);

	// IP��ַ���ü���
	m_uiIPSetReturnNum = 0;
	strTemp.Format(_T("%d"),m_uiIPSetReturnNum);
	m_pwnd->GetDlgItem(IDC_STATIC_IPSETRETURNNUM)->SetWindowText(strTemp);

	// β������
	m_uiTailFrameNum = 0;
	strTemp.Format(_T("%d"),m_uiTailFrameNum);
	m_pwnd->GetDlgItem(IDC_STATIC_TAILFRAMENUM)->SetWindowText(strTemp);

	// β��ʱ�̲�ѯӦ�����
	m_uiTailTimeReturnNum = 0;
	strTemp.Format(_T("%d"),m_uiTailTimeReturnNum);
	m_pwnd->GetDlgItem(IDC_STATIC_TAILTIMERETURNNUM)->SetWindowText(strTemp);

	// ʱ������Ӧ�����
	m_uiDelayTimeReturnNum = 0;
	strTemp.Format(_T("%d"),m_uiDelayTimeReturnNum);
	m_pwnd->GetDlgItem(IDC_STATIC_DELAYTIMERETURNNUM)->SetWindowText(strTemp);

	// ADC����Ӧ�����
	m_uiADCSetReturnNum = 0;
	strTemp.Format(_T("%d"),m_uiADCSetReturnNum);
	m_pwnd->GetDlgItem(IDC_STATIC_ADCSETRETURNNUM)->SetWindowText(strTemp);

// 	// ADC���ݲɼ�֡����
// 	m_uiADCDataRecNum = 0;
// 	strTemp.Format(_T("%d"),m_uiADCDataRecNum);
// 	m_pwnd->GetDlgItem(IDC_STATIC_ADCDATARECNUM)->SetWindowText(strTemp);

	// ��ʾ�װ�֡������SN���װ�ʱ��
	m_csHeadFrameShow = _T("");
	m_pwnd->GetDlgItem(IDC_EDIT_HEADFRAMESHOW)->SetWindowText(_T(""));

	// ��ʾIP��ַ����Ӧ��֡������SN�����õ�IP��ַ
	m_csIPSetReturnShow = _T("");
	m_pwnd->GetDlgItem(IDC_EDIT_IPSETRETURNSHOW)->SetWindowText(_T(""));

	// ��ʾβ��֡������SN
	m_csTailFrameShow = _T("");
	m_pwnd->GetDlgItem(IDC_EDIT_TAILFRAMESHOW)->SetWindowText(_T(""));

	// ��ʾβ��ʱ�̲�ѯӦ��֡������IP��ַ�Ͳ�ѯ���
	m_csTailTimeReturnShow = _T("");
	m_pwnd->GetDlgItem(IDC_EDIT_TAILTIMERETURNSHOW)->SetWindowText(_T(""));

	// ��ʾʱ������Ӧ��֡������IP��ַ����������
	m_csDelayTimeReturnShow = _T("");
	m_pwnd->GetDlgItem(IDC_EDIT_DELAYTIMERETURNSHOW)->SetWindowText(_T(""));

	// ��ʾADC��������֡������IP��ַ��֡�����Ͳ�������֡����
	m_csADCDataRecShow = _T("");
	m_pwnd->GetDlgItem(IDC_EDIT_ADCDATARECSHOW)->SetWindowText(_T(""));

	// ����֡��
	m_uiRecFrameNum = 0;
	strTemp.Format(_T("%d"),m_uiRecFrameNum);
	m_pWndTab->GetDlgItem(IDC_STATIC_RECFRAMENUM)->SetWindowText(strTemp);

}
// ��ֹ������ѭ���������޷���Ӧ��Ϣ
void CPortMonitoringSendThread::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}
